/*
*   name: include/graphics/vkGlobals.hpp
*   origin: Citrus Engine
*   purpose: {PURPOSE FOR THE FILE}
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_VULKAN_GLOBALS_HPP__
#define CITRUS_ENGINE_VULKAN_GLOBALS_HPP__

#include <vulkan.h>

#ifdef _WIN32

#include <Windows.h>
typedef HMODULE dllptr_t;

#elif defined(__unix__)

typedef void* dllptr_t;

#endif

#include "include/graphics/vkCall.hpp"

#ifndef VULKAN_VERSION
#define VULKAN_VERSION VK_VERSION_1_0
#endif

namespace engine
{
namespace internals
{
	namespace Vulkan
	{
		typedef PFN_vkVoidFunction (vkGIPA_t)(VkInstance, const char*);
		typedef PFN_vkVoidFunction (vkGDPA_t)(VkDevice, const char*);

		// The address of the Vulkan library
		extern dllptr_t libvulkan;

		// Good ol' vkGetInstanceProcAddr
		extern vkGIPA_t vkGetInstanceProcAddr;
		// Good ol' vkGetDeviceProcAddr
		extern vkGDPA_t vkGetDeviceProcAddr;
		
		extern VkInstance instance;
		extern VkDevice device;
		extern VkPhysicalDevice pdevice;
	};
};
};

#endif