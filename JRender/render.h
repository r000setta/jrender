#pragma once
#include <type_traits>
#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <float.h>
#include <intrin.h>
#include <stdarg.h>
#include "logging.h"
typedef float Float;
static Float Pi = 3.14159265358979323846;
#define Infinity std::numeric_limits<Float>::infinity()
inline Float Radians(Float deg) {
	return (Pi / 180) * deg;
}