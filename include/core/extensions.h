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

#define ALWAYS_INLINE __attribute__((always_inline))
#define DEPRECATED __attribute__((deprecated))
#define NORETURN __attribute__((noreturn))
#define PACKED __attribute__((__packed__)) __VA_ARGS__
#define OPTIMIZE(i) __attribute__ ((optimize(i)))

#else

#error The Citrus Engine requires a G++ compatible compiler

#endif

#define FORCE_INLINE ALWAYS_INLINE
#define OPERATOR ALWAYS_INLINE

#define STRINGIFY(...) __STRINGIFY__(##__VA_ARGS__)
#define __STRINGIFY__(...) #__VA_ARGS__

#define __VA_ARGS_FIX__(...) __VA_ARGS__

#define NOMANGLE extern "C"

#define COMPILE_ASSERT(cond, msg) static_assert(cond, msg)

// Used for interthread communication, just volatile but whatever.
#define INTERTHREAD volatile

// Same thing as INTERTHREAD
#define MUTEX INTERTHREAD

#endif
