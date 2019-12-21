#pragma once
#ifndef JRENDER_CORE_SPECTRUM_H
#define JRENDER_CORE_SPECTRUM_H

#include "render.h"

namespace jrender {
	template <int nSpectrumSamples>
	class CoefficientSpectrum {
	public:
		CoefficientSpectrum(Float v = 0.f) {
			for (int i = 0; i < nSpectrumSamples; i++) c[i] = v;
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
		bool HasNaNs() const {
			for (int i = 0; i < nSpectrumSamples; ++i)
				if (std::isnan(c[i])) return true;
			return false;
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
}

#endif // !JRENDER_CORE_SPECTRUM_H
