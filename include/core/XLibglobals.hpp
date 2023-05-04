/*
*   name: include/core/XLibglobals.hpp
*   origin: Citrus Engine
*   purpose: Globals for XLib
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_XLIB_GLOBAL_VARIABLES_HPP__
#define CITRUS_ENGINE_XLIB_GLOBAL_VARIABLES_HPP__

#ifdef __linux__
#include <X11/Xlib.h>

namespace engine
{
	namespace internals
	{
		Display *display;
		int screen;
		Window window;
	}
}

#elif defined(_WIN32)

#warning Why is core/XLibglobals included in Windows code exactly?

#endif

#endif