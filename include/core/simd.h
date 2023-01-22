/*
*   name: include/core/simd.h
*   origin: Citrus Engine
*   purpose: Provide SIMD abstractions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: CC0-1.0 OR LGPL-3.0-ONLY
*/

#ifndef CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_H__
#define CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_H__

#include <immintrin.h>

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

#define castpd_ps(a) _mm_castpd_ps(a)
#define castpd_si128(a) _mm_castpd_si128(a)

#define castps_pd(a) _mm_castps_pd(a)
#define castps_si128(a) _mm_castps_si128(a)

#define castsi128_pd(a) _mm_castsi128_pd(a)
#define castsi128_ps(a) _mm_castsi128_ps(a)

#define ceil_pd(a) _mm_ceil_pd(a)
#define ceil_ps(a) _mm_ceil_ps(a)
#define ceil_sd(a, b) _mm_ceil_sd(a, b)
#define ceil_ss(a, b) _mm_ceil_ss(a, b)

#define clflush(cvp) _mm_cflush(cvp)

// TODO: Add more stuff

#endif
