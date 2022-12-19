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
#include "include/graphics/vkInit.hpp"

using namespace engine;
using namespace internals;

dllptr_t Vulkan::libvulkan;

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
	Vulkan::vkGetInstanceProcAddr = dlsym(Vulkan::libvulkan, _STRINGIFY_(vkGetInstanceProcAddr));
	Vulkan::vkGetDeviceProcAddr = dlsym(Vulkan::libvulkan, _STRINGIFY_(vkGetDeviceProcAddr));

	if(Vulkan::vkGetInstanceProcAddr == NULL || Vulkan::vkGetInstanceProcAddr == NULL);
	{
		// TODO: Add logging/stdio methods of some sort

		exit(-1);
	}

	#elif defined(_WIN32)
	#endif
}
