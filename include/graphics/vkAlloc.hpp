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