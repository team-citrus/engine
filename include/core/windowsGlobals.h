/*
*   name: include/core/windowsGlobals.h
*   origin: Citrus Engine
*   purpose: Globals for XLib
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_WINDOWS_WINDOWING_GLOBAL_VARIABLES_HPP__
#define CITRUS_ENGINE_WINDOWS_WINDOWING_GLOBAL_VARIABLES_HPP__

#include "../core/os.h"

#ifdef CITRUS_ENGINE_WINDOWS

#include <Windows.h>
#include "core/extensions.h"

#ifdef __cplusplus
NOMANGLE {
#endif

HINSTANCE hinstance;
HWND hwnd;
int showStyle;

void winit();

#ifdef __cplusplus
}
#endif

#elif defined(CITRUS_ENGINE_UNIX)

#warning Why is core/windowsGlobals.h included in unix code exactly?

#endif

#endif
