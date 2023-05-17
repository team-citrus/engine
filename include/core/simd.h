/*
*   name: include/core/simd.h
*   origin: Citrus Engine
*   purpose: Provide SIMD abstractions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: CC0-1.0 OR LGPL-3.0-ONLY
*/

#ifndef CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_H__
#define CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_H_

#ifdef __x86_64__
#include <x86intrin.h>

#ifdef __AVX512F__

#define _MAVX_ 512

#elif defined(__AVX2__)

#define _MAVX_ 2

#elif defined(__AVX__)

#define _MAVX_ 1

#endif

#define ROTL(x, b) (x << b) | (x >> (sizeof(x)*8 - b))
#define ROTR(x, b) (x >> b) | (x << (sizeof(x)*8 - b))

// Create a shuffle mask for shuffling an xmmreg packed with 32 bit integers
// a is xmmreg_i32[3], b is xmmreg_i32[2], etc.
#define XMM_I32_CREATE_SHUFFLE_MASK(a, b, c, d) ((a & 3) << 6) | ((b & 3) << 4) | ((c & 3) << 2) | (d & 3)

// Create a shuffle mask for shuffling an xmmreg packed with 32 bit floats
// a is xmmreg_f32[3], b is xmmreg_f32[2], etc.
#define XMM_F32_CREATE_SHUFFLE_MASK(a, b, c, d) ((a & 3) << 6) | ((b & 3) << 4) | ((c & 3) << 2) | (d & 3)

// Create a shuffle mask for shuffling a 64 bit value packed with 16 bit integers
// a is val[3], b is val[2], etc.
#define XMM_I16_CREATE_SHUFFLE_MASK(a, b, c, d) XMM_I32_CREATE_SHUFFLE_MASK(a, b, c, d)

// Create a shuffle mask for shuffling an xmmreg packed with 64 bit floats
// a is xmmreg_f64[1] = a ? xmmreg_f64[0] : xmmreg_f64[1], b is xmmreg_f64[0] = a ? xmmreg_f64[0] : xmmreg_f64[1]
#define XMM_F64_CREATE_SHUFFLE_MASK(a, b) ((a & 1) << 1) | (b & 1)

// Create a blend mask for blending an xmmreg packed with 16 bit integers
// a is xmmdest_i16[7] = a ? xmmsrc1_i16[7] : xmmsrc0_i16[7], etc.
#define XMM_I16_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h) ((a & 1) << 7) | ((b & 1) << 6) | ((c & 1) << 5) | ((d & 1) << 4) | ((e & 1) << 3) | ((f & 1) << 2) | ((g & 1) << 1) | (h & 1)

// Create a blend mask for blending an xmmreg packed with 32 bit floats
// a is xmmdest_f32[3] = a ? xmmsrc1_f32[3] : xmmsrc0_f32[3], etc.
#define XMM_F32_CREATE_BLEND_MASK(a, b, c, d) ((a & 1) << 3) | ((b & 1) << 2) | ((c & 1) << 1) | (d & 1)

// Create a blend mask for blending an xmmreg packed with 64 bit floats
// a is xmmdest_f64[1] = a ? xmmsrc1_f64[1] : xmmsrc0_f64[1], b is xmmdest_f64[0] = b ? xmmsrc1_f64[0] : xmmsrc0_f64[0]
#define XMM_F64_CREATE_BLEND_MASK(a, b) ((a & 1) << 1) | (b & 1)

typedef __m128 m128f_t;
typedef __m128d m128d_t;
typedef __m128i m128i_t;

#ifdef _MAVX_

// Create a shuffle mask for shufflng an ymmreg packed with 64 bit floats
// a is ymmreg_f64[3] = a ? ymmreg_f64[3] : ymmreg_f64[2], b is ymmreg_f64[2] = b ? ymmreg_f64[3] : ymmreg_f64[2], c is ymmreg_f64[1] = c ? ymmreg_f64[1] : ymmreg_f64[0], d is ymmreg_f64[1] = d ? ymmreg_f64[1] : ymmreg_f64[0] 
#define YMM_F64_CREATE_SHUFFLE_MASK(a, b, c, d) ((a & 1) << 3) | ((b & 1) << 2) | ((c & 1) << 1) | (d & 1)

// Create a shuffle mask for shuffling each 128 bit half of a ymmreg packed with 32 bit floats
#define YMM_F32_CREATE_SHUFFLE_MASK(a, b, c, d) XMM_F32_CREATE_SHUFFLE_MASK(a, b, c, d)

// Create a blend mask for blending an ymmreg packed with 64 bit floats
// a is ymmdest_f64[3] = a ? ymmsrc1_f64[3] : ymmsrc0_f64[3], etc.
#define YMM_F64_CREATE_BLEND_MASK(a, b, c, d) XMM_F32_CREATE_BLEND_MASK(a, b, c, d)

// Create a blend mask for blending an ymmreg packed with 32 bit floats
// a is ymmdest_f32[7] = a ? ymmsrc1_f32[7] : ymmsrc0_f32[7], etc.
#define YMM_F32_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h) XMM_I16_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h)

#if _MAVX_ >= 2

// Create a blend mask for blending an xmmreg packed with 32 bit integers
// a is xmmdest_i32[3] = a ? xmmsrc1_i32[3] : xmmsrc0_i32[3], etc.
#define XMM_I32_CREATE_BLEND_MASK(a, b, c, d) XMM_F32_CREATE_BLEND_MASK(a, b, c, d)

// Create a blend mask for blending each 128 bit half of a ymmreg packed with 16 bit ints
// a is ymmhhdest_i16[7] = a ? ymmhhsrc1_i16[7] : ymmhhsrc0_i16[7], etc.
#define YMM_I16_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h) XMM_I16_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h)

// Create a blend mask for blending an ymmreg packed with 32 bit integers
// a is ymmdest_i32[7] = a ? ymmsrc1_i32[7] : ymmsrc0_i32[7], etc.
#define YMM_I32_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h) XMM_I16_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h)

#endif

// Create a permutate mask for shuffling 2 ymmregs
// a is higher half of the dest, b is the lower half
// If bit 3 is set, the selected 128 bits will be zeroed
// If bit 1 is set, it will select from source 1, if bit 1 is clear, it will select from source 0
// If bit 0 is set, it will select the high half of the reg, if bit 0 is clear, it will select the lower half of the right
#define YMM_CREATE_PERMUTATE_MASK(a, b) ((a & 013) << 4) | (b & 013)

typedef __m256 m256f_t;
typedef __m256d m256d_t;
typedef __m256i m256i_t;

#if _MAVX_ >= 512

typedef __m512 m512f_t;
typedef __m512d m512d_t
typedef __m512i m512i_t;

#endif

#endif

// xmm/SSE intrinsics

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

#define bshl_i128(a, i) _mm_bslli_si128(a, i)
#define bshr_i128(a, i) _mm_bsrli_si128(a, i)

#define shl_i128(a, i) _mm_slli_si128(a, i)
#define shr_i128(a, i) _mm_srli_si128(a, i)
#define shl_i16(a, i) _mm_slli_epi16(a, i)
#define shr_i16(a, i) _mm_srli_epi16(a, i)
#define shl_i32(a, i) _mm_slli_epi32(a, i)
#define shr_i32(a, i) _mm_srli_epi32(a, i)
#define shl_i64(a, i) _mm_slli_epi64(a, i)
#define shr_i64(a, i) _mm_srli_epi64(a, i)

#define ceil_pd(a) _mm_ceil_pd(a)
#define ceil_ps(a) _mm_ceil_ps(a)
#define ceil_sd(a, b) _mm_ceil_sd(a, b)
#define ceil_ss(a, b) _mm_ceil_ss(a, b)

#define extract_i8(a, i) _mm_extract_epi8(a, i)
#define extract_i16(a, i) _mm_extract_epi16(a, i)
#define extract_i32(a, i) _mm_extract_epi32(a, i)
#define extract_i64(a, i) _mm_extract_epi64(a, i)

#define shuffle_i8(a, xm) _mm_shuffle_epi8(a, xm)
#define shuffle64_i8(a, m) _mm_shuffle_pi8(a, m)
#define shuffleh_i16(a, m) _mm_shufflehi_epi16(a, m)
#define shufflel_i16(a, m) _mm_shufflelo_epi16(a, m)
#define shuffle64_i16(a, m) _mm_shuffle_pi16(a, m)
#define shuffle_i32(a, m) _mm_shuffle_epi32(a, m)

#define equals_i8(a, b) _mm_cmpeq_epi8(a, b)
#define equals_i16(a, b) _mm_cmpeq_epi16(a, b)
#define equals_i32(a, b) _mm_cmpeq_epi32(a, b)
#define equals_i64(a, b) _mm_cmpeq_epi64(a, b)
#define equals_f32(a, b) _mm_cmpeq_ps(a, b)
#define equals_f64(a, b) _mm_cmpeq_pd(a, b)

#define greaterequal_i8(a, b) _mm_cmpge_epi8(a, b)
#define greaterequal_i16(a, b) _mm_cmpge_epi16(a, b)
#define greaterequal_i32(a, b) _mm_cmpge_epi32(a, b)
#define greaterequal_i64(a, b) _mm_cmpge_epi64(a, b)
#define greaterequal_f32(a, b) _mm_cmpge_ps(a, b)
#define greaterequal_f64(a, b) _mm_cmpge_pd(a, b)

#define greater_i8(a, b) _mm_cmpgt_epi8(a, b)
#define greater_i16(a, b) _mm_cmpgt_epi16(a, b)
#define greater_i32(a, b) _mm_cmpgt_epi32(a, b)
#define greater_i64(a, b) _mm_cmpgt_epi64(a, b)
#define greater_f32(a, b) _mm_cmpgt_ps(a, b)
#define greater_f64(a, b) _mm_cmpgt_pd(a, b)

#define lesserequal_i8(a, b) _mm_cmple_epi8(a, b)
#define lesserequal_i16(a, b) _mm_cmple_epi16(a, b)
#define lesserequal_i32(a, b) _mm_cmple_epi32(a, b)
#define lesserequal_i64(a, b) _mm_cmple_epi64(a, b)
#define lesserequal_f32(a, b) _mm_cmple_ps(a, b)
#define lesserequal_f64(a, b) _mm_cmple_pd(a, b)

#define lesser_i8(a, b) _mm_cmplt_epi8(a, b)
#define lesser_i16(a, b) _mm_cmplt_epi16(a, b)
#define lesser_i32(a, b) _mm_cmplt_epi32(a, b)
#define lesser_i64(a, b) _mm_cmplt_epi64(a, b)
#define lesser_f32(a, b) _mm_cmplt_ps(a, b)
#define lesser_f64(a, b) _mm_cmplt_pd(a, b)


#define notequal_i8(a, b) _mm_cmpenq_epi8(a, b)
#define notequal_i16(a, b) _mm_cmpneq_epi16(a, b)
#define notequal_i32(a, b) _mm_cmpneq_epi32(a, b)
#define notequal_i64(a, b) _mm_cmpneq_epi64(a, b)
#define notequal_f32(a, b) _mm_cmpneq_ps(a, b)
#define notequal_f64(a, b) _mm_cmpneq_pd(a, b)

#define notgreaterequal_i8(a, b) _mm_cmpnge_epi8(a, b)
#define notgreaterequal_i16(a, b) _mm_cmpnge_epi16(a, b)
#define notgreaterequal_i32(a, b) _mm_cmpnge_epi32(a, b)
#define notgreaterequal_i64(a, b) _mm_cmpnge_epi64(a, b)
#define notgreaterequal_f32(a, b) _mm_cmpnge_ps(a, b)
#define notgreaterequal_f64(a, b) _mm_cmpnge_pd(a, b)

#define notgreater_i8(a, b) _mm_cmpngt_epi8(a, b)
#define notgreater_i16(a, b) _mm_cmpngt_epi16(a, b)
#define notgreater_i32(a, b) _mm_cmpngt_epi32(a, b)
#define notgreater_i64(a, b) _mm_cmpngt_epi64(a, b)
#define notgreater_f32(a, b) _mm_cmpngt_ps(a, b)
#define notgreater_f64(a, b) _mm_cmpngt_pd(a, b)
 
#define notlessequal_i8(a, b) _mm_cmpnle_epi8(a, b)
#define notlessequal_i16(a, b) _mm_cmpnle_epi16(a, b)
#define notlessequal_i32(a, b) _mm_cmpnle_epi32(a, b)
#define notlessequal_i64(a, b) _mm_cmpnle_epi64(a, b)
#define notlessequal_f32(a, b) _mm_cmpnle_ps(a, b)
#define notlessequal_f64(a, b) _mm_cmpnle_pd(a, b)

#define notless_i8(a, b) _mm_cmpnlt_epi8(a, b)
#define notless_i16(a, b) _mm_cmpnlt_epi16(a, b)
#define notless_i32(a, b) _mm_cmpnlt_epi32(a, b)
#define notless_i64(a, b) _mm_cmpnlt_epi64(a, b)
#define notless_f32(a, b) _mm_cmpnlt_ps(a, b)
#define notless_f64(a, b) _mm_cmpnlt_pd(a, b)

#define extractbools_i8(a) _mm_movemask_epi8(a)
#define movemask_f32(a) _mm_movemask_ps(a)
#define movemask_f64(a) _mm_movemask_pd(a)


#ifndef _MAVX_

#define shuffle_f32(a, m) _mm_shuffle_ps(a, a, m)
#define shuffle_f64(a, m) _mm_shuffle_pd(a, a, m)

#else 

#define shuffle_f32(a, m) _mm_permute_ps(a, m)
#define shuffle_f64(a, m) _mm_permute_pd(a, m)

#endif

#define shufflem_f64(a, b, m) _mm_shuffle_pd(a, b, m)
#define shufflem_f32(a, b, m) _mm_shuffle_ps(a, b, m)

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

#define horizadd_i16(a, b) _mm_hadd_epi16(a, b)
#define horizadd_i32(a, b) _mm_hadd_epi32(a, b)
#define horizadd_f32(a, b) _mm_hadd_ps(a, b)
#define horizadd_f64(a, b) _mm_hadd_pd(a, b)

#define horizsub_i16(a, b) _mm_hsub_epi16(a, b)
#define horizsub_i32(a, b) _mm_hsub_epi32(a, b)
#define horizsub_f32(a, b) _mm_hsub_ps(a, b)
#define horizsub_f64(a, b) _mm_hsub_pd(a, b)

#define load_mf64(ptr) _mm_load_pd(ptr)
#define load_mf32(ptr) _mm_load_ps(ptr)
#define load_f64(ptr) _mm_load_sd(ptr)
#define load_f32(ptr) _mm_load_ss(ptr)
#define load_i128(ptr) _mm_load_si128(ptr)

#define uload_mf64(ptr) _mm_loadu_pd(ptr)
#define uload_mf32(ptr) _mm_loadu_ps(ptr)
#define uload_f64(ptr) load_f64(ptr)
#define uload_f32(ptr) load_f32(ptr)
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

// ymm/AVX intrinsics

#ifdef _MAVX_

#define add256_f64(a, b) _mm256_add_pd(a, b)
#define add256_f32(a, b) _mm256_add_ps(a, b)

#define sub256_f64(a, b) _mm256_sub_pd(a, b)
#define sub256_f32(a, b) _mm256_sub_ps(a, b)

#define mul256_f64(a, b) _mm256_mul_pd(a, b)
#define mul256_f32(a, b) _mm256_mul_ps(a, b)

#define div256_f64(a, b) _mm256_div_pd(a, b)
#define div256_f32(a, b) _mm256_div_ps(a, b)

#define and256_f64(a, b) _mm256_and_pd(a, b)
#define and256_f32(a, b) _mm256_and_ps(a, b)

#define andnot256_f64(a, b) _mm256_andnot_pd(a, b)
#define andnot256_f32(a, b) _mm256_andnot_ps(a, b)

#define or256_f64(a, b) _mm256_or_pd(a, b)
#define or256_f32(a, b) _mm256_or_ps(a, b)

#define xor256_f64(a, b) _mm256_xor_pd(a, b)
#define xor256_f32(a, b) _mm256_xor_ps(a, b)

#define blend256_f64(a, b, m) _mm256_blend_pd(a, b, m)
#define blend256_f32(a, b, m) _mm256_blend_ps(a, b, m)

#define blendv256_f64(a, b, mv) _mm256_blendv_pd(a, b, mv)
#define blendv256_f32(a, b, mv) _mm256_blendv_ps(a, b, mv)

#if _MAVX_ >= 2

#define add256_i8(a, b) _mm256_add_epi8(a, b)
#define add256_i16(a, b) _mm256_add_epi16(a, b)
#define add256_i32(a, b) _mm256_add_epi32(a, b)
#define add256_i64(a, b) _mm256_add_epi64(a, b)

#define sub256_i8(a, b) _mm256_sub_epi8(a, b)
#define sub256_i16(a, b) _mm256_sub_epi16(a, b)
#define sub256_i32(a, b) _mm256_sub_epi32(a, b)
#define sub256_i64(a, b) _mm256_sub_epi64(a, b)

#define mul256_i8(a, b) _mm256_mul_epi8(a, b)
#define mul256_i16(a, b) _mm256_mul_epi16(a, b)
#define mul256_i32(a, b) _mm256_mul_epi32(a, b)
#define mul256_i64(a, b) _mm256_mul_epi64(a, b)

#define shl256_i128(a, i) _mm256_bslli_epi128(a, i)
#define shr256_i128(a, i) _mm256_bsrli_epi128(a, i)

#define shl256_i16(a, i) _mm256_slli_epi16(a, i)
#define shr256_i16(a, i) _mm256_srli_epi16(a, i)
#define shl256_i32(a, i) _mm256_slli_epi32(a, i)
#define shr256_i32(a, i) _mm256_srli_epi32(a, i)
#define shl256_i64(a, i) _mm256_slli_epi64(a, i)
#define shr256_i64(a, i) _mm256_srli_epi64(a, i)

#define shlv256_i16(a, iv) _mm256_sll_epi16(a, iv)
#define shrv256_i16(a, iv) _mm256_srl_epi16(a, iv)
#define shlv256_i32(a, iv) _mm256_sll_epi32(a, iv)
#define shrv256_i32(a, iv) _mm256_srl_epi32(a, iv)
#define shlv256_i64(a, iv) _mm256_sll_epi64(a, iv)
#define shrv256_i64(a, iv) _mm256_srl_epi64(a, iv)

#define and_i256(a, b) _mm256_and_si256(a, b)
#define andnot_i256(a, b) _mm256_andnot_si256(a, b)
#define or_i256(a, b) _mm256_or_si256(a, b)
#define xor_i256(a, b) _mm256_xor_si256(a, b)

#define blend256_i16(a, b, i) _mm256_blend_epi16(a, b, i)
#define blend256_i32(a, b, i) _mm256_blend_epi32(a, b, i) 
#define blendv256_i8(a, b, mv) _mm256_blendv_epi8(a, b, mv)

#define horizadd256_i16(a, b) _mm256_hadd_epi16(a, b)
#define horizadd256_i32(a, b) _mm256_hadd_epi32(a, b)

#define horizsub256_i16(a, b) _mm256_hsub_epi16(a, b)
#define horizsub256_i32(a, b) _mm256_hsub_epi32(a, b)

#define ibroadcast_i8(a) _mm_broadcastb_epi8(a)
#define ibroadcast_i16(a) _mm_broadcastw_epi16(a)
#define ibroadcast_i32(a) _mm_broadcastd_epi32(a)
#define ibroadcast_i64(a) _mm_broadcastq_epi64(a)
#define ibroadcast_f32(a) _mm_broadcastss_ps(a)
#define ibroadcast_f64(a) *(m128d_t*)&ibroadcast_i64(*(m128i_t*)&a) // It ain't pretty but it should work

#define ibroadcast256_i8(a) _mm256_broadcastb_epi8(a)
#define ibroadcast256_i16(a) _mm256_broadcastw_epi16(a)
#define ibroadcast256_i32(a) _mm256_broadcastd_epi32(a)
#define ibroadcast256_i64(a) _mm256_broadcastq_epi64(a)

#endif

#define shuffle256_f64(a, m) _mm256_permute_pd(a, m)
#define shufflem256_f64(a, b, m) _mm256_shuffle_pd(a, b, m)
#define shuffle256_f32(a, m) _mm256_permute_ps(a, m)
#define shufflem256_f32(a, b, m) _mm256_shuffle_ps(a, b, m)

#define permute256_f64(a, b, m) _mm256_permute2f128_pd(a, b, m)
#define permute256_f32(a, b, m) _mm256_permute2f128_ps(a, b, m)
#define permute_i256(a, b, m) _mm256_permute2f128_si256(a, b, m)

#define horizadd256_f64(a, b) _mm256_hadd_pd(a, b)
#define horizadd256_f32(a, b) _mm256_hadd_ps(a, b)

#define horizsub256_f64(a, b) _mm256_hsub_pd(a, b)
#define horizsub256_f32(a, b) _mm256_hsub_ps(a, b)

#define broadcast256_i8(i) _mm256_set1_epi8(i)
#define broadcast256_i16(i) _mm256_set1_epi16(i)
#define broadcast256_i32(i) _mm256_set1_epi32(i)
#define broadcast256_i64(i) _mm256_set1_epi64x(i)
#define broadcast256_f32(f) _mm256_broadcast_ss(&f)
#define broadcast256_f64(f) _mm256_broadcast_sd(&f)

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

#if _MAVX_ >= 512

#define load_i512(ptr) _mm512_load_si512(ptr)

#define store_i512(dest, src) _mm512_store_si512(dest, src)

// TODO: AVX512

#endif

#endif

// Non-SIMD intrinsics

#define spinlock_pause() _mm_pause()

#define crc32_u8(crc, u8) _mm_crc32_u8(crc, u8)
#define crc32_u16(crc, u16) _mm_crc32_u16(crc, u16)
#define crc32_u32(crc, u32) _mm_crc32_u32(crc, u32)
#define crc32_u64(crc, u64) _mm_crc32_u64(crc, u64)

// TODO: Add more stuff

// Copy from 16 byte aligned address src b 16 byte blocks to 16 byte aligned address dest
OPERATOR void xmm_memcpy(void *dest, void *src, size_t b)
{
	m128i_t *vdest = dest;
	m128i_t *vsrc = src;
	for(int i = 0; i < b; i++) store_i128(&(vdest[i]), load_i128(&(vsrc[i])));
}

// Copy from 16 byte aligned address src b 16 byte blocks to 16 byte aligned address dest in a manor that is safe on overlap
OPERATOR void xmm_memmove(void *dest, void *src, size_t b)
{
	m128i_t *vdest = dest;
	m128i_t *vsrc = src;
	if(dest == src)
		return;
	
	if((uintptr_t)dest > (uintptr_t)src && (uintptr_t)dest < (uintptr_t)src + (b * 16))
	{
		for(int i = b - 1; i >= 0; i--) store_i128(&(vdest[i]), load_i128(&(vsrc[i])));
	}
	else
		xmm_memcpy(dest, src, b);
}

// memset 16 byte aligned array in 16 byte blocks
OPERATOR void xmm_memset(void *ptr, unsigned char c, size_t b)
{
	m128i_t val;
	m128i_t *vptr = ptr;
	val = broadcast_i8(c);
	for(int i = 0; i < b; i++, vptr++) store_i128(vptr, val);
}

#ifdef _MAVX_

// Copy from 32 byte aligned address src b 32 byte blocks to 32 byte aligned address dest
OPERATOR void ymm_memcpy(void *dest, void *src, size_t b)
{
	m256i_t *vdest = dest;
	m256i_t *vsrc = src;
	for(int i = 0; i < b; i++) store_i256(&(vdest[i]), load_i256(&(vsrc[i])));
}

// memset 32 byte aligned array in 32 byte blocks
OPERATOR void ymm_memset(void *ptr, unsigned char c, size_t b)
{
	m256i_t val;
	m256i_t *vptr = ptr;
	val = broadcast256_i8(c);
	for(int i = 0; i < b; i++, vptr++) store_i256(vptr, val);
}

// Copy from 32 byte aligned address src b 32 byte blocks to 32 byte aligned address dest in a manor that is safe on overlap
OPERATOR void ymm_memmove(void *dest, void *src, size_t b)
{
	m256i_t *vdest = dest;
	m256i_t *vsrc = src;
	if(dest == src)
		return;
	
	if((uintptr_t)dest > (uintptr_t)src && (uintptr_t)dest < (uintptr_t)src + (b * 16))
	{
		for(int i = b - 1; i >= 0; i--) store_i256(&(vdest[i]), load_i256(&(vsrc[i])));
	}
	else
		ymm_memcpy(dest, src, b);
}

#else

// Copy from 32 byte aligned address src b 32 byte blocks to 32 byte aligned address dest
#define ymm_memcpy(dest, src, b) xmm_memcpy(dest, src, b * 2)

// memset 32 byte aligned array in 32 byte blocks
#define ymm_memset(ptr, c, b) xmm_memcpy(ptr, c, b * 2)

// Copy from 32 byte aligned address src b 32 byte blocks to 32 byte aligned address dest in a manor that is safe on overlap
#define ymm_memmove(dest, src, b) xmm_memmove(dest, src, b * 2)

#endif

#if defined(_MAVX_) && _MAVX_ >= 512

// Copy from 64 byte aligned address src b 64 byte blocks to 64 byte aligned address dest
OPERATOR void zmm_memcpy(void *dest, void *src, size_t b)
{
	m512i_t *vdest = dest;
	m512i_t *vsrc = src;
	for(size_t i = 0; i < b; i++) store_i512(&(vdest[i]), load_i512(&(vsrc[i])));
}

// Copy from 64 byte aligned address src b 64 byte blocks to 64 byte aligned address dest in a manor that is safe on overlap
OPERATOR void zmm_memmove(void *dest, void *src, size_t b)
{
	m512i_t *vdest = dest;
	m512i_t *vsrc = src;
	if(dest == src)
		return;
	
	if((uintptr_t)dest > (uintptr_t)src && (uintptr_t)dest < (uintptr_t)src + (b * 16))
	{
		for(int i = b - 1; i >= 0; i--) store_i512(&(vdest[i]), load_i512(&(vsrc[i])));
	}
	else
		zmm_memcpy(dest, src, b);
}
											 
#else
											 
// Copy from 64 byte aligned address src b 64 byte blocks to 64 byte aligned address dest   
#define zmm_memcpy(dest, src, b) ymm_memcpy(dest, src, b * 2)

// memset 64 byte aligned array in 64 byte blocks
#define zmm_memset(ptr, c, b) ymm_memset(ptr, c, b * 2)
 
// Copy from 64 byte aligned address src b 64 byte blocks to 64 byte aligned address dest in a manor that is safe on overlap
#define zmm_memmove(ptr, dest, b) ymm_memmove(ptr, dest, b * 2)

#endif

#else

#define spinlock_pause() 

#if defined(__aarch64__)

#include <arm_neon.h>

// Inherit the names from AMD64 'cause why make our lives harder?

// Copy from 16 byte aligned address src b 16 byte blocks to 16 byte aligned address dest
OPERATOR void xmm_memcpy(void *dest, void *src, size_t b)
{
	uint64_t *rdest = dest;
	uint64_t *rsrc = src;

	for(size_t i = 0; i < b; i++)
		vst1q_u64(&(rdest[i * 2]), vld1q_u64(&(src[i * 2])));
}

// Copy from 16 byte aligned address src b 16 byte blocks to 16 byte aligned address dest in a manor that is safe on overlap
OPERATOR void xmm_memmove(void *dest, void *src, size_t b)
{
	uint64_t *rdest = dest;
	uint64_t *rsrc = src;

	if(dest == src)
		return;
	
	if((uintptr_t)dest > (uintptr_t)src && (uintptr_t)dest < (uintptr_t)src + (b * 16))
	{
		for(int i = b - 1; i >= 0; i--) vst1q_u64(&(rdest[i * 2]), vld1q_u64(&(src[i * 2])));
	}
	else
		xmm_memcpy(dest, src, b);
}

// memset 16 byte aligned array in 16 byte blocks
OPERATOR void xmm_memset(void *ptr, unsigned char c, size_t b)
{
	uint64_t *rptr = ptr;
	uint64x2_t val = vld1q_u64({0ull, 0ull});

	for(size_t i = 0; i < b; i++, rptr += 2) vst1q_u64(rptr, val);
}

// Copy from 32 byte aligned address src b 32 byte blocks to 32 byte aligned address dest
#define ymm_memcpy(dest, src, b) xmm_memcpy(dest, src, b * 2)

// Copy from 16 byte aligned address src b 16 byte blocks to 16 byte aligned address dest in a manor that is safe on overlap
#define ymm_memmove(dest, src, b) xmm_memmove(dest, src, b * 2)

// memset 32 byte aligned array in 32 byte blocks
#define ymm_memset(ptr, c, b) xmm_memset(ptr, c, b * 2)

// Copy from 64 byte aligned address src b 64 byte blocks to 64 byte aligned address dest   
#define zmm_memcpy(dest, src, b) ymm_memcpy(dest, src, b * 2)

// memset 64 byte aligned array in 64 byte blocks
#define zmm_memset(ptr, c, b) ymm_memset(ptr, c, b * 2)

#elif defined(__i386__)

#error x86/x86-32/i*86 is not supported by the Citrus Engine! The Citrus Engine only supports 64 bit targets!

#elif defined(__arm__)

#error 32-bit Arm is not supported by the Citrus Engine! The Citrus Engine only supports 64 bit targets!

#else

#error Unsupported CPU architecture!

#endif

#endif

#endif