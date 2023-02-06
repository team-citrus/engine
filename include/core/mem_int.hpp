/*
*   name: include/core/mem_int.hpp
*   origin: Citrus Engine
*   purpose: Provide memory management internals
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_MEMORY_MANAGEMENT_INTERNALS_HPP__
#define CITRUS_ENGINE_MEMORY_MANAGEMENT_INTERNALS_HPP__

#ifndef _WIN32
#include <unistd.h>
#else
#include <Windows.h>
#endif

#include <cstdint>
#include <stdatomic.h>
#include "core/extensions.hpp"
#include "core/simd.h"

#define POOL_FREE_BLOCK_MAGIC 0x46534545
#define POOL_ALLOC_BLOCK_MAGIC 0x4E4F474F

#ifndef _POOL_SIZE_
#define _POOL_SIZE_ 1024 * 1024 * 1024 * 2

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
				atomic_flag locked;
				// The start of the pool
				poolBlock *start;
				// The first free section header block
				poolBlock *head;
				// Size, allocated immediately so as to stay contigous, in blocks
				size_t size;

				// Allocate some blocks
				void *allocate(int blocks);
				// Realloc
				void *reallocate(void *ptr, int blocks);
				// Free some blocks
				void free(engine::internals::poolBlock *bptr);
				
				// Wait
				OPERATOR void wait()
				{
					while(atomic_flag_test_and_set(&locked))
						spinlock_pause();
					return;
				}

				Pool()
				{
					#ifndef _WIN32
					start = mmap(NULL, _POOL_SIZE_, PROT_WRITE | PROT_READ, MAP_ANON, 0, 0);
					#else
					start = VirtualAlloc(NULL, _POOL_SIZE_, 0, 0);
					#endif
					size = _POOL_SIZE_/32;
				}
				~Pool()
				{
					#ifndef _WIN32
					munmap(start, _POOL_SIZE_);
					#else
					VirtualFree(start, _POOL_SIZE_, 0);
					#endif
				}
		};

		// Main memory pool
		extern Pool pool;
	};
};

#endif
