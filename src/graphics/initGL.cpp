/*
*   name: src/graphics/initGL.cpp
*   origin: Citrus Engine
*   purpose: Provide the code for engine::internals::OpenGL::loadGL()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifdef __unix__

#include <unistd.h>
#include <dlfcn.h>

#elif defined(_WIN32)

#include <Windows.h>

#endif

#include <stdlib.h>
#include <gl/gl.h>
#include "core/crash.hpp"
#include "core/log.hpp"
#include "core/mem.hpp"
#include "core/extensions.h"
#include "core/vector.hpp"
#include "graphics/glGlobals.hpp"
#include "graphics/initGL.hpp"

using namespace engine;
using namespace internals;

int OpenGL::loadGL()
{
    // Since OpenGL is only supported as an extension for backwards compatibility, it is it's own seperate DLL
    #ifdef __unix__

    OpenGL::gl_dll = dlopen("liblegacyrender.so", RTLD_NOW | RTLD_GLOBAL);

    // TODO: Create and fill the trampoline

    #elif defined(_WIN32)

    OpenGL::gl_dll = LoadLibraryA("GL.dll");

    // TODO: Create and fill the trampoline

    #endif
}