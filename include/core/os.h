/*
*   name: include/core/os.h
*   origin: Citrus Engine
*   purpose: Provides some operating system defines
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: MIT or LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_OPERATING_SYSTEM_H__
#define CITRUS_ENGINE_OPERATING_SYSTEM_H__

#if defined(_WIN64) || defined(__MINGW32__) || defined(__MSYS__) || defined(__CYGWIN__)

#define CITRUS_ENGINE_OPERATING_SYSTEM_STRING "Windows"
#define CITRUS_ENGINE_OPERATING_SYSTEM_CODE 1
#define CITRUS_ENGINE_WINDOWS
#define CITRUS_ENGINE_WIN64

#elif defined(__ANDROID__)

#error I am sorry but as of yet we do not support any mobile platforms.

#elif defined(__linux__)

#define CITRUS_ENGINE_OPERATING_SYSTEM_STRING "Linux"
#define CITRUS_ENGINE_OPERATING_SYSTEM_CODE 0
#define CITRUS_ENGINE_LINUX
#define CITRUS_ENGINE_LINUX_GNU
#define CITRUS_ENGINE_GNU_LINUX
#define CITRUS_ENGINE_UNIX

#elif defined(__FreeBSD__)

#define CITRUS_ENGINE_OPERATING_SYSTEM_STRING "FreeBSD"
#define CITRUS_ENGINE_OPERATING_SYSTEM_CODE 2
#define CITRUS_ENGINE_FREEBSD
#define CITRUS_ENGINE_UNIX

#elif defined(__OpenBSD__)

#define CITRUS_ENGINE_OPERATING_SYSTEM_STRING "OpenBSD"
#define CITRUS_ENGINE_OPERATING_SYSTEM_CODE 3
#define CITRUS_ENGINE_OPENBSD
#define CITRUS_ENGINE_UNIX

#elif defined(__NetBSD__)

#define CITRUS_ENGINE_OPERATING_SYSTEM_STRING "OpenBSD"
#define CITRUS_ENGINE_OPERATING_SYSTEM_CODE 4
#define CITRUS_ENGINE_NETBSD
#define CITRUS_ENGINE_UNIX

#elif defined(__DragonFly__)

#define CITRUS_ENGINE_OPERATING_SYSTEM_STRING "DragonFly BSD"
#define CITRUS_ENGINE_OPERATING_SYSTEM_CODE 5
#define CITRUS_ENGINE_DRAGONFLY
#define CITRUS_ENGINE_UNIX

#elif defined(__gnu_hurd__)

#warning We won't stop you but you sure that's a good idea?

#define CITRUS_ENGINE_OPERATING_SYSTEM_STRING "GNU/Hurd"
#define CITRUS_ENGINE_OPERATING_SYSTEM_CODE 6
#define CITRUS_ENGINE_HURD
#define CITRUS_ENGINE_GNU_HURD
#define CITRUS_ENGINE_UNIX

#elif defined(__APPLE__) && defined(__MACH__)

#error We do not support Apple as of yet. Please get a better operating system, perhaps consider using Linux?

#else

#error We don't know what operating system you're running but we do NOT support it

#endif

#endif