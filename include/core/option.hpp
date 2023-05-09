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
		bool some;
		public:
		Option()
		{
			return none<T>();
		}

		Option(Option<T> &&o)
		{
			some = o.some;
			t = o.t;a
		}

		OPERATOR bool isSome()
		{
			return some;
		}

		OPERATOR bool isNone()
		{
			return !some;
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