#pragma once
#ifndef JRENDER_TRANSFORM_H
#define JRENDER_TRANSFORM_H

#include "render.h"
#include "geometry.h"

struct Matrix4x4 {
	Matrix4x4() {
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
		m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = m[2][0] =
			m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.f;
	}
	Matrix4x4(Float mat[4][4]);
	Matrix4x4(Float t00, Float t01, Float t02, Float t03, Float t10, Float t11,
		Float t12, Float t13, Float t20, Float t21, Float t22, Float t23,
		Float t30, Float t31, Float t32, Float t33);

	bool operator==(const Matrix4x4& m2) const {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (m[i][j] != m2.m[i][j])
					return false;
			}
		}
	}
	bool operator!=(const Matrix4x4& m2) const {
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				if (m[i][j] != m2.m[i][j]) return true;
		return false;
	}
	friend Matrix4x4 Transpose(const Matrix4x4&);
	void Print(FILE* f) const {
		fprintf(f, "[ ");
		for (int i = 0; i < 4; ++i) {
			fprintf(f, "  [ ");
			for (int j = 0; j < 4; ++j) {
				fprintf(f, "%f", m[i][j]);
				if (j != 3) fprintf(f, ", ");
			}
			fprintf(f, " ]\n");
		}
		fprintf(f, " ] ");
	}
	static Matrix4x4 Mul(const Matrix4x4& m1, const Matrix4x4& m2) {
		Matrix4x4 r;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				r.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] +
				m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
		return r;
	}
	friend Matrix4x4 Inverse(const Matrix4x4&);

	friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& m) {
		// clang-format off
		os << StringPrintf("[ [ %f, %f, %f, %f ] "
			"[ %f, %f, %f, %f ] "
			"[ %f, %f, %f, %f ] "
			"[ %f, %f, %f, %f ] ]",
			m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3],
			m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3],
			m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3],
			m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]);
		// clang-format on
		return os;
	}

	Float m[4][4];
};

class Transform {
public:
	Transform(){}
	Transform(const Float mat[4][4]) {
		m = Matrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3], mat[1][0],
			mat[1][1], mat[1][2], mat[1][3], mat[2][0], mat[2][1],
			mat[2][2], mat[2][3], mat[3][0], mat[3][1], mat[3][2],
			mat[3][3]);
		mInv = Inverse(m);
	}

	Transform(const Matrix4x4& m) :m(m),mInv(Inverse(m)){}
	Transform(const Matrix4x4& m, const Matrix4x4& mInv) :m(m), mInv(mInv) {}
	void Print(FILE* f) const;
	friend Transform Inverse(const Transform& t) {
		return Transform(t.mInv, t.m);
	}
	friend Transform Transpose(const Transform& t) {
		return Transform(Transpose(t.m), Transpose(t.mInv));
	}
	bool operator==(const Transform& t) const {
		return t.m == m && t.mInv == mInv;
	}
	bool operator!=(const Transform& t) const {
		return t.m != m || t.mInv != mInv;
	}
	bool operator<(const Transform& t2) const {
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j) {
				if (m.m[i][j] < t2.m.m[i][j]) return true;
				if (m.m[i][j] > t2.m.m[i][j]) return false;
			}
		return false;
	}
	bool IsIdentity() const {
		return (m.m[0][0] == 1.f && m.m[0][1] == 0.f && m.m[0][2] == 0.f &&
			m.m[0][3] == 0.f && m.m[1][0] == 0.f && m.m[1][1] == 1.f &&
			m.m[1][2] == 0.f && m.m[1][3] == 0.f && m.m[2][0] == 0.f &&
			m.m[2][1] == 0.f && m.m[2][2] == 1.f && m.m[2][3] == 0.f &&
			m.m[3][0] == 0.f && m.m[3][1] == 0.f && m.m[3][2] == 0.f &&
			m.m[3][3] == 1.f);
	}

	const Matrix4x4& GetMatrix() const { return m; }
	const Matrix4x4& GetInverseMatrix() const { return mInv; }
	bool HasScale() const {
		Float la2 = (*this)(Vector3f(1, 0, 0)).LengthSquared();
		Float lb2 = (*this)(Vector3f(0, 1, 0)).LengthSquared();
		Float lc2 = (*this)(Vector3f(0, 0, 1)).LengthSquared();
#define NOT_ONE(x) ((x) < .999f || (x) > 1.001f)
		return (NOT_ONE(la2) || NOT_ONE(lb2) || NOT_ONE(lc2));
#undef NOT_ONE
	}
	template <typename T>
	inline Point3<T> operator()(const Point3<T>& p) const;
	template <typename T>
	inline Vector3<T> operator()(const Vector3<T>& v) const;
	template <typename T>
	inline Normal3<T> operator()(const Normal3<T>&) const;
	inline Ray operator()(const Ray& r) const;
	//inline RayDifferential operator()(const RayDifferential& r) const;
	//Bounds3f operator()(const Bounds3f& b) const;
	Transform operator*(const Transform& t2) const;
	bool SwapsHandedness() const;
	//SurfaceInteraction operator()(const SurfaceInteraction& si) const;
	template <typename T>
	inline Point3<T> operator()(const Point3<T>& pt,
		Vector3<T>* absError) const;
	template <typename T>
	inline Point3<T> operator()(const Point3<T>& p, const Vector3<T>& pError,
		Vector3<T>* pTransError) const;
	template <typename T>
	inline Vector3<T> operator()(const Vector3<T>& v,
		Vector3<T>* vTransError) const;
	template <typename T>
	inline Vector3<T> operator()(const Vector3<T>& v, const Vector3<T>& vError,
		Vector3<T>* vTransError) const;
	inline Ray operator()(const Ray& r, Vector3f* oError,
		Vector3f* dError) const;
	inline Ray operator()(const Ray& r, const Vector3f& oErrorIn,
		const Vector3f& dErrorIn, Vector3f* oErrorOut,
		Vector3f* dErrorOut) const;

	friend std::ostream& operator<<(std::ostream& os, const Transform& t) {
		os << "t=" << t.m << ", inv=" << t.mInv;
		return os;
	}
private:
	Matrix4x4 m, mInv;
};

Matrix4x4 Inverse(const Matrix4x4& m);
Transform Translate(const Vector3f& delta);
Transform Scale(Float x, Float y, Float z);
Transform RotateX(Float theta);
Transform RotateY(Float theta);
Transform RotateZ(Float theta);
Transform Rotate(Float theta, const Vector3f& axis);
Transform LookAt(const Point3f& pos, const Point3f& look, const Vector3f& up);
Transform Orthographic(Float znear, Float zfar);
Transform Perspective(Float fov, Float znear, Float zfar);
bool SolveLinearSystem2x2(const Float A[2][2], const Float B[2], Float* x0,
	Float* x1);
#endif // JRENDER_TRANSORM_H
