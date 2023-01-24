/*
*   name: include/graphics/initGL.hpp
*   origin: Citrus Engine
*   purpose: Functions for initalizing and de-initalizing OpenGL
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_OPENGL_INITIALIZATION_HPP__
#define CITRUS_ENGINE_OPENGL_INITIALIZATION_HPP__

#include <gl/gl.h>

namespace engine
{
namespace internals
{
	namespace OpenGL
	{
        int loadGL();
        int terminateGL();
    }
}
}

#endif