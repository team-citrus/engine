/*
*   name: include/core/simd.h
*   origin: Citrus Engine
*   purpose: Provide SIMD abstractions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: CC0-1.0 OR LGPL-3.0-ONLY
*/

#ifndef CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_HPP__
#define CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_HPP__

#include "include/core/simd.h"

class m128ps
{
    m128f_t pfs;
    public:
    m128ps(m128f_t f)
    {
        pfs = f;
    }

    inline m128ps operator+(const m128f_t &b)
    {
        return m128ps(add_ps(pfs, b));
    }

    inline m128ps operator+(const m128ps &b)
    {
        return m128ps(add_ps(pfs, b.pfs));
    }

    inline m128ps operator-(const m128f_t &b)
    {
        return m128ps(sub_ps(pfs, b));
    }

    inline m128ps operator-(const m128ps &b)
    {
        return m128ps(sub_ps(pfs, b.pfs));
    }

    inline m128ps operator*(const m128f_t &b)
    {
        return m128ps(mul_ps(pfs, b));
    }

    inline m128ps operator*(const m128ps &b)
    {
        return m128ps(mul_ps(pfs, b.pfs));
    }

    inline m128ps operator/(const m128f_t &b)
    {
        return m128ps(div_ps(pfs, b));
    }

    inline m128ps operator/(const m128ps &b)
    {
        return m128ps(div_ps(pfs, b.pfs));
    }
};

#endif