/*
 *   name: include/core/rustints.h
 *   origin: Citrus Engine
 *   purpose: Provide Rust style int types
 *   author: https://github.com/ComradeYellowCitrusFruit
 *   license: CC0-1.0 OR LGPL-3.0-ONLY
 */

#ifndef CITRUS_ENGINE_RUST_INTEGER_TYPES_H__
#define CITRUS_ENGINE_RUST_INTEGER_TYPES_H__

#include <cstdint>
#include <cstdlib>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef size_t usize;
typedef long long isize; // ssize_t is only defined in *nix, however we can assume long long will be the signed size_t integer, as we are definitly in 64 bits

typedef float f32;
typedef double f64;

#define I8_MAX (i8)0x7F
#define I16_MAX (i16)0x7FFF
#define I32_MAX (i32)0x7FFFFFFF
#define I64_MAX (i64)0x7FFFFFFFFFFFFFFF

#define I8_MIN (i8)0x80
#define I16_MIN (i16)0x8000
#define I32_MIN (i32)0x80000000
#define I64_MIN (i64)0x8000000000000000

#define U8_MAX (u8)0xFF
#define U16_MAX (u16)0xFFFF
#define U32_MAX (u32)0xFFFFFFFF
#define U64_MAX (u64)0xFFFFFFFFFFFFFFFF

#define U8_MIN (u8)0
#define U16_MIN (u16)0
#define U32_MIN (u32)0
#define U64_MIN (u64)0

#ifdef __cplusplus

namespace engine
{

    template <typename T>
    T max(T a, T b)
    {
        return (a > b) ? a : b;
    }

    template <typename T>
    T min(T a, T b)
    {
        return (a < b) ? a : b;
    }

    template <typename T>
    T abs(T a);

    u8 abs(u8 a)
    {
        return a;
    }

    u16 abs(u16 a)
    {
        return a;
    }

    u32 abs(u32 a)
    {
        return a;
    }

    u64 abs(u64 a)
    {
        return a;
    }

    i8 abs(i8 a)
    {
        return (a & 0x80) ? ~a + 1 : a;
    }

    i16 abs(i16 a)
    {
        return (a & 0x8000) ? ~a + 1 : a;
    }

    i32 abs(i32 a)
    {
        return (a & 0x80000000) ? ~a + 1 : a;
    }

    i64 abs(i64 a)
    {
        return (a & 0x8000000000000000) ? ~a + 1 : a;
    }

    f32 abs(f32 a)
    {
        return (a < 0.0f) ? a * -1.0f : a;
    }

    f64 abs(f64 a)
    {
        return (a < 0.0) ? a * -1.0 : a;
    }

    template <typename T>
    T pow(T a, int power)
    {
        return (power) ? a * pow(a, power - 1) : (T)1;
    }

    // TODO: sqrt and isqrt

}

#endif

#endif