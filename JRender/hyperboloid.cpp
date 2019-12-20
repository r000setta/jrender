#include "hyperboloid.h"

namespace jrender {
	Hyperboloid::Hyperboloid(const Transform* o2w, const Transform* w2o, bool ro,
		const Point3f& point1, const Point3f& point2, Float tm)
		: Shape(o2w, w2o, ro) {
		p1 = point1;
		p2 = point2;
		phiMax = Radians(Clamp(tm, 0, 360));
		Float radius1 = std::sqrt(p1.x * p1.x + p1.y * p1.y);
		Float radius2 = std::sqrt(p2.x * p2.x + p2.y * p2.y);
		rMax = std::max(radius1, radius2);
		zMin = std::min(p1.z, p2.z);
		zMax = std::max(p1.z, p2.z);
		// Compute implicit function coefficients for hyperboloid
		if (p2.z == 0.f) std::swap(p1, p2);
		Point3f pp = p1;
		Float xy1, xy2;
		do {
			pp += (Float)2. * (p2 - p1);
			xy1 = pp.x * pp.x + pp.y * pp.y;
			xy2 = p2.x * p2.x + p2.y * p2.y;
			ah = (1.f / xy1 - (pp.z * pp.z) / (xy1 * p2.z * p2.z)) /
				(1 - (xy2 * pp.z * pp.z) / (xy1 * p2.z * p2.z));
			ch = (ah * xy2 - 1) / (p2.z * p2.z);
		} while (std::isinf(ah) || std::isnan(ah));
	}

	Bounds3f Hyperboloid::ObjectBound() const {
		Point3f p1 = Point3f(-rMax, -rMax, zMin);
		Point3f p2 = Point3f(rMax, rMax, zMax);
		return Bounds3f(p1, p2);
	}

#define SQR(a) ((a)*(a))
#define QUAD(a) ((SQR(a))*(SQR(a)))
	Float Hyperboloid::Area() const {
		return phiMax / 6.f *
			(2 * QUAD(p1.x) - 2 * p1.x * p1.x * p1.x * p2.x + 2 * QUAD(p2.x) +
				2 * (p1.y * p1.y + p1.y * p2.y + p2.y * p2.y) *
				(SQR(p1.y - p2.y) + SQR(p1.z - p2.z)) +
				p2.x * p2.x * (5 * p1.y * p1.y + 2 * p1.y * p2.y - 4 * p2.y * p2.y +
					2 * SQR(p1.z - p2.z)) +
				p1.x * p1.x * (-4 * p1.y * p1.y + 2 * p1.y * p2.y +
					5 * p2.y * p2.y + 2 * SQR(p1.z - p2.z)) -
				2 * p1.x * p2.x *
				(p2.x * p2.x - p1.y * p1.y + 5 * p1.y * p2.y - p2.y * p2.y -
					p1.z * p1.z + 2 * p1.z * p2.z - p2.z * p2.z));
	}
#undef SQR
#undef QUAD
}