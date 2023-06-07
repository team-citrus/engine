/*
*   name: include/graphics/vkGlobals.hpp
*   origin: Citrus Engine
*   purpose: Vulkan global variables
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_VULKAN_GLOBALS_H__
#define CITRUS_ENGINE_VULKAN_GLOBALS_H__

#include <vulkan.h>
#include "../core/os.h"

#ifdef CITRUS_ENGINE_WINDOWS

#include <Windows.h>
typedef HMODULE dllptr_t;

#else

typedef void* dllptr_t;

#endif

#include "../graphics/vkCall.h"

typedef PFN_vkVoidFunction (*vkGIPA_t)(VkInstance, const char*);
typedef PFN_vkVoidFunction (*vkGDPA_t)(VkDevice, const char*);

#ifdef __cplusplus

NOMANGLE
{

#endif

// The address of the Vulkan library
extern dllptr_t libvulkan;

// Good ol' vkGetInstanceProcAddr
extern vkGIPA_t vkGetInstanceProcAddrPtr;
// Good ol' vkGetDeviceProcAddr
extern vkGDPA_t vkGetDeviceProcAddrPtr;
		
// The Vulkan instance
extern VkInstance instance;

// The Vulkan device
extern VkDevice device;

// The Vulkan Swapchain
extern VkSwapchainKHR swapchain;
extern VkSufaceKHR surface;

// Physical device info

extern VkPhysicalDevice physicalDevice;
extern VkPhysicalDeviceProperties physicalDeviceProperties;
extern VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
extern size_t physicalDeviceVRAM;
		
// TODO: Add different Vulkan render functions based on different Vulkan versions and extensions
// TODO: Framebuffer

#ifdef __cplusplus

}

#endif

#endif