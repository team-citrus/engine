/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifndef CITRUS_ENGINE_VULKAN_GLOBALS_HPP__
#define CITRUS_ENGINE_VULKAN_GLOBALS_HPP__

#include <vulkan.h>

namespace engine
{
namespace internals
{
	namespace Vulkan
	{
		extern VkInstance instance;
		extern VkDevice device;
	};
};
};

#endif