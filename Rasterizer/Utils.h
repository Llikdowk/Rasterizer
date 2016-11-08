#pragma once
#include <algorithm>
#include <assert.h>

namespace Utils
{
	template <typename T>
	T clamp(T value, T min, T max)
	{
		return std::max(min, std::min(value, max));
	}

	template <typename T>
	T lerp(T a, T b, float t)
	{
		assert(t >= 0.0f && t <= 1.0f);
		return a*(1 - t) + b*t;
	}
}