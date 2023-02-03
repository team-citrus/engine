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

#define abs_epi16(a) _mm_abs_epi16(a)
#define abs_epi32(a) _mm_abs_epi32(a)
#define abs_epi8(a) _mm_abs_epi8(a)

#define add_epi8(a, b) _mm_add_epi8(a, b)
#define add_epi16(a, b) _mm_add_epi16(a, b)
#define add_epi32(a, b) _mm_add_epi32(a, b)
#define add_epi64(a, b) _mm_add_epi64(a, b)
#define add_pd(a, b) _mm_add_pd(a, b)
#define add_ps(a, b) _mm_add_ps(a, b)
#define add_sd(a, b) _mm_add_sd(a, b)

#define adds_epi8(a, b) _mm_adds_epi8(a, b)
#define adds_epi16(a, b) _mm_adds_epi16(a, b)
#define adds_epi32(a, b) _mm_adds_epi32(a, b)
#define adds_epi64(a, b) _mm_adds_epi64(a, b)

#define addsub_pd(a, b) _mm_addsub_pd(a, b)
#define addsub_ps(a, b) _mm_addsub_ps(a, b)
#define addsub_sd(a, b) _mm_addsub_sd(a, b)

#define alignr_epi8(a, b, i) _mm_alignr_epi8(a, b, i)
#define alignr_pi8(a, b, i) _mm_alignr_pi8(a, b, i)

#define and_pd(a, b) _mm_and_pd(a, b)
#define and_ps(a, b) _mm_and_ps(a, b)
#define and_si128(a, b) _mm_and_si128(a, b)

#define andnot_pd(a, b) _mm_andnot_pd(a, b)
#define andnot_ps(a, b) _mm_andnot_ps(a, b)
#define andnot_si128(a, b) _mm_andnot_si128(a, b)

#define avg_epu8(a, b) _mm_avg_epu8(a, b)
#define avg_epu16(a, b) _mm_avg_epu16(a, b)

#define avg_pu8(a, b) _mm_avg_pu8(a, b)
#define avg_pu16(a, b) _mm_avg_pu16(a, b)

#define blend_epi16(a, b, i) _mm_blend_epi16(a, b, i)
#define blend_pd(a, b, i) _mm_blend_pd(a, b, i)
#define blend_ps(a, b, i) _mm_blend_ps(a, b, i)

#define blendv_epi8(a, b, m) _mm_blendv_epi8(a, b, m)
#define blendv_pd(a, b, m) _mm_blendv_pd(a, b, m)
#define blendv_ps(a, b, m) _mm_blendv_ps(a, b, m)

#define bslli_si128(a, i) _mm_bslli_si128(a, i)
#define bsrli_si128(a, i) _mm_bsrli_si128(a, i)

#define ceil_pd(a) _mm_ceil_pd(a)
#define ceil_ps(a) _mm_ceil_ps(a)
#define ceil_sd(a, b) _mm_ceil_sd(a, b)
#define ceil_ss(a, b) _mm_ceil_ss(a, b)

#define clflush(cvp) _mm_cflush(cvp)

#define crc32_u8(crc, u8) _mm_crc32_u8(crc, u8)
#define crc32_u16(crc, u16) _mm_crc32_u16(crc, u16)
#define crc32_u32(crc, u32) _mm_crc32_u32(crc, u32)
#define crc32_u64(crc, u64) _mm_crc32_u64(crc, u64)

#define extract_i8(a, i) _mm_extract_epi8(a, i)
#define extract_i16(a, i) _mm_extract_epi16(a, i)
#define extract_i32(a, i) _mm_extract_epi32(a, i)
#define extract_i64(a, i) _mm_extract_epi64(a, i)
#define extract_f32(a, i) _mm_extract_ps(a, i)

#define sub_epi8(a, b) _mm_sub_epi8(a, b)
#define sub_epi16(a, b) _mm_sub_epi16(a, b)
#define sub_epi32(a, b) _mm_sub_epi32(a, b)
#define sub_epi64(a, b) _mm_sub_epi64(a, b)
#define sub_pd(a, b) _mm_sub_pd(a, b)
#define sub_ps(a, b) _mm_sub_ps(a, b)
#define sub_sd(a, b) _mm_sub_sd(a, b)

#define mul_pd(a, b) _mm_mul_pd(a, b)
#define mul_ps(a, b) _mm_mul_ps(a, b)
#define mul_sd(a, b) _mm_mul_sd(a, b)

#define div_pd(a, b) _mm_div_pd(a, b)
#define div_ps(a, b) _mm_div_ps(a, b)
#define div_sd(a, b) _mm_div_sd(a, b)

#define or_pd(a, b) _mm_or_pd(a, b)
#define or_ps(a, b) _mm_or_ps(a, b)
#define or_si128(a, b) _mm_or_si128(a, b)

#define xor_pd(a, b) _mm_xor_pd(a, b)
#define xor_ps(a, b) _mm_xor_ps(a, b)
#define xor_si128(a, b) _mm_xor_si128(a, b)

#define epi8_i16(a) _mm_cvtepi8_epi16(a)
#define epi8_i32(a) _mm_cvtepi8_epi32(a)
#define epi8_i64(a) _mm_cvtepi8_epi64(a)

#define epi16_i32(a) _mm_cvtepi16_epi32(a)
#define epi16_i64(a) _mm_cvtepi16_epi64(a)

#define epi32_i64(a) _mm_cvtepi32_epi64(a)

#define epu8_i16(a) _mm_cvtepu8_epi16(a)
#define epu8_i32(a) _mm_cvtepu8_epi32(a)
#define epu8_i64(a) _mm_cvtepu8_epi64(a)

#define epu16_i32(a) _mm_cvtepu16_epi32(a)
#define epu16_i64(a) _mm_cvtepu16_epi64(a)

#define epu32_i64(a) _mm_cvtepu32_epi64(a)

#define get_f64(a) _mm_cvtsd_f64(a)
#define get_i32(a) _mm_cvtsi128_si32(a)
#define get_i64(a) _mm_cvtsi128_si64(a)

#define mov_i32(i) _mm_cvtsi32_si128(i)
#define mov_i64(i) _mm_cvtsi64_si128(i)
#define mov_pd(ptr) _mm_load_pd(ptr)
#define mov_ps(ptr) _mm_load_ps(ptr)
#define mov_sd(ptr) _mm_load_sd(ptr)
#define mov_ss(ptr) _mm_load_ss(ptr)
#define mov_s128(ptr) _mm_load_si128(ptr)

// TODO: Add more stuff

#endif
