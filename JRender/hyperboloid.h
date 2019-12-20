#pragma once
#ifndef JRENDER_SHAPE_HYPERBOLOID_H
#define JRENDER_SHAPE_HYPERBOLOID_H

#include "shape.h"
namespace jrender {
	class Hyperboloid :public Shape {
	public:
		Hyperboloid(const Transform* o2w, const Transform* w2o, bool ro,
			const Point3f& point1, const Point3f& point2, Float tm);
		Bounds3f ObjectBound() const;
		Float Area() const;
	protected:
		// Hyperboloid Private Data
		Point3f p1, p2;
		Float zMin, zMax;
		Float phiMax;
		Float rMax;
		Float ah, ch;
	};
}
#endif // !JRENDER_SHAPE_HYPERBOLOID_H
