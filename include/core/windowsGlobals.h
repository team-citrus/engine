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

HINSTANCE hinstance;
HWND hwnd;

#elif defined(CITRUS_ENGINE_UNIX)

#warning Why is core/windowsGlobals.h included in unix code exactly?

#endif

#endif