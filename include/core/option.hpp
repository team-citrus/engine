/*
*   name: include/core/option.hpp
*   origin: Citrus Engine
*   purpose: Provide Rust-like options
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_OPTION_HPP___
#define CITRUS_ENGINE_OPTION_HPP___

#include "../core/extensions.h"

namespace engine
{
	template <typename T>
	class Option
	{
		T t;
		bool isItSome;
		public:
		Option()
		{
			return none<T>();
		}

		Option(Option<T> &&o)
		{
			isItSome = o.isItSome;
			t = o.t;
		}

		OPERATOR bool isSome()
		{
			return isItSome;
		}

		OPERATOR bool isNone()
		{
			return !isItSome;
		}

		OPERATOR T unwrap()
		{
			return t;
		}

		template<typename T> static OPERATOR Option<T> some(T t)
		{
			return Option<T> { t, true };
		}

		template<typename T> static OPERATOR Option<T> none()
		{
			Option<T> opt;
			opt.some = false;
			return opt;
		}
	};
}

#endif