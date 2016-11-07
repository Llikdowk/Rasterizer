#pragma once
#include <algorithm>

namespace Utils
{
	template <typename T>
	T clamp(T value, T min, T max)
	{
		return std::max(min, std::min(value, max));
	}
}