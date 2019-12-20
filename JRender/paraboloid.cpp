#include "paraboloid.h"

namespace jrender {
	Paraboloid::Paraboloid(const Transform* o2w, const Transform* w2o, bool ro,
		Float radius, Float z0, Float z1, Float phiMax)
		: Shape(o2w, w2o, ro),
		radius(radius),
		zMin(std::min(z0, z1)),
		zMax(std::max(z0, z1)),
		phiMax(Radians(Clamp(phiMax, 0, 360))) {}
	Bounds3f Paraboloid::ObjectBound() const {
		Point3f p1 = Point3f(-radius, -radius, zMin);
		Point3f p2 = Point3f(radius, radius, zMax);
		return Bounds3f(p1, p2);
	}

	Float Paraboloid::Area() const {
		Float radius2 = radius * radius;
		Float k = 4 * zMax / radius2;
		return (radius2 * radius2 * phiMax / (12 * zMax * zMax)) *
			(std::pow(k * zMax + 1, 1.5f) - std::pow(k * zMin + 1, 1.5f));
	}
}