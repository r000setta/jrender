#pragma once
#ifndef JRENDER_SHAPE_DISK_H
#define JRENDER_SHAPE_DISK_H

#include "shape.h"

namespace jrender {
	class Disk :public Shape {
	public:
		Disk(const Transform* ObjectToWorld, const Transform* WorldToObject,
			bool reverseOrientation, Float height, Float radius, Float innerRadius,
			Float phiMax)
			: Shape(ObjectToWorld, WorldToObject, reverseOrientation),
			height(height),
			radius(radius),
			innerRadius(innerRadius),
			phiMax(Radians(Clamp(phiMax, 0, 360))) {}
		Bounds3f ObjectBound() const;
		Float Area() const;

	private:
		const Float height, radius, innerRadius, phiMax;
	};
}


#endif // !JRENDER_SHAPE_DISK_H
