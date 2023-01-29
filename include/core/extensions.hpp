/*
*   name: include/core/extensions.hpp
*   origin: Citrus Engine
*   purpose: Provide common compiler extensions in the form of preprocessor defines
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_COMPILER_EXTENSIONS_HPP__
#define CITRUS_ENGINE_COMPILER_EXTENSIONS_HPP__

#ifdef __GNUC__

#define _GNU_ __GNUC__

#define _ALWAYS_INLINE_ __attribute__((always_inline))
#define _DEPRECATED_ __attribute__((deprecated))
#define _NORETURN_ __attribute__((noreturn))
#define _PACKED_(...) __attribute__((__packed__)) __VA_ARGS__
#define _OPTIMIZE_(i) __attribute__ ((optimize(i)))

#elif defined(_MSC_VER)

#define _MSVC_ _MSC_VER

#define _ALWAYS_INLINE_ __forceinline
#define _DEPRECATED_ __declspec(deprecated)
#define _NORETURN_ __declspec(noreturn)
#define _PACKED_(...) __pragma(pack(push, 1)) __VA_ARGS__ __pragma(pack(pop))
#define _OPTIMIZE_(i) __pragma(_STRINGIFY_(i), on)

#endif

#define _FORCE_INLINE_ _ALWAYS_INLINE_
#define OPERATOR _ALWAYS_INLINE_

#define _STRINGIFY_(...) __STRINGIFY__(##__VA_ARGS__)
#define __STRINGIFY__(...) #__VA_ARGS__

#define __VA_ARGS_FIX__(...) __VA_ARGS__

#define NOMANGLE extern "C"

#endif
