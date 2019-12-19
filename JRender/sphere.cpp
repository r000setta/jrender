#include "sphere.h"

namespace jrender {
	Bounds3f Sphere::ObjectBound() const {
		return Bounds3f(Point3f(-radius, -radius, zMin),
			Point3f(radius, radius, zMax));
	}

	Float Sphere::Area() const {
		return phiMax * radius * (zMax - zMin);
	}
}