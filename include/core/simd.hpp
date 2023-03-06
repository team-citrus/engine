/*
*   name: include/core/simd.h
*   origin: Citrus Engine
*   purpose: Provide SIMD abstractions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: CC0-1.0 OR LGPL-3.0-ONLY
*/

#ifndef CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_HPP__
#define CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_HPP__

#include "core/rustints.h"
#include "core/simd.h"

#ifdef __x86_64__

// TODO: Make this actually useful

class f32x4
{
    public:
    m128f_t packed;

    f32x4()
    {
        packed = broadcast_f32(0.0f);
    }

    f32x4(m128f_t p)
    {
        packed = p;
    }

    f32x4(f32 f)
    {
        packed = broadcast_f32(f);
    }

    f32x4(f32 *f)
    {
        packed = uload_mf32(f);
    }

    f32x4 operator=(m128f_t p)
    {
        packed = p;
    }

    f32x4 operator=(f32 f)
    {
        packed = broadcast_f32(f);
    }

    f32x4 operator=(f32 *f)
    {
        packed = uload_mf32(f);
    }

    f32x4 operator+(f32x4 &f)
    {
        return f32x4(add_mf32(packed, f.packed));
    }

    f32x4 operator+(m128f_t f)
    {
        return f32x4(add_mf32(packed, f));
    }

    f32x4 operator+(f32 f)
    {
        return *this + broadcast_f32(f);
    }

    f32x4 operator-(f32x4 &f)
    {
        return f32x4(sub_mf32(packed, f.packed));
    }

    f32x4 operator-(m128f_t f)
    {
        return f32x4(sub_mf32(packed, f));
    }

    f32x4 operator-(f32 f)
    {
        return *this - broadcast_f32(f);
    }

    f32x4 operator*(f32x4 &f)
    {
        return f32x4(mul_mf32(packed, f.packed));
    }

    f32x4 operator*(m128f_t f)
    {
        return f32x4(mul_mf32(packed, f));
    }

    f32x4 operator*(f32 f)
    {
        return *this * broadcast_f32(f);
    }

    f32x4 operator/(f32x4 &f)
    {
        return f32x4(div_mf32(packed, f.packed));
    }

    f32x4 operator/(m128f_t f)
    {
        return f32x4(div_mf32(packed, f));
    }

    f32x4 operator/(f32 f)
    {
        return *this / broadcast_f32(f);
    }

    f32x4 operator&(f32x4 &f)
    {
        return f32x4(and_f32(packed, f.packed));
    }

    f32x4 operator&(m128f_t f)
    {
        return f32x4(and_f32(packed, f));
    }

    f32x4 operator&(f32 f)
    {
        return *this & broadcast_f32(f);
    }

    f32x4 operator^(f32x4 &f)
    {
        return f32x4(xor_f32(packed, f.packed));
    }

    f32x4 operator^(m128f_t f)
    {
        return f32x4(xor_f32(packed, f));
    }

    f32x4 operator^(f32 f)
    {
        return *this ^ broadcast_f32(f);
    }

    f32x4 operator|(f32x4 &f)
    {
        return f32x4(or_f32(packed, f.packed));
    }

    f32x4 operator|(m128f_t f)
    {
        return f32x4(or_f32(packed, f));
    }

    f32x4 operator|(f32 f)
    {
        return *this | broadcast_f32(f);
    }

    f32x4 blend(f32x4 b, i8 m)
    {
        return f32x4(blend_f32(packed, b.packed, m));
    }

    f32x4 blend(m128f_t b, i8 m)
    {
        return f32x4(blend_f32(packed, b, m));
    }

    f32x4 ceil()
    {
        return f32x4(ceil_ps(packed));
    }

    f32x4 shuffle(i8 m)
    {
        return f32x4(shuffle_f32(packed, m));
    }

    f32x4 horizadd(f32x4 b)
    {
        return f32x4(horizadd_f32(packed, b.packed));
    }

    f32x4 horizadd(m128f_t b)
    {
        return f32x4(horizadd_f32(packed, b));
    }

    f32x4 horizsub(f32x4 b)
    {
        return f32x4(horizsub_f32(packed, b.packed));
    }

    f32x4 horizadd(m128f_t b)
    {
        return f32x4(horizsub_f32(packed, b));
    }

    f32 getIndex(int i)
    {
        f32 ret;
        store_f32(&ret, shuffle_f32(packed, XMM_F32_CREATE_SHUFFLE_MASK(i % 4, i % 4, i % 4, i % 4)));
        return ret;
    }

    void setIndex(f32 val, int i)
    {
        packed = blend_f32(packed, broadcast_f32(val), 1 << (i % 4));
    }
};

using xmm_f32 = f32x4;

class f64x2
{
    public:
    m128d_t packed;
    f64x2()
    {
        packed = broadcast_f64(0.0d);
    }

    f64x2(f64 d)
    {
        packed = broadcast_f64(d);
    }

    f64x2(f64 *ptr)
    {
        packed = uload_mf64(ptr);
    }

    f64x2(m128d_t v)
    {
        packed = v;
    }

    f64x2 operator=(f64 d)
    {
        packed = broadcast_f64(d);
    }

    f64x2 operator=(f64 *ptr)
    {
        packed = uload_mf64(ptr);
    }

    f64x2 operator=(m128d_t v)
    {
        packed = v;
    }

    f64x2 operator+(f64x2 &v)
    {
        return f64x2(add_mf64(packed, v.packed));
    }

    f64x2 operator+(m128d_t v)
    {
        return f64x2(add_mf64(packed, v));
    }

    f64x2 operator+(f64 f)
    {
        return *this + broadcast_f64(f);
    }

    f64x2 operator-(f64x2 &v)
    {
        return f64x2(sub_mf64(packed, v.packed));
    }

    f64x2 operator-(m128d_t v)
    {
        return f64x2(sub_mf64(packed, v));
    }

    f64x2 operator-(f64 f)
    {
        return *this - broadcast_f64(f);
    }

    f64x2 operator*(f64x2 &v)
    {
        return f64x2(mul_mf64(packed, v.packed));
    }

    f64x2 operator*(m128d_t v)
    {
        return f64x2(mul_mf64(packed, v));
    }

    f64x2 operator*(f64 f)
    {
        return *this * broadcast_f64(f);
    }

    f64x2 operator/(f64x2 &v)
    {
        return f64x2(div_mf64(packed, v.packed));
    }

    f64x2 operator/(m128d_t v)
    {
        return f64x2(div_mf64(packed, v));
    }

    f64x2 operator/(f64 f)
    {
        return *this / broadcast_f64(f);
    }

    f64x2 operator^(f64x2 &v)
    {
        return f64x2(xor_f64(packed, v.packed));
    }

    f64x2 operator^(m128d_t v)
    {
        return f64x2(xor_f64(packed, v));
    }

    f64x2 operator^(f64 f)
    {
        return *this ^ broadcast_f64(f);
    }

    f64x2 operator&(f64x2 &v)
    {
        return f64x2(and_f64(packed, v.packed));
    }

    f64x2 operator&(m128d_t v)
    {
        return f64x2(and_f64(packed, v));
    }

    f64x2 operator&(f64 f)
    {
        return *this & broadcast_f64(f);
    }

    f64x2 operator|(f64x2 &v)
    {
        return f64x2(or_f64(packed, v.packed));
    }

    f64x2 operator|(m128d_t v)
    {
        return f64x2(or_f64(packed, v));
    }

    f64x2 operator|(f64 f)
    {
        return *this | broadcast_f64(f);
    }

    f64x2 blend(f64x2 v, int m)
    {
        return f64x2(blend_f64(packed, v.packed, m));
    }

    f64x2 blend(m128d_t v, int m)
    {
        return f64x2(blend_f64(packed, v, m));
    }

    f64x2 ceil()
    {
        return f64x2(ceil_pd(packed));
    }

    f64x2 shuffle(int m)
    {
        return f64x2(shuffle_f64(packed, m));
    }

    f64x2 horizadd(f64x2 v)
    {
        return f64x2(horizadd_f64(packed, v.packed));
    }

    f64x2 horizadd(m128d_t v)
    {
        return f64x2(horizadd_f64(packed, v));
    }

    f64x2 horizsub(f64x2 v)
    {
        return f64x2(horizsub_f64(packed, v.packed));
    }

    f64x2 horizsub(m128d_t v)
    {
        return f64x2(horizsub_f64(packed, v));
    }

    f64 getIndex(int i)
    {
        f64 ret;
        store_f64(&ret, shuffle_f64(packed, XMM_F64_CREATE_SHUFFLE_MASK(i, i)));
        return ret;
    }

    void setIndex(f64 val, int i)
    {
        packed = blend_f64(packed, broadcast_f64(val), i + 1 );
    }
};

using xmm_f64 = f64x2;

// TODO: Integer SIMD stuff
// TODO: ymm stuff

#elif defined(__aarch64__)

#include <arm_neon.h>

// TODO: Arm Neon code.

#elif defined(__i386__)

#error x86/x86-32/i*86 is not supported by the Citrus Engine! The Citrus Engine only supports 64 bit targets!

#elif defined(__arm__)

#error 32-bit Arm is not supported by the Citrus Engine! The Citrus Engine only supports 64 bit targets!

#else

#error Unsupported CPU architecture!

#endif

#endif
