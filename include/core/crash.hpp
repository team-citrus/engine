/*
*	name: include/core/crash.hpp
*	origin: Citrus Engine
*	purpose: Provide crash exit codes
*	author: https://github.com/ComradeYellowCitrusFruit
*	license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_ERROR_CODES_HPP__
#define CITRUS_ENGINE_ERROR_CODES_HPP__

#define USR_API_PREFIX 0x10 << 24
#define CORE_PREFIX 0x20 << 24
#define OPENGL_PREFIX 0x40 << 24
#define VK_PREFIX 0x80 << 24

#define SEGFAULT 0xFFFFFF | CORE_PREFIX
#define SIG_ILLEGAL_INSTRUCTION 0xEEEEEE | CORE_PREFIX
#define INVALID_CPU 0x7FFFFF | CORE_PREFIX
#define VK_LOAD_FAILURE 0xFFFFFF | VK_PREFIX
#define VULKAN_NOT_FOUND 0xFFFFFF | VK_PREFIX | CORE_PREFIX
#define VK_COMPATIBLE_GPU_NOT_FOUND 0x888888 | VK_PREFIX
#define CRITICAL_FILE_MISSING 0x777777 | CORE_PREFIX
#define DEPENDANCY_MISSING 0x888888 | CORE_PREFIX

namespace engine
{
    const char *interpretCrashCode(int code); // TODO: Implement this
}

#endif
