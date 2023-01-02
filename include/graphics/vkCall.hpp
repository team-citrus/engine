/*
*   name: include/graphics/vkCall.hpp
*   origin: Citrus Engine
*   purpose: Provide preprocessor defines for Vulkan call wrappers
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_VULKAN_CALLS_HPP__
#define CITRUS_ENGINE_VULKAN_CALLS_HPP__

#include <vulkan.h>
#include <cstdint>
#include "include/graphics/vkGlobals.hpp"

namespace engine
{
namespace internals
{
    namespace Vulkan
    {
        typedef VkResult (*vkFuncPtr_t)(...);

        /*  Make a call to a Vulkan device function.
        *   All of the arguments after func will be passed in order to the function being called
        *   @param func Function to call
        *   @param device Device to call the function on
        *   @return Returns the function's return value
        */
        #define vkDeviceCall(func, device, ...)  (*(vkFuncPtr_t)vkGetDeviceProcAddr(device, __STRINGIFY_(func)))(device, __VA_ARGS__)

        /*  Make a call to a Vulkan instance function.
        *   All of the arguments after func will be passed in order to the function being called
        *   @param func Function to call
        *   @param instance Instance to call the function on
        *   @return Returns the function's return value
        */
        #define vkInstanceCall(func, instance, ...)  (*(vkFuncPtr_t)vkGetInstanceProcAddr(instance, __STRINGIFY_(func)))(instance, __VA_ARGS__)
    };
};
};

#endif