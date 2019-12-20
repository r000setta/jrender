#include "cone.h"

namespace jrender {
	Cone::Cone(const Transform* o2w, const Transform* w2o, bool ro, Float height,
		Float radius, Float phiMax)
		: Shape(o2w, w2o, ro),
		radius(radius),
		height(height),
		phiMax(Radians(Clamp(phiMax, 0, 360))) {}
	Bounds3f Cone::ObjectBound() const {
		Point3f p1 = Point3f(-radius, -radius, 0);
		Point3f p2 = Point3f(radius, radius, height);
		return Bounds3f(p1, p2);
	}
	Float Cone::Area() const {
		return radius * std::sqrt((height * height) + (radius * radius)) * phiMax /
			2;
	}
}