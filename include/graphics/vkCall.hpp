/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
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