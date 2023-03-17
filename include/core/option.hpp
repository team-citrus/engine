/*
*   name: include/core/option.hpp
*   origin: Citrus Engine
*   purpose: Provide Rust-like options
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_OPTION_HPP___
#define CITRUS_ENGINE_OPTION_HPP___

#include "core/extensions.h"

namespace engine
{
    template <typename T>
    class option
    {
        T t;
        bool some;
        public:
        option()
        {
            return none<T>();
        }

        option(option<T> &&o)
        {
            some = o.some;
            t = o.t;
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

        template<typename T> static OPERATOR option<T> some(T t)
        {
            return option<T> { t, true };
        }

        template<typename T> static OPERATOR option<T> none()
        {
            option<T> opt;
            opt.some = false;
            return opt;
        }
    };
}

#endif