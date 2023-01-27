/*
*   name: graphics/vkInit.hpp
*   origin: Citrus Engine
*   purpose: Functions for initalizing and de-initalizing Vulkan
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_VULKAN_INITIALIZATION_HPP__
#define CITRUS_ENGINE_VULKAN_INITIALIZATION_HPP__

/*  THIS FILE IS A VERY IMPORTANT FILE, DONT TAMPER WITH IT UNLESS ABSOLUTELY NECESSARY
*   Within this file the prototypes of our Vulkan initalization functions and #defines are contained
*   It is important that they function as expected, or launching will fail
*/

#define ERR_VULKAN_NOT_FOUND -1
#define ERR_VULKAN_LOADER_FAILED -2
#define ERR_VULKAN_INCOMPATIBLE -3
#define ERR_VULKAN_INSTANCE_FAILURE -4

#include <vulkan.h>
#include "graphics/vkGlobals.hpp"

namespace engine
{
namespace internals
{
	namespace Vulkan
	{	
		int vkLoad();
		int vkTerminate();
	};
};
};
#endif
