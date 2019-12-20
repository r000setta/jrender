#include "disk.h"

namespace jrender {
	Bounds3f Disk::ObjectBound() const {
		return Bounds3f(Point3f(-radius, -radius, height),
			Point3f(radius, radius, height));
	}

	Float Disk::Area() const {
		return phiMax * 0.5 * (radius * radius - innerRadius * innerRadius);
	}
}