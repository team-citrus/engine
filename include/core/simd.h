/*
*   name: include/core/simd.h
*   origin: Citrus Engine
*   purpose: Provide SIMD abstractions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: CC0-1.0 OR LGPL-3.0-ONLY
*/

#ifndef CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_H__
#define CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_H__

#include <x86intrin.h>

typedef __m128 m128f_t;
typedef __m128d m128d_t;
typedef __m128i m128i_t;
typedef __m256 m256f_t;
typedef __m256d m256d_t;
typedef __m256i m256i_t;

#define abs_i16(a) _mm_abs_epi16(a)
#define abs_i32(a) _mm_abs_epi32(a)
#define abs_i8(a) _mm_abs_epi8(a)

#define add_i8(a, b) _mm_add_epi8(a, b)
#define add_i16(a, b) _mm_add_epi16(a, b)
#define add_i32(a, b) _mm_add_epi32(a, b)
#define add_i64(a, b) _mm_add_epi64(a, b)
#define add_mf64(a, b) _mm_add_pd(a, b)
#define add_mf32(a, b) _mm_add_ps(a, b)
#define add_f64(a, b) _mm_add_sd(a, b)
#define add_f32(a, b) _mm_add_ss(a, b)

#define adds_i8(a, b) _mm_adds_epi8(a, b)
#define adds_i16(a, b) _mm_adds_epi16(a, b)
#define adds_i32(a, b) _mm_adds_epi32(a, b)
#define adds_i64(a, b) _mm_adds_epi64(a, b)

#define addsub_mf64(a, b) _mm_addsub_pd(a, b)
#define addsub_mf32(a, b) _mm_addsub_ps(a, b)
#define addsub_f64(a, b) _mm_addsub_sd(a, b)

#define and_f64(a, b) _mm_and_pd(a, b)
#define and_f32(a, b) _mm_and_ps(a, b)
#define and_i128(a, b) _mm_and_si128(a, b)

#define andnot_f64(a, b) _mm_andnot_pd(a, b)
#define andnot_f32(a, b) _mm_andnot_ps(a, b)
#define andnot_i128(a, b) _mm_andnot_si128(a, b)

#define average_u8(a, b) _mm_avg_epu8(a, b)
#define average_u16(a, b) _mm_avg_epu16(a, b)

#define raverage_u8(a, b) _mm_avg_pu8(a, b)
#define raverage_u16(a, b) _mm_avg_pu16(a, b)

#define blend_i16(a, b, i) _mm_blend_epi16(a, b, i)
#define blend_f64(a, b, i) _mm_blend_pd(a, b, i)
#define blend_f32(a, b, i) _mm_blend_ps(a, b, i)

#define blendv_i8(a, b, m) _mm_blendv_epi8(a, b, m)
#define blendv_f64(a, b, m) _mm_blendv_pd(a, b, m)
#define blendv_f32(a, b, m) _mm_blendv_ps(a, b, m)

#define bslli_i128(a, i) _mm_bslli_si128(a, i)
#define bsrli_i128(a, i) _mm_bsrli_si128(a, i)

#define ceil_pd(a) _mm_ceil_pd(a)
#define ceil_ps(a) _mm_ceil_ps(a)
#define ceil_sd(a, b) _mm_ceil_sd(a, b)
#define ceil_ss(a, b) _mm_ceil_ss(a, b)

#define extract_i8(a, i) _mm_extract_epi8(a, i)
#define extract_i16(a, i) _mm_extract_epi16(a, i)
#define extract_i32(a, i) _mm_extract_epi32(a, i)
#define extract_i64(a, i) _mm_extract_epi64(a, i)
#define extract_f32(a, i) _mm_extract_ps(a, i)

#define broadcast_i8(a) _mm_set1_epi8(a)
#define broadcast_i16(a) _mm_set1_epi16(a)
#define broadcast_i32(a) _mm_set1_epi32(a)
#define broadcast_i64(a) _mm_set1_epi64x(a)
#define broadcast_f64(a) _mm_set1_pd(a)
#define broadcast_f32(a) _mm_set1_ps(a)

#define sub_i8(a, b) _mm_sub_epi8(a, b)
#define sub_i16(a, b) _mm_sub_epi16(a, b)
#define sub_i32(a, b) _mm_sub_epi32(a, b)
#define sub_i64(a, b) _mm_sub_epi64(a, b)
#define sub_mf64(a, b) _mm_sub_pd(a, b)
#define sub_mf32(a, b) _mm_sub_ps(a, b)
#define sub_f64(a, b) _mm_sub_sd(a, b)

#define mul_mf64(a, b) _mm_mul_pd(a, b)
#define mul_mf32(a, b) _mm_mul_ps(a, b)
#define mul_f64(a, b) _mm_mul_sd(a, b)

#define div_mf64(a, b) _mm_div_pd(a, b)
#define div_mf32(a, b) _mm_div_ps(a, b)
#define div_f64(a, b) _mm_div_sd(a, b)

#define or_f64(a, b) _mm_or_pd(a, b)
#define or_f32(a, b) _mm_or_ps(a, b)
#define or_i128(a, b) _mm_or_si128(a, b)

#define xor_f64(a, b) _mm_xor_pd(a, b)
#define xor_f32(a, b) _mm_xor_ps(a, b)
#define xor_i128(a, b) _mm_xor_si128(a, b)

#define load_mf64(ptr) _mm_load_pd(ptr)
#define load_mf32(ptr) _mm_load_ps(ptr)
#define load_f64(ptr) _mm_load_sd(ptr)
#define load_f32(ptr) _mm_load_ss(ptr)
#define load_i128(ptr) _mm_load_si128(ptr)

#define uload_mf64(ptr) _mm_loadu_pd(ptr)
#define uload_mf32(ptr) _mm_loadu_ps(ptr)
#define uload_f64(ptr) load_sd(ptr)
#define uload_f32(ptr) load_ss(ptr)
#define uload_i128(ptr) _mm_lddqu_si128(ptr)

#define store_mf64(dest, src) _mm_store_pd(dest, src)
#define store_mf32(dest, src) _mm_store_ps(dest, src)
#define store_f64(dest, src) _mm_store_sd(dest, src)
#define store_f32(dest, src) _mm_store_ss(dest, src)
#define store_i128(dest, src) _mm_store_si128(dest, src)

#define ustore_mf64(dest, src) _mm_storeu_pd(dest, src)
#define ustore_mf32(dest, src) _mm_storeu_ps(dest, src)
#define ustore_f64(dest, src) store_sd(dest, src)
#define ustore_f32(dest, src) store_ss(dest, src)
#define ustore_i128(dest, src) _mm_storeu_si128(dest, src)

// ymm intrinsics

#define load256_f64(ptr) _mm256_load_pd(ptr)
#define load256_f32(ptr) _mm256_load_ps(ptr)
#define load_i256(src) _mm256_load_si256(src)

#define uload256_f64(ptr) _mm256_loadu_pd(ptr)
#define uload256_f32(ptr) _mm256_loadu_ps(ptr)
#define uload_i256(ptr) _mm256_lddqu_si256(ptr)

#define store256_f64(dest, src) _mm256_store_pd(dest, src)
#define store256_f32(dest, src) _mm256_store_ps(dest, src)
#define store_i256(dest, src) _mm256_store_si256(dest, src)

#define ustore256_f64(dest, src) _mm256_storeu_pd(dest, src)
#define ustore256_f32(dest, src) _mm256_storeu_ps(dest, src)
#define ustore_i256(dest, src) _mm256_storeu_si256(dest, src)

// Non-SIMD intrinsics

#define spinlock_pause() _mm_pause()

#define crc32_u8(crc, u8) _mm_crc32_u8(crc, u8)
#define crc32_u16(crc, u16) _mm_crc32_u16(crc, u16)
#define crc32_u32(crc, u32) _mm_crc32_u32(crc, u32)
#define crc32_u64(crc, u64) _mm_crc32_u64(crc, u64)

// TODO: Add more stuff

#endif
