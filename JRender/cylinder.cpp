#include "cylinder.h"

namespace jrender {
	Float Cylinder::Area() const {
		return (zMax - zMin) * radius * phiMax;
	}
}