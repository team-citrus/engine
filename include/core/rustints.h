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


#endif