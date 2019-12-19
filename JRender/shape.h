#pragma once
#ifndef JRENDER_CORE_SHAPE_H
#define JRENDER_CORE_SHAPE_H

#include "render.h"
#include "geometry.h"
#include "transform.h"

namespace jrender {
	class Shape {
	public:
		Shape(const Transform* ObjectToWorld, const Transform* WorldToObject, bool reverseOrientation);
		virtual ~Shape();

		const Transform* ObjectToWorld, * WorldToObject;
		const bool reverseOrientation;
		const bool transformSwapHandedness;

		virtual Float Area() const = 0;
	};

}

#endif // !JRENDER_CORE_SHAPE_H
