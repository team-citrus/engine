/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifdef __unix__

#include <unistd.h>
#include <dlfcn.h>

#elif defined(_WIN32)

#include <Windows.h>

#endif

#include <stdlib.h>
#include <vulkan.h>

#include "include/core/mem.hpp"
#include "include/core/extensions.hpp"
#include "include/graphics/vkGlobals.hpp"
#include "include/graphics/vkInit.hpp"

using namespace engine;
using namespace internals;

dllptr_t Vulkan::libvulkan;

Vulkan::vkGIPA_t Vulkan::vkGetInstanceProcAddr;
Vulkan::vkGDPA_t Vulkan::vkGetDeviceProcAddr;
VkAllocationCallbacks Vulkan::vkAllocCallbacks;

VkInstance Vulkan::instance;
VkDevice Vulkan::device;

int Vulkan::vkLoad()
{
	#ifdef __unix__

	Vulkan::libvulkan = dlopen("libvulkan.so", RTLD_NOW);
	if(Vulkan::libvulkan == NULL)
	{
		// TODO: Add logging/stdio methods of some sort
		
		exit(-1);
	}

	// Get good ol' vkGetInstanceProcAddr and vkGetDeviceProcAddr
	Vulkan::vkGetInstanceProcAddr = (Vulkan::vkGIPA_t)dlsym(Vulkan::libvulkan, _STRINGIFY_(vkGetInstanceProcAddr));
	Vulkan::vkGetDeviceProcAddr = (Vulkan::vkGIDA_t)dlsym(Vulkan::libvulkan, _STRINGIFY_(vkGetDeviceProcAddr));

	if(Vulkan::vkGetInstanceProcAddr == NULL || Vulkan::vkGetInstanceProcAddr == NULL);
	{
		// TODO: Add logging/stdio methods of some sort

		exit(-1);
	}

	#elif defined(_WIN32)

	Vulkan::libvulkan = LoadLibraryA("Vulkan-1.dll");
	if(Vulkan::libvulkan == NULL)
	{
		// TODO: Add logging/stdio methods of some sort

		exit(-1);
	}

    // Get good ol' vkGetInstanceProcAddr and vkGetDeviceProcAddr
    Vulkan::vkGetInstanceProcAddr = (Vulkan::vkGIPA_t)GetProcAddress(Vulkan::libvulkan, _STRINGIFY_(vkGetInstanceProcAddr));
	Vulkan::vkGetDeviceProcAddr = (Vulkan::vkGDPA_t)GetProcAddress(Vulkan::libvulkan, _STRINGIFY_(vkGetDeviceProcAddr));

	if(vkGetInstanceProcAddr == NULL || vkGetDeviceProcAddr == NULL)
	{
		// TODO: Add logging/stdio methods of some sort

		exit(-1);
	}

	#endif

	// Initalize Vulkan

	// Vulkan application info

	VkApplicationInfo aInfo;
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	// _APPLICATION_NAME_ defined during compilation
	info.pApplicationName = _APPLICATION_NAME_;
	info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	info.pNext = NULL;
	info.pEngineName = "Citrus Engine Builtin Vulkan Render Engine";
	// _CITRUS_ENGINE_VERSION_ defined during compilation
	info.engineVersion = _CITRUS_ENGINE_VERSION_;
	info.apiVersion = VULKAN_VERSION;

	// Vulkan instance creation info

	VkInstanceCreateInfo iInfo;
	iInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	iInfo.pApplicationInfo = &aInfo;
	// TODO: Add the layer information.
	iInfo.enabledExtensionCount = 0;
	iInfo.ppEnabledExtensionNames = NULL;

	// TODO: Add allocation callback information
	
	// Initalize the instance
	vkInstanceCall(vkCreateInstance, 0, &iInfo, &Vulkan::allocCallbacks, &Vulkan::instance);

}
