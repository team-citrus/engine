/*
*   name: include/core/XLibglobals.hpp
*   origin: Citrus Engine
*   purpose: Globals for XLib
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_XLIB_GLOBAL_VARIABLES_HPP__
#define CITRUS_ENGINE_XLIB_GLOBAL_VARIABLES_HPP__

#include "../core/os.h"

#ifdef CITRUS_ENGINE_UNIX

#include <X11/Xlib.h>

Display *display;
int screen;
Window window;
Time frameStart;
Time gameStart;

#elif defined(CITRUS_ENGINE_WINDOWS)

#warning Why is core/XLibglobals.h included in Windows code exactly?

#endif

#endif