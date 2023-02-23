/*
*	name: include/core/errno.hpp
*	origin: Citrus Engine
*	purpose: Provide engine::errno
*	author: https://github.com/ComradeYellowCitrusFruit
*	license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_ERROR_NUMBER_HPP__
#define CITRUS_ENGINE_ERROR_NUMBER_HPP__

#define ENGINE_FATALERR_PREFIX 0x8 << 28
#define ENGINE_ERROR_PREFIX 0x4 << 28

#define ENGINE_NO_MEM ENGINE_FATALERR_PREFIX | ‬01

#define ENGINE_INVALID_PTR ENGINE_ERROR_PREFIX | 020
#define ENGINE_INVALID_ARG ENGINE_ERROR_PREFIX | 040
#define ENGINE_INVALID_SCENE ENGINE_ERROR_PREFIX | 060
#define ENGINE_HASH_COLLISION ENGINE_INVALID_ARG
// TODO: More defines

namespace engine
{
    extern unsigned int errno;
}

#endif
