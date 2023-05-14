/*
*   name: include/graphics/vkGlobals.hpp
*   origin: Citrus Engine
*   purpose: Vulkan global variables
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_VULKAN_GLOBALS_HPP__
#define CITRUS_ENGINE_VULKAN_GLOBALS_HPP__

#include <vulkan.h>
#include "../core/os.h"

#ifdef CITRUS_ENGINE_WINDOWS

#include <Windows.h>
typedef HMODULE dllptr_t;

#else

typedef void* dllptr_t;

#endif

#include "../graphics/matrix.hpp"
#include "../graphics/vkCall.hpp"

namespace engine
{
namespace internals
{
	namespace Vulkan
	{
		typedef PFN_vkVoidFunction (*vkGIPA_t)(VkInstance, const char*);
		typedef PFN_vkVoidFunction (*vkGDPA_t)(VkDevice, const char*);

		// The address of the Vulkan library
		extern dllptr_t libvulkan;

		// Good ol' vkGetInstanceProcAddr
		extern vkGIPA_t vkGetInstanceProcAddr;
		// Good ol' vkGetDeviceProcAddr
		extern vkGDPA_t vkGetDeviceProcAddr;
		
		// The Vulkan instance
		extern VkInstance instance;

		// The Vulkan device
		extern VkDevice device;

		// Physical device info

		extern VkPhysicalDevice physicalDevice;
		extern VkPhysicalDeviceProperties physicalDeviceProperties;
		extern VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
		extern size_t physicalDeviceVRAM;
		
		// TODO: Add different Vulkan render functions based on different Vulkan versions and extensions

		render::Matrix4x4 viewmat;
		// TODO: render::Camera &mainCamera;

		// TODO: Framebuffer
	};
};
};

#endif