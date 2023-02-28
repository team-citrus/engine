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
};

using xmm_f32 = f32x4;

#endif
