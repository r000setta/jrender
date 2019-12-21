#pragma once
#ifndef JRENDER_CORE_PRIMITIVE_H
#define JRENDER_CORE_PRIMITIVE_H

#include "render.h"	
#include "shape.h"
#include "transform.h"

namespace jrender {
	class Primitive {
	public:
		virtual ~Primitive();
		virtual Bounds3f WorldBound() const = 0;

	};

	class GeometricPrimitive :public Primitive {
	private:
		std::shared_ptr<Shape> shape;
	};
}

#endif // !JRENDER_CORE_PRIMITIVE_H
