#pragma once
#ifndef JRENDER_SHAPES_CONE_H
#define JRENDER_SHAPES_CONE_H

#include "shape.h"

namespace jrender {
	class Cone :public Shape {
	public:
		Cone(const Transform* o2w, const Transform* w2o, bool reverseOrientation,
			Float height, Float radius, Float phiMax);
		Bounds3f ObjectBound() const;
		Float Area() const;
	protected:
		const Float radius, height, phiMax;
	};
}
#endif // !JRENDER_SHAPES_CONE_H
