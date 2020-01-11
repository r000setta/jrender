#pragma once
#ifndef JRENDER_CORE_SPECTRUM_H
#define JRENDER_CORE_SPECTRUM_H

#include "render.h"

namespace jrender {
	static const int sampledLambdaStart = 400;
	static const int sampledLambdaEnd = 700;
	static const int nSpectralSamples = 60;

	extern bool SpectrumSamplesSorted(const Float* lambda, const Float* vals,
		int n);
	extern void SortSpectrumSamples(Float* lambda, Float* vals, int n);
	extern Float AverageSpectrumSamples(const Float* lambda, const Float* vals,
		int n, Float lambdaStart, Float lambdaEnd);

	inline void XYZToRGB(const Float xyz[3], Float rgb[3]) {
		rgb[0] = 3.240479f * xyz[0] - 1.537150f * xyz[1] - 0.498535f * xyz[2];
		rgb[1] = -0.969256f * xyz[0] + 1.875991f * xyz[1] + 0.041556f * xyz[2];
		rgb[2] = 0.055648f * xyz[0] - 0.204043f * xyz[1] + 1.057311f * xyz[2];
	}

	inline void RGBToXYZ(const Float rgb[3], Float xyz[3]) {
		xyz[0] = 0.412453f * rgb[0] + 0.357580f * rgb[1] + 0.180423f * rgb[2];
		xyz[1] = 0.212671f * rgb[0] + 0.715160f * rgb[1] + 0.072169f * rgb[2];
		xyz[2] = 0.019334f * rgb[0] + 0.119193f * rgb[1] + 0.950227f * rgb[2];
	}

	enum class SpectrumType {
		Reflectance,Illuminant
	};

	extern Float InterpolateSpectrumSamples(const Float* lambda, const Float* vals, int n, Float l);
	extern void Blackbody(const Float* lambda, int n, Float T, Float* Le);
	extern void BlackbodyNormalized(const Float* lambda, int n, Float T, Float* vals);

	static const int nCIESamples = 471;
	extern const Float CIE_X[nCIESamples];
	extern const Float CIE_Y[nCIESamples];
	extern const Float CIE_Z[nCIESamples];
	extern const Float CIE_lambda[nCIESamples];
	static const Float CIE_Y_integral = 106.856895;

	template <int nSpectrumSamples>
	class CoefficientSpectrum {
	public:
		CoefficientSpectrum(Float v = 0.f) {
			for (int i = 0; i < nSpectrumSamples; i++) c[i] = v;
		}

		void Print(FILE* f) const {
			fprintf(f, "[");
			for (size_t i = 0; i < nSpectrumSamples; i++){
				fprintf(f, "%f", c[i]);
				if (i != nSpectrumSamples - 1)
					fprintf(f, ",");
			}
			fprintf(f, "]");
		}

		CoefficientSpectrum& operator+=(const CoefficientSpectrum& s2) {
			for (int i = 0; i < nSpectrumSamples; i++)
				c[i] += s2.c[i];
			return *this;
		}
		CoefficientSpectrum operator+(const CoefficientSpectrum& s2) const {
			CoefficientSpectrum ret = *this;
			for (int i = 0; i < nSpectrumSamples; ++i) ret.c[i] += s2.c[i];
			return ret;
		}
		CoefficientSpectrum operator-(const CoefficientSpectrum& s2) const {
			//DCHECK(!s2.HasNaNs());
			CoefficientSpectrum ret = *this;
			for (int i = 0; i < nSpectrumSamples; ++i) ret.c[i] -= s2.c[i];
			return ret;
		}
		CoefficientSpectrum operator/(const CoefficientSpectrum& s2) const {
			//DCHECK(!s2.HasNaNs());
			CoefficientSpectrum ret = *this;
			for (int i = 0; i < nSpectrumSamples; ++i) {
				//CHECK_NE(s2.c[i], 0);
				ret.c[i] /= s2.c[i];
			}
			return ret;
		}
		CoefficientSpectrum operator*(const CoefficientSpectrum& sp) const {
			//DCHECK(!sp.HasNaNs());
			CoefficientSpectrum ret = *this;
			for (int i = 0; i < nSpectrumSamples; ++i) ret.c[i] *= sp.c[i];
			return ret;
		}
		CoefficientSpectrum& operator*=(const CoefficientSpectrum& sp) {
			//DCHECK(!sp.HasNaNs());
			for (int i = 0; i < nSpectrumSamples; ++i) c[i] *= sp.c[i];
			return *this;
		}
		CoefficientSpectrum operator*(Float a) const {
			CoefficientSpectrum ret = *this;
			for (int i = 0; i < nSpectrumSamples; ++i) ret.c[i] *= a;
			//DCHECK(!ret.HasNaNs());
			return ret;
		}
		CoefficientSpectrum& operator*=(Float a) {
			for (int i = 0; i < nSpectrumSamples; ++i) c[i] *= a;
			//DCHECK(!HasNaNs());
			return *this;
		}
		friend inline CoefficientSpectrum operator*(Float a,
			const CoefficientSpectrum& s) {
			return s * a;
		}
		CoefficientSpectrum operator/(Float a) const {
			CoefficientSpectrum ret = *this;
			for (int i = 0; i < nSpectrumSamples; ++i) ret.c[i] /= a;
			return ret;
		}
		CoefficientSpectrum& operator/=(Float a) {
			for (int i = 0; i < nSpectrumSamples; ++i) c[i] /= a;
			return *this;
		}
		bool operator==(const CoefficientSpectrum& sp) const {
			for (int i = 0; i < nSpectrumSamples; ++i)
				if (c[i] != sp.c[i]) return false;
			return true;
		}
		bool operator!=(const CoefficientSpectrum& sp) const {
			return !(*this == sp);
		}
		bool IsBlack() const {
			for (int i = 0; i < nSpectrumSamples; ++i)
				if (c[i] != 0.) return false;
			return true;
		}
		friend CoefficientSpectrum Sqrt(const CoefficientSpectrum& s) {
			CoefficientSpectrum ret;
			for (int i = 0; i < nSpectrumSamples; ++i) ret.c[i] = std::sqrt(s.c[i]);
			//DCHECK(!ret.HasNaNs());
			return ret;
		}

		template <int n>
		friend inline CoefficientSpectrum<n> Pow(const CoefficientSpectrum<n>& s, Float e);

		friend CoefficientSpectrum Exp(const CoefficientSpectrum& s) {
			CoefficientSpectrum ret;
			for (int i = 0; i < nSpectrumSamples; ++i)
				ret.c[i] = std::exp(s.c[i]);
			return ret;
		}

		friend std::ostream& operator<<(std::ostream& os, const CoefficientSpectrum& s) {
			return os << s.ToString();
		}
		
		std::string ToString() const {
			std::string str = "[";
			for (int i = 0; i < nSpectrumSamples; ++i) {
				ret.c[i] = Clamp(c[i], low, high);
			}
			return ret;
		}
		bool HasNaNs() const {
			for (int i = 0; i < nSpectrumSamples; ++i)
				if (std::isnan(c[i])) return true;
			return false;
		}

		bool Write(FILE* f) const {
			for (int i = 0; i < nSpectrumSamples; i++) {
				if (fprintf(f, "%f", c[i]) < 0)
					return false;
			}
			return true;
		}

		bool Read(FILE* f) {
			for (int i = 0; i < nSpectrumSamples; ++i) {
				double v;
				if (fscanf(f, "%lf", &v) < 0)
					return false;
				c[i] = v;
			}
			return true;
		}

		Float& operator[](int i) {
			//DCHECK(i >= 0 && i < nSpectrumSamples);
			return c[i];
		}
		Float operator[](int i) const {
			//DCHECK(i >= 0 && i < nSpectrumSamples);
			return c[i];
		}
		static const int nSamples = nSpectrumSamples;
	protected:
		Float c[nSpectrumSamples];
	};

	class SampledSpectrum :public CoefficientSpectrum<nSpectralSamples> {
	public:
		SampledSpectrum(Float v = 0.f) :CoefficientSpectrum(v) {}
		SampledSpectrum(const CoefficientSpectrum<nSpectralSamples>& v)
			: CoefficientSpectrum<nSpectralSamples>(v) {}
		
		//take arrays of SPD sample value v at given wavelengths lambda and use them
		//to define a piecewise linear function to represent the SPD
		static SampledSpectrum FromSampled(const Float* lambda, const Float* v, int n) {
			if (!SpectrumSamplesSorted(lambda, v, n)) {
				std::vector<Float> slambda(&lambda[0], &lambda[n]);
				std::vector<Float> sv(&v[0], &v[n]);
				SortSpectrumSamples(&slambda[0], &sv[0], n);
				return FromSampled(&slambda[0], &sv[0], n);
			}

			SampledSpectrum r;
			for (int i = 0; i < nSpectralSamples; ++i) {
				//Compute average value of given SPD over $i$ith sample's range
				Float lambda0 = Lerp(Float(i) / Float(nSpectralSamples), sampledLambdaStart, sampledLambdaEnd);
				Float lambda1 = Lerp(Float(i+1) / Float(nSpectralSamples), sampledLambdaStart, sampledLambdaEnd);
				r.c[i] = AverageSpectrumSamples(lambda, v, n, lambda0, lambda1);
			}
			return r;
		}
		static void Init() {
			//Compute XYZ matching functions for SampledSpectrum
			for (int i =0 ; i < nSpectralSamples; ++i) {
				Float wl0 = Lerp(Float(i) / Float(nSpectralSamples), sampledLambdaStart, sampledLambdaEnd);
				Float wl1 = Lerp(Float(i+1) / Float(nSpectralSamples), sampledLambdaStart, sampledLambdaEnd);
				X.c[i] = AverageSpectrumSamples(CIE_lambda, CIE_X, nCIESamples, wl0, wl1);
				Y.c[i] = AverageSpectrumSamples(CIE_lambda, CIE_Y, nCIESamples, wl0, wl1);
				Z.c[i] = AverageSpectrumSamples(CIE_lambda, CIE_Z, nCIESamples, wl0, wl1);
			}

			for (int i = 0; i < nSpectralSamples; ++i) {

			}
		}
		
		//Some processs need to convert the SPDinto XYZ coefficients as a first step and finally
		//turning them into RGB values used for storage or display.
		void ToXYZ(Float xyz[3]) const {
			xyz[0] = xyz[1] = xyz[2] = 0.f;
			for (int i = 0; i < nSpectralSamples; ++i) {
				xyz[0] += X.c[i] * c[i];
				xyz[1] += Y.c[i] * c[i];
				xyz[2] += Z.c[i] * c[i];
			}

			Float scale = Float(sampledLambdaEnd - sampledLambdaStart) /
				Float(CIE_Y_integral * nSpectralSamples);
			xyz[0] *= scale;
			xyz[1] *= scale;
			xyz[2] *= scale;
		}

		Float y() const {
			Float yy = 0.f;
			for (int i = 0; i < nSpectralSamples; ++i)
				yy += Y.c[i] * c[i];
			return yy * Float(sampledLambdaEnd - sampledLambdaStart) / Float(nSpectralSamples);
		}

		void ToRGB(Float rgb[3]) const {
			Float xyz[3];
			ToXYZ(xyz);
			XYZToRGB(xyz, rgb);
		}

	private:
		static SampledSpectrum X, Y, Z;
		static SampledSpectrum rgbRefl2SpectWhite, rgbRefl2SpectCyan;
		static SampledSpectrum rgbRefl2SpectMagenta, rgbRefl2SpectYellow;
		static SampledSpectrum rgbRefl2SpectRed, rgbRefl2SpectGreen;
		static SampledSpectrum rgbRefl2SpectBlue;
		static SampledSpectrum rgbIllum2SpectWhite, rgbIllum2SpectCyan;
		static SampledSpectrum rgbIllum2SpectMagenta, rgbIllum2SpectYellow;
		static SampledSpectrum rgbIllum2SpectRed, rgbIllum2SpectGreen;
		static SampledSpectrum rgbIllum2SpectBlue;
	};

	class RGBSpectrum :public CoefficientSpectrum<3> {
		using CoefficientSpectrum<3>::c;
	public:
		RGBSpectrum(Float v = 0.f) :CoefficientSpectrum<3>(v){}
		RGBSpectrum(const CoefficientSpectrum<3>& v) : CoefficientSpectrum<3>(v) {}
		RGBSpectrum(const RGBSpectrum& s,
			SpectrumType type = SpectrumType::Reflectance) {
			*this = s;
		}
		static RGBSpectrum FromRGB(const Float rgb[3],
			SpectrumType type = SpectrumType::Reflectance) {
			RGBSpectrum s;
			s.c[0] = rgb[0];
			s.c[1] = rgb[1];
			s.c[2] = rgb[2];
			return s;
		}

		void ToRGB(Float* rgb) const {
			rgb[0] = c[0];
			rgb[1] = c[1];
			rgb[2] = c[2];
		}

		const RGBSpectrum& ToRGBSpectrum() const { return *this; }
		
	};

}
#endif // !JRENDER_CORE_SPECTRUM_H