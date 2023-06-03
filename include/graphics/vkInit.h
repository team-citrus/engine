/*
*   name: include/graphics/vkInit.hpp
*   origin: Citrus Engine
*   purpose: Functions for initalizing and de-initalizing Vulkan
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_VULKAN_INITIALIZATION_HPP__
#define CITRUS_ENGINE_VULKAN_INITIALIZATION_HPP__

#define ERR_VULKAN_NOT_FOUND -1
#define ERR_VULKAN_LOADER_FAILED -2
#define ERR_VULKAN_INCOMPATIBLE -3
#define ERR_VULKAN_INSTANCE_FAILURE -4

#define VK_NO_PROTOTYPES
#include <vulkan.h>
#include "../graphics/vkGlobals.h"

	
int vkLoad();
int vkTerminate();

#endif
