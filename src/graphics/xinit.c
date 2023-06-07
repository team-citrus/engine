/*
*   name: src/graphics/xinit.c
*   origin: Citrus Engine
*   purpose: Functions for initalizing Xlib windows
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include "core/os.h"

#ifdef CITRUS_ENGINE_UNIX

#include <X11/Xlib.h>
#include "core/XLibglobals.h"

void xinit()
{
	display = XOpenDisplay(NULL);
	screen = DefaultScreen(display);
	window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, 200, 200, CopyFromParent, BlackPixel(display, screen), WhitePixel(display, screen));
}

#endif