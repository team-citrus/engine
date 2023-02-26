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

class m128_i8
{
    public:
    m128i_t Pi8;

    m128_i8(m128i_t i)
    {
        Pi8 = i;
    }

    m128_i8 operator+(m128_i8 &i)
    {
        return m128_i8(add_i8(Pi8, i.Pi8));
    }

    m128_i8 operator+(m128i_t &i)
    {
        return m128_i8(add_i8(Pi8, i));
    }

    m128_i8 operator+(i8 i)
    {
        m128i_t a = broadcast_i8(i);
        return *this + a;
    }
    
    m128_i8 operator-(m128_i8 &i)
    {
        return m128_i8(sub_epi8(Pi8, i.Pi8));
    }

    m128_i8 operator-(m128i_t &i)
    {
        return m128_i8(sub_epi8(Pi8, i));
    }

    m128_i8 operator-(i8 i)
    {
        m128i_t a = broadcast_i8(i);
        return *this - a;
    }
    
    m128_i8 operator|(m128_i8 &i)
    {
        return m128_i8(or_i128(Pi8, i.Pi8));
    }

    m128_i8 operator|(m128i_t &i)
    {
        return m128_i8(or_i128(Pi8, i));
    }

    m128_i8 operator|(i8 i)
    {
        m128i_t a = broadcast_i8(i);
        return *this | a;
    }
    
    m128_i8 operator&(m128_i8 &i)
    {
        return m128_i8(and_i128(Pi8, i.Pi8));
    }

    m128_i8 operator&(m128i_t &i)
    {
        return m128_i8(and_i128(Pi8, i));
    }

    m128_i8 operator&(i8 i)
    {
        m128i_t a = broadcast_i8(i);
        return *this & m128_i8(a);
    }
    
    m128_i8 operator&(i8 i)
    {
        m128i_t a = broadcast_i8(i);
        return *this & a;
    }
    
    m128_i8 operator^(m128_i8 &i)
    {
        return m128_i8(xor_i128(Pi8, i.Pi8));
    }

    m128_i8 operator^(m128i_t &i)
    {
        return m128_i8(xor_i128(Pi8, i));
    }

    m128_i8 operator^(i8 i)
    {
        m128i_t a = broadcast_i8(i);
        return *this ^ a;
    }
};

#endif
