#pragma once
#ifndef JRENDER_SHAPES_PARABOLOID_H
#define JRENDER_SHAPES_PARABOLOID_H

#include "shape.h"

namespace jrender {
	class Paraboloid :public Shape {
	public:
		Paraboloid(const Transform* o2w, const Transform* w2o,
			bool reverseOrientation, Float radius, Float z0, Float z1,
			Float phiMax);
		Bounds3f ObjectBound() const;
		Float Area() const;
	protected:
		// Paraboloid Private Data
		const Float radius, zMin, zMax, phiMax;
	};
}

#endif // !JRENDER_SHAPES_PARABOLOID_H
