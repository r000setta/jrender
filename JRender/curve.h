#pragma once
#ifndef JRENDER_SHAPE_CURVE
#define JRENDER_SHAPE_CURVE

#include "shape.h"

namespace jrender {
	enum class CurveType { Flat, Cylinder, Ribbon };
	struct CurveCommon {
		CurveCommon(const Point3f c[4], Float w0, Float w1, CurveType type,
			const Normal3f* norm);
		const CurveType type;
		Point3f cpObj[4];
		Float width[2];
		Normal3f n[2];
		Float normalAngle, invSinNormalAngle;
	};
	class Curve :public Shape {
	public:
		Bounds3f ObjectBound() const;
		Float Area() const;
	private:
		const std::shared_ptr<CurveCommon> common;
		const Float uMin, uMax;
	};

}

#endif // !JRENDER_SHAPE_CURVE
