#ifndef CITRUS_ENGINE_MEMORY_MANAGEMENT_INTERNALS_HPP__
#define CITRUS_ENGINE_MEMORY_MANAGEMENT_INTERNALS_HPP__

#include <cstdint>
#include "include/core/extensions.hpp"

#define ALLOC_HEADER_MAGIC_NUMBER 0x8BFEDC0A

#define ALLOC_HEADER_TYPE_HEAP 'H'
#define ALLOC_HEADER_TYPE_MMAP 'M'
#define ALLOC_HEADER_TYPE_POOL 'P'

#define ALLOC_PAGE_OFFSET(x) (x * 0x1000)
#define ALLOC_PAGE_START() ((void*)((uintptr_t)poolResvEnd + ALLOC_PAGE_OFFSET(2)))
#define ALLOC_RESOURCE_START() (ALLOC_PAGE_START + ALLOC_PAGE_OFFSET(200))

namespace engine
{
	namespace internals
	{
		class poolHeader
		{
			public:
				// Pretty much just pool - poolResvEnd
				ptrdiff_t maxPoolSize;
				// Size of current allocated pool
				size_t poolSize;
				// Unallocated bytes in pool
				size_t
				// Size of the area before the pool describing the rest of our memory space, in pages.
				int metaMemsize;
				// Meta memory start position
				void *metaMem;


		// The base address of the pool, always aligned to a page boundary.
		void *pool;

		// End of the pool reserved space. 
		void *poolResvEnd;
		_PACKED_(class allocHeader
		{
			public:
				uint32_t magic;
				// The flags given to memalloc(), however the high bit will be set if using page allocation, bit 14 has to be set for pool allocation, or clear for heap allocation
				uint16_t flags;
				// How many bytes used to align
				size_t align : 4;
				size_t size : 60;
				OPERATOR bool isValid()
				{
					return (magic == ALLOC_HEADER_MAGIC_NUMBER);
				}

				OPERATOR bool isHeap()
				{
					return (type == ALLOC_HEADER_TYPE_HEAP);
				}

				OPERATOR bool isPool()
				{
					return (type == ALLOC_HEADER_TYPE_POOL);
				}

				OPERATOR bool isMmap()
				{
					return (type == ALLOC_HEADER_TYPE_MMAP);
				}
		});
	};
};

#endif
