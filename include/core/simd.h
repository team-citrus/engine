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

// TODO: Add more stuff

#endif