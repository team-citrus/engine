/*
*   name: graphics/initGL.hpp
*   origin: Citrus Engine
*   purpose: Functions for initalizing and de-initalizing OpenGL
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_OPENGL_INITIALIZATION_HPP__
#define CITRUS_ENGINE_OPENGL_INITIALIZATION_HPP__

/*  THIS FILE IS A VERY IMPORTANT FILE, DONT TAMPER WITH IT UNLESS ABSOLUTELY NECESSARY
*   Within this file the prototypes of our Vulkan initalization functions and #defines are contained
*   It is important that they function as expected, or launching will fail
*/

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