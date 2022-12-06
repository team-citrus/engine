#ifndef CITRUS_ENGINE_MEMORY_MANAGEMENT_INTERNALS_HPP__
#define CITRUS_ENGINE_MEMORY_MANAGEMENT_INTERNALS_HPP__

#include <cstdint>
#include "include/core/extensions.hpp"

#define ALLOC_HEADER_MAGIC_NUMBER 0x8BFEDC0A

#define ALLOC_HEADER_TYPE_HEAP 'H'
#define ALLOC_HEADER_TYPE_MMAP 'M'
#define ALLOC_HEADER_TYPE_POOL 'P'

namespace engine
{
	namespace internals
	{
		_PACKED_(class allocHeader
		{
			public:
				uint32_t magic;
				uint16_t flags;
				char type;
				char align;
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
