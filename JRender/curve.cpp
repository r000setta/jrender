#include "curve.h"

namespace jrender {

	static Point3f BlossomBezier(const Point3f p[4], Float u0, Float u1, Float u2) {
		Point3f a[3] = { Lerp(u0, p[0], p[1]), Lerp(u0, p[1], p[2]),
						Lerp(u0, p[2], p[3]) };
		Point3f b[2] = { Lerp(u1, a[0], a[1]), Lerp(u1, a[1], a[2]) };
		return Lerp(u2, b[0], b[1]);
	}

	Float Curve::Area() const {
		// Compute object-space control points for curve segment, _cpObj_
		Point3f cpObj[4];
		cpObj[0] = BlossomBezier(common->cpObj, uMin, uMin, uMin);
		cpObj[1] = BlossomBezier(common->cpObj, uMin, uMin, uMax);
		cpObj[2] = BlossomBezier(common->cpObj, uMin, uMax, uMax);
		cpObj[3] = BlossomBezier(common->cpObj, uMax, uMax, uMax);
		Float width0 = Lerp(uMin, common->width[0], common->width[1]);
		Float width1 = Lerp(uMax, common->width[0], common->width[1]);
		Float avgWidth = (width0 + width1) * 0.5f;
		Float approxLength = 0.f;
		for (int i = 0; i < 3; ++i)
			approxLength += Distance(cpObj[i], cpObj[i + 1]);
		return approxLength * avgWidth;
	}
}