/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
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