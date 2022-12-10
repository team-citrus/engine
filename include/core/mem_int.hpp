#ifndef CITRUS_ENGINE_MEMORY_MANAGEMENT_INTERNALS_HPP__
#define CITRUS_ENGINE_MEMORY_MANAGEMENT_INTERNALS_HPP__

#include <cstdint>
#include "include/core/extensions.hpp"
#define POOL_FREE_BLOCK_MAGIC 0x46534545
#define POOL_ALLOC_BLOCK_MAGIC 0x4E4F474F

namespace engine
{
	namespace internals
	{
		// Pool block
		class poolBlock
		{
			public:
				union
				{
					// Attempt to force compress the structs
					union
					{
						// Header for a contigous free section
						struct
						{
							// Small magic number for a free section
							uint32_t fmagic;
							// Size of section, in blocks
							int fsize;
							// Next contigous section, NULL if last
							poolBlock *next;
							poolBlock *last;
						};
						// Header for an allocated section
						struct
						{
							// Small magic number for an allocated section
							uint32_t amagic;
							// Size of section, in blocks
							int asize;
						};
					};
					// Expand the size to 32 bytes
					uint8_t b[32];
				};
		};

		// The pool, as a class, for convience
		class Pool
		{
			public:
				// Is the pool locked?
				bool locked;
				// The start of the pool
				poolBlock *start;
				// The first free section header block
				poolBlock *head;
				// The last free section header block
				poolBlock *tail;
				// Size, allocated immediately so as to stay contigous, in blocks
				size_t size;

				// Allocate some blocks
				void *allocate(int blocks);
				// Realloc
				void *reallocate(void *ptr, int blocks);
				// Free some blocks
				void free(void *ptr);
				
				// Wait
				OPERATOR void wait()
				{
					while(locked);
					return;
				}

				Pool();
				~Pool();
		};

		// Main memory pool
		Pool pool;
	};
};

#endif
