#pragma once
#include "render.h"

inline void stringPrintfRecursive(std::string* s, const char* fmt) {
	const char* c = fmt;
	// No args left; make sure there aren't any extra formatting
	// specifiers.
	while (*c) {
		if (*c == '%') {
			//CHECK_EQ(c[1], '%');
			++c;
		}
		*s += *c++;
	}
}
template <typename... Args>
inline std::string StringPrintf(const char* fmt, Args... args) {
	std::string ret;
	stringPrintfRecursive(&ret, fmt, args...);
	return ret;
}