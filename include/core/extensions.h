/*
*   name: include/core/extensions.h
*   origin: Citrus Engine
*   purpose: Provide common compiler extensions in the form of preprocessor defines
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: CC0-1.0 OR LGPL-3.0-only
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
#define _ATTRIBUTE_(...) __VA_ARGS_FIX__(__attribute__(( __VA_ARGS__ )))

#else

#error The Citrus Engine requires a G++ compatible compiler

#endif

#define _FORCE_INLINE_ _ALWAYS_INLINE_
#define OPERATOR _ALWAYS_INLINE_

#define _STRINGIFY_(...) __STRINGIFY__(##__VA_ARGS__)
#define __STRINGIFY__(...) #__VA_ARGS__

#define __VA_ARGS_FIX__(...) __VA_ARGS__

#define NOMANGLE extern "C"

#define COMPILE_ASSERT(cond, msg) static_assert(cond, msg)

#endif
