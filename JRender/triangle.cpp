#include "triangle.h"

namespace jrender {
	Float Triangle::Area() const {
		const Point3f& p0 = mesh->p[v[0]];
		const Point3f& p1 = mesh->p[v[1]];
		const Point3f& p2 = mesh->p[v[2]];
		return 0.5 * Cross(p1 - p0, p2 - p0).Length();
	}

	Bounds3f Triangle::ObjectBound() const {

	}
}