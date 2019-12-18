#include "shape.h"

Shape::~Shape(){}

Shape::Shape(const Transform* ObjectToWorld, const Transform* WorldToObject,
	bool reverseOrientation)
	:ObjectToWorld(ObjectToWorld),
	WorldToObject(WorldToObject),
	reverseOrientation(reverseOrientation),
	transformSwapHandedness(ObjectToWorld->SwapsHandedness()) {
}

