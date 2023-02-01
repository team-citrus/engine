/*
*   name: include/graphics/glGlobals.hpp
*   origin: Citrus Engine
*   purpose: {PURPOSE FOR THE FILE}
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_OPENGL_GLOBALS_HPP__
#define CITRUS_ENGINE_OPENGL_GLOBALS_HPP__

#ifdef _WIN32

#include <Windows.h>
typedef HMODULE dllptr_t;

#elif defined(__unix__)

typedef void* dllptr_t;

#endif

namespace engine
{
namespace internals
{
	namespace OpenGL
	{
        dllptr_t gl_dll;
    }
}
}

#endif