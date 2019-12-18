#pragma once
#ifndef JRENDER_GEOMETRY_H
#define JRENDER_GEOMETRY_H

#include "render.h"
#include "stringprint.h"

template <typename T>
inline bool isNaN(const T x) {
	return std::isnan(x);
}

template <>
inline bool isNaN(const int x) {
	return false;
}

template <typename T>
class Vector2 {
public:
	Vector2() { x = y = 0; }
	Vector2(T xx, T yy) :x(xx), y(yy) {}
	bool HasNaNs() const { return isNaN(x) || isNaN(y); }
	explicit Vector2(const Point2<T> &p):x(p.x),y(p.y){}
	explicit Vector2(const Point3<T> &p):x(p.x),y(p.y){}
	Vector2(const Vector2<T>& v) {
		////DCHECK(!v.HasNaNs());
		x = v.x;
		y = v.y;
	}

	Vector2<T>& operator=(const Vector2<T>& v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	Vector2 operator+(const Vector2<T>& v) {
		return Vector2(x + v.x, y + v.y);
	}

	Vector2& operator+=(const Vector2<T>& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2 operator-(const Vector2<T>& v) {
		return Vector2(x - v.x, y - v.y);
	}

	Vector2& operator-=(const Vector2<T>& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	bool operator==(const Vector2<T>& v) const { return x == v.x && y == v.y; }
	bool operator!=(const Vector2<T>& v) const { return x != v.x || y != v.y; }
	template <typename U>
	Vector2<T> operator*(U f) const {
		return Vector2<T>(f * x, f * y);
	}

	template <typename U>
	Vector2<T>& operator*=(U f) const {
		x *= f;
		y *= f;
		return *this;
	}

	template <typename U>
	Vector2<T> operator/(U f) const {
		////CHECK_NE(f, 0);
		Float inv = (Float)1 / f;
		return Vector2<T>(x * inv, y * inv);
	}

	template <typename U>
	Vector2<T>& operator/=(U f) {
		////CHECK_NE(f, 0);
		Float inv = (Float)1 / f;
		x *= inv;
		y *= inv;
		return *this;
	}
	Vector2<T> operator-() const { return Vector2<T>(-x, -y); }
	T operator[](int i) const {
		////DCHECK(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}

	T& operator[](int i) {
		////DCHECK(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}
	Float LengthSquared() const { return x * x + y * y; }
	Float Length() const { return std::sqrt(LengthSquared()); }
	T x, y;
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
	os << "[ " << v.x << ", " << v.y << " ]";
	return os;
}

template <>
inline std::ostream& operator<<(std::ostream& os, const Vector2<Float>& v) {
	os << StringPrintf("[ %f, %f ]", v.x, v.y);
	return os;
}

template <typename T>
class Vector3 {
public:
	T operator[](int i) const {
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	T& operator[](int i) {
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}
	Vector3() { x = y = z = 0; }
	Vector3(T x, T y, T z) :x(x), y(y), z(z) {}
	bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
	explicit Vector3(const Point3<T>& p) :x(p.x), y(p.y), z(p.z){}
	Vector3(const Vector3<T>& v) {
		////DCHECK(!v.HasNaNs());
		x = v.x;
		y = v.y;
		z = v.z;
	}

	Vector3<T>& operator=(const Vector3<T>& v) {
		////DCHECK(!v.HasNaNs());
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	Vector3<T> operator+(const Vector3<T>& v) const {
		////DCHECK(!v.HasNaNs());
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3<T>& operator+=(const Vector3<T>& v) {
		////DCHECK(!v.HasNaNs());
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector3<T> operator-(const Vector3<T>& v) const {
		////DCHECK(!v.HasNaNs());
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	Vector3<T>& operator-=(const Vector3<T>& v) {
		////DCHECK(!v.HasNaNs());
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	bool operator==(const Vector3<T>& v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	bool operator!=(const Vector3<T>& v) const {
		return x != v.x || y != v.y || z != v.z;
	}
	template <typename U>
	Vector3<T> operator*(U s) const {
		return Vector3<T>(s * x, s * y, s * z);
	}
	template <typename U>
	Vector3<T>& operator*=(U s) {
		////DCHECK(!isNaN(s));
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	template <typename U>
	Vector3<T> operator/(U f) const {
		////CHECK_NE(f, 0);
		Float inv = (Float)1 / f;
		return Vector3<T>(x * inv, y * inv, z * inv);
	}

	template <typename U>
	Vector3<T>& operator/=(U f) {
		////CHECK_NE(f, 0);
		Float inv = (Float)1 / f;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}
	Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }
	Float LengthSquared() const { return x * x + y * y + z * z; }
	Float Length() const { return std::sqrt(LengthSquared()); }
	T x, y, z;
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) {
	os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
	return os;
}

template <>
inline std::ostream& operator<<(std::ostream& os, const Vector3<Float>& v) {
	os << StringPrintf("[ %f, %f, %f ]", v.x, v.y, v.z);
	return os;
}

typedef Vector2<Float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector3<Float> Vector3f;
typedef Vector3<int> Vector3i;

template <typename T>
class Point2 {
public:
	explicit Point2(const Point3<T>& p) :x(p.x), y(p.y) {}
	Point2() { x = y = 0; }
	Point2(T xx, T yy):x(xx),y(yy){}

	template <typename U>
	explicit Point2(const Point2<U>& p) {
		x = (T)p.x;
		y = (T)p.y;
		////DCHECK(!HasNaNs());
	}

	template <typename U>
	explicit Point2(const Vector2<U>& p) {
		x = (T)p.x;
		y = (T)p.y;
		////DCHECK(!HasNaNs());
	}

	template <typename U>
	explicit operator Vector2<U>() const {
		return Vector2<U>(x, y);
	}

	Point2(const Point2<T>& p) {
		////DCHECK(!p.HasNaNs());
		x = p.x;
		y = p.y;
	}

	Point2<T>& operator=(const Point2<T>& p) {
		////DCHECK(!p.HasNaNs());
		x = p.x;
		y = p.y;
		return *this;
	}
	Point2<T> operator+(const Vector2<T>& v) const {
		////DCHECK(!v.HasNaNs());
		return Point2<T>(x + v.x, y + v.y);
	}

	Point2<T>& operator+=(const Vector2<T>& v) {
		////DCHECK(!v.HasNaNs());
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2<T> operator-(const Point2<T>& p) const {
		////DCHECK(!p.HasNaNs());
		return Vector2<T>(x - p.x, y - p.y);
	}

	Point2<T> operator-(const Vector2<T>& v) const {
		////DCHECK(!v.HasNaNs());
		return Point2<T>(x - v.x, y - v.y);
	}
	Point2<T> operator-() const { return Point2<T>(-x, -y); }
	Point2<T>& operator-=(const Vector2<T>& v) {
		////DCHECK(!v.HasNaNs());
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Point2<T>& operator+=(const Point2<T>& p) {
		////DCHECK(!p.HasNaNs());
		x += p.x;
		y += p.y;
		return *this;
	}
	Point2<T> operator+(const Point2<T>& p) const {
		////DCHECK(!p.HasNaNs());
		return Point2<T>(x + p.x, y + p.y);
	}
	template <typename U>
	Point2<T> operator*(U f) const {
		return Point2<T>(f * x, f * y);
	}
	template <typename U>
	Point2<T>& operator*=(U f) {
		x *= f;
		y *= f;
		return *this;
	}
	template <typename U>
	Point2<T> operator/(U f) const {
		////CHECK_NE(f, 0);
		Float inv = (Float)1 / f;
		return Point2<T>(inv * x, inv * y);
	}
	template <typename U>
	Point2<T>& operator/=(U f) {
		////CHECK_NE(f, 0);
		Float inv = (Float)1 / f;
		x *= inv;
		y *= inv;
		return *this;
	}
	T operator[](int i) const {
		////DCHECK(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}

	T& operator[](int i) {
		////DCHECK(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}
	bool operator==(const Point2<T>& p) const { return x == p.x && y == p.y; }
	bool operator!=(const Point2<T>& p) const { return x != p.x || y != p.y; }
	bool HasNaNs() const { return isNaN(x) || isNaN(y); }

	// Point2 Public Data
	T x, y;
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Point2<T>& v) {
	os << "[ " << v.x << ", " << v.y << " ]";
	return os;
}

template <>
inline std::ostream& operator<<(std::ostream& os, const Point2<Float>& v) {
	os << StringPrintf("[ %f, %f ]", v.x, v.y);
	return os;
}

template <typename T>
class Point3 {
public:
	Point3() { x = y = z = 0; }
	Point3(T x, T y, T z):x(x), y(y), z(z) {}
	template <typename U>
	explicit Point3(const Point3<U>& p) :x((T)p.x), y((T)p.y), z((T)p.z){}
	template <typename U>
	explicit operator Vector3<U>() const {
		return Vector3<U>(x, y, z);
	}

	Point3(const Point3<T>& p) {
		x = p.x;
		y = p.y;
		z = p.z;
	}

	Point3<T>& operator=(const Point3<T>& p) {
		x = p.x;
		y = p.y;
		z = p.z;
		return *this;
	}

	Point3<T> operator+(const Vector3<T>& v) {
		return Point3<T>(x + v.x, y + v.y, z + v.z);
	}
	Point3<T>& operator+=(const Vector3<T>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector3<T> operator-(const Point3<T>& p) const {
		////DCHECK(!p.HasNaNs());
		return Vector3<T>(x - p.x, y - p.y, z - p.z);
	}
	Point3<T> operator-(const Vector3<T>& v) const {
		////DCHECK(!v.HasNaNs());
		return Point3<T>(x - v.x, y - v.y, z - v.z);
	}
	Point3<T>& operator-=(const Vector3<T>& v) {
		////DCHECK(!v.HasNaNs());
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Point3<T>& operator+=(const Point3<T>& p) {
		////DCHECK(!p.HasNaNs());
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}
	Point3<T> operator+(const Point3<T>& p) const {
		////DCHECK(!p.HasNaNs());
		return Point3<T>(x + p.x, y + p.y, z + p.z);
	}
	template <typename U>
	Point3<T>& operator*=(U f) {
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	template <typename U>
	Point3<T> operator/(U f) const {
		////CHECK_NE(f, 0);
		Float inv = (Float)1 / f;
		return Point3<T>(inv * x, inv * y, inv * z);
	}
	template <typename U>
	Point3<T>& operator/=(U f) {
		////CHECK_NE(f, 0);
		Float inv = (Float)1 / f;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}
	T operator[](int i) const {
		////DCHECK(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	T& operator[](int i) {
		////DCHECK(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}
	bool operator==(const Point3<T>& p) const {
		return x == p.x && y == p.y && z == p.z;
	}
	bool operator!=(const Point3<T>& p) const {
		return x != p.x || y != p.y || z != p.z;
	}
	template <typename U>
	Point3<T> operator*(U f) const {
		return Point3<T>(f * x, f * y, f * z);
	}
	bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
	Point3<T> operator-() const { return Point3<T>(-x, -y, -z); }
	T x, y, z;
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Point3<T>& v) {
	os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
	return os;
}

template <>
inline std::ostream& operator<<(std::ostream& os, const Point3<Float>& v) {
	os << StringPrintf("[ %f, %f, %f ]", v.x, v.y, v.z);
	return os;
}

typedef Point2<Float> Point2f;
typedef Point2<int> Point2i;
typedef Point3<Float> Point3f;
typedef Point3<int> Point3i;

template <typename T>
class Normal3 {
public:
	Normal3() { x = y = z = 0; }
	Normal3(T xx, T yy, T zz) :x(xx), y(yy), z(zz) {}
	bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }

	Normal3<T> operator-() const { return Normal3(-x, -y, -z); }
	T x, y, z;
};

class Ray {
public:
	Point3f o;
	Vector3f d;
	mutable Float Max;
	Float time;
};

template <typename T>
inline Vector3<T> Normalize(const Vector3<T>& v) {
	return v / v.Length();
}

template <typename T>
inline Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2) {
	////DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
	double v1x = v1.x, v1y = v1.y, v1z = v1.z;
	double v2x = v2.x, v2y = v2.y, v2z = v2.z;
	return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
		(v1x * v2y) - (v1y * v2x));
}

#endif // !JRENDER_GEOMETRY_H