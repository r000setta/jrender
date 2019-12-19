#pragma once
#ifndef JRENDER_CORE_MEDIUM_H
#define JRENDER_CORE_MEDIUM_H

#include "render.h"
#include "geometry.h"
#include <memory>

namespace jrender {
	class PhaseFunction {
	public:
		virtual ~PhaseFunction();
		virtual Float p(const Vector3f& wo, const Vector3f& wi) const = 0;
		virtual Float Sample_p(const Vector3f& wo, Vector3f* wi,
			const Point2f& u) const = 0;
		virtual std::string ToString() const = 0;
	};

	inline std::ostream& operator<<(std::ostream& os, const PhaseFunction& p) {
		os << p.ToString();
		return os;
	}
}

#endif // !JRENDER_CORE_MEDIUM_H
