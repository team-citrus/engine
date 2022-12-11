/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifndef CITRUS_ENGINE_VULKAN_MEMORY_ALLOCATION_HPP__
#define CITRUS_ENGINE_VULKAN_MEMORY_ALLOCATION_HPP__

#include <vulkan.h>

/* Vulkan memory allocation and deallocation */

namespace engine
{
namespace internals
{
	namespace Vulkan
	{
		/* Allocate memory of size bytes, of type type */
		void *malloc(size_t bytes, int type);
		
		/* Reallocate memory of size bytes, of type type */
		void *realloc(void *alloc, size_t bytes, int type);

		/* Free memory */
		void free(void *alloc);
	};
};
};

#endif