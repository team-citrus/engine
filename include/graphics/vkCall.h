/*
*   name: include/graphics/vkNullCall.hpp
*   origin: Citrus Engine
*   purpose: Provide preprocessor defines for Vulkan call wrappers
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_VULKAN_CALLS_H__
#define CITRUS_ENGINE_VULKAN_CALLS_H__

#define VK_NO_PROTOTYPES
#include <vulkan.h>
#include <cstdint>
#include "../graphics/vkGlobals.h"
#include "../core/extensions.h"
#include "../core/log.hpp"

typedef VkResult (*vkFuncPtr_t)(...);

// TODO: Redo this cause apparently there are a fuck ton of errors

/*  Make a call to a Vulkan device function.	
*   All of the arguments after func will be passed in order to the function being called
*   @param func Function to call
*   @param device Device to call the function on
*   @return Returns the function's return value
*/
template<typename... A>
VkResult vkDeviceCall(const char *func, A... parameters)
{
	return ((vkGetDeviceProcAddrPtr(device, func))(parameters...));
}

/*  Make a call to a Vulkan instance function.
*   All of the arguments after func will be passed in order to the function being called
*   @param func Function to call
*   @param instance Instance to call the function on
*   @return Returns the function's return value
*/
template<typename... A>
VkResult vkInstanceCall(const char *func, A... parameters)
{
	return ((vkGetInstanceProcAddrPtr(instance, func))(parameters...));
}
		

/*  Make a call to a Vulkan function that doesn't take an instance or device in the function call.
*   All of the arguments after func will be passed in order to the function being called
*   @param func Function to call
*   @return Returns the function's return value
*/
template<typename... A>
VkResult vkNullCall(const char *func, A... parameters)
{
	return ((vkGetInstanceProcAddrPtr(NULL, func))(parameters...));
}

#define vkCheck(x) {auto _x = x; if(x!=VK_SUCCESS) { log("Vulkan", "Vulkan error %d, exiting.", _x); exit(-1); }}

#endif