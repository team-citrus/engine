/*
*   name: include/core/math.hpp
*   origin: Citrus Engine
*   purpose: Provide some utility math functions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-ONLY
*/

#ifndef CITRUS_ENGINE_MATH_UTIL_HPP__
#define CITRUS_ENGINE_MATH_UTIL_HPP__

#include <cmath>

namespace engine
{
	template<typename T>
	T mapToRange(T a, T b, T c, T d, T input)
	{
		return c + (input - a)*(c-d)/(b-a);
	}

	template<typename T>
	T min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template<typename T>
	T max(T a, T b)
	{
		return (a > b) ? a : b;
	}
}

#endif