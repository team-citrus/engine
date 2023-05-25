/*
*   name: include/core/stack.hpp
*   origin: Citrus Engine
*   purpose: Provide a stack data structure
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-ONLY
*/

#ifndef CITRUS_ENGINE_STACK_HPP__
#define CITRUS_ENGINE_STACK_HPP__

#include "../core/errno.hpp"
#include "../core/extensions.h"

template <typename T, const int I>
class StaticSizedStack
{
	T arr[I];
	size_t offset;
	public:
	T &push(T t)
	{
		T temp = t;
		if(offset == I - 1)
		{
			errorcode() = ENGINE_INVALID_ARG;
			return temp;
		}

		return (arr[offset++] = t);
	}

	T pop()
	{
		T temp;
		if(offset == 0)
		{
			errorcode() = ENGINE_INVALID_ARG;
			return temp;
		}
		return (arr[offset--]);
	}

	OPERATOR T &operator[](size_t index)
	{
		return (index < offset) ? arr[(offset - 1) - index] : arr[0] ;
	}

	OPERATOR T *data()
	{
		return arr;
	}
	
	OPERATOR size_t height()
	{
		return offset;
	}
};

#endif
