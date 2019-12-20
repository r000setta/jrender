#pragma once
#ifndef JRENDER_SHAPES_CYLINDER_H
#define JRENDER_SHAPES_CYLINDER_H

#include "shape.h"
namespace jrender {
	class Cylinder :public Shape {
		Cylinder(const Transform* ObjectToWorld, const Transform* WorldToObject,
			bool reverseOrientation, Float radius, Float zMin, Float zMax,
			Float phiMax)
			: Shape(ObjectToWorld, WorldToObject, reverseOrientation),
			radius(radius),
			zMin(std::min(zMin, zMax)),
			zMax(std::max(zMin, zMax)),
			phiMax(Radians(Clamp(phiMax, 0, 360))) {}
		Bounds3f ObjectBound() const;
		Float Area() const;
	protected:
		const Float radius, zMin, zMax, phiMax;
	};
}

#endif // !JRENDER_SHAPES_CYLINDER_H
