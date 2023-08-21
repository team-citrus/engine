/*
*   name: include/core/extensions.h
*   origin: Citrus Engine
*   purpose: Provide common compiler extensions and C++ attributes in the form of preprocessor defines
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: CC0-1.0 OR LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_COMPILER_EXTENSIONS_HPP__
#define CITRUS_ENGINE_COMPILER_EXTENSIONS_HPP__

#ifdef __GNUC__

#define GNU __GNUC__

#ifdef __cplusplus

#define ALWAYS_INLINE [[gnu::always_inline]]
#define NEVER_INLINE [[gnu::noinline]]
#define DEPRECATED(...) [[deprecated(STRINGIFY(__VA_ARGS__))]]
#define NORETURN [[noreturn]]
#define NO_DISCARD [[nodiscard]]
#define PURE [[gnu::pure]]
#define SYMBOL_ALIAS(x) __attribute__((alias(STRINGIFY(x))))
#define WEAK [[gnu::weak]]
#define WARN_UNUSED [[nodiscard]]

#else

#define ALWAYS_INLINE __attribute__((always_inline))
#define NEVER_INLINE __attribute__((noinline))
#define DEPRECATED __attribute__((deprecated))
#define NORETURN __attribute__((noreturn))
#define OPTIMIZE(i) __attribute__((optimize(i)))
#define NO_DISCARD __attribute__((warn_unused_result))
#define PURE  __attribute__((pure))
#define SYMBOL_ALIAS(x) __attribute__((alias(STRINGIFY(x))))
#define WEAK  __attribute__((weak))
#define WARN_UNUSED __attribute__((warn_unused_result))
#endif

#define PACKED __attribute__((__packed__))
#define OPTIMIZE(i) __attribute__ ((optimize(i)))
#define ALIAS(x) SYMBOL_ALIAS(x)
#define ALIGN(x) __attribute__((aligned(x)))

#else

#error The Citrus Engine requires a G++ compatible compiler

#endif

#define FORCE_INLINE ALWAYS_INLINE
#define OPERATOR ALWAYS_INLINE

#define NO_INLINE NEVER_INLINE

#define STRINGIFY(...) __STRINGIFY__(__VA_ARGS__)
#define __STRINGIFY__(...) #__VA_ARGS__

#define __VA_ARGS_FIX__(...) __VA_ARGS__

#define NOMANGLE extern "C"

#define COMPILE_ASSERT(cond, msg) static_assert(cond, msg)

// Used for interthread communication, just volatile but whatever.
#define INTERTHREAD volatile

// Same thing as INTERTHREAD
#define MUTEX INTERTHREAD

#endif
