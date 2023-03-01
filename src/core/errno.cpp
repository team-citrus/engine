/*
*	name: src/core/errno.cpp
*	origin: Citrus Engine
*	purpose: Provide different engine::errorcode() variables with as little trouble as possible.
*	author: https://github.com/ComradeYellowCitrusFruit
*	license: LGPL-3.0-only
*/

#define _FILE_IS_ERRNO_DOT_CPP_

#include <threads.h>
#include "core/errno.hpp"
#include "core/pair.hpp"
#include "core/hash.hpp"
#include "core/option.hpp"

engine::hashMap<thrd_t, unsigned int> errcodes;

unsigned int engine::errorcode()
{
    static bool inited = false;
    engine::option<unsigned int &>ret;
    if(!inited)
        errcodes = engine::hashMap<thrd_t, unsigned int>(32);

    if((ret = errcodes.add(thrd_current(), 0)).is_none())
        return errcodes[thrd_current()];
    else
        return ret.unwrap();
}

