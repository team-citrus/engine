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
#include <sys/mman.h>
#else
#include <Windows.h>
#endif

#include <cstdint>
#include <atomic>
#include "../core/extensions.h"
#include "../core/simd.h"

#define POOL_FREE_BLOCK_MAGIC 0x465245454E554D00ull
#define POOL_ALLOC_BLOCK_MAGIC 0x414C4C4F43454400ull
#define POOL_END -1ull

#ifndef _POOL_SIZE_
#define _POOL_SIZE_ (1024ull * 1024ull * 1024ull * 2ull)
#endif

#ifndef _POOL_EXPANSION_SIZE_
#define _POOL_EXPANSION_SIZE_ _POOL_SIZE_
#endif

#ifndef _POOL_LIMIT_IS_HARD_
#define _POOL_LIMIT_IS_HARD_ true
#endif

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
							uint64_t fmagic;
							// Size of section, in blocks
							uint32_t fsize;
							// Next contigous section, POOL_END if last
							poolBlock *next;
							poolBlock *last;
						};
						// Header for an allocated section
						struct
						{
							// Small magic number for an allocated section
							uint64_t amagic;
							// Size of section, in blocks
							uint32_t asize;
							poolBlock *__next;
							poolBlock *__last;
						};
					};
					// Expand the size to 32 bytes
					uint_least8_t __force_size[32];
				};
		};

		// The pool, as a class, for convience
		class Pool
		{
			public:
				// Is the pool locked?
				MUTEX std::atomic_bool locked;
				// The start of the pool
				poolBlock *start;
				// The first free section header block
				poolBlock *head;
				// Size, allocated immediately so as to stay contigous, in blocks
				size_t size = _POOL_SIZE_/32;
				// Limit of the pool, if an address goes above this, bad things happen.
				uintptr_t limit;
				// For a soft limit
				bool limitExceeded;

				// Allocate some blocks
				void *allocate(int blocks);
				// Realloc
				void *reallocate(void *ptr, int blocks);
				// Free some blocks
				void free(engine::internals::poolBlock *bptr);
				
				// Wait
				OPERATOR void wait()
				{
					while(locked.load())
						spinlock_pause();

					return;
				}

				// Lock it
				OPERATOR void lock()
				{
					while(locked.load())
						spinlock_pause();
					locked.store(true);

					return;
				}

				// Unlock it
				OPERATOR void unlock()
				{
					locked.store(false);
					return;
				}

				void init()
				{
					#ifdef CITRUS_ENGINE_UNIX
					start = (engine::internals::poolBlock*)mmap(NULL, _POOL_SIZE_, PROT_WRITE | PROT_READ, MAP_ANON |
					
					#if (_POOL_SIZE_ + _POOL_EXPANSION_SIZE_) % (1024ull * 1024ull * 1024ull) == 0 || (_POOL_SIZE_ + _POOL_EXPANSION_SIZE_) % (1024ull * 1024ull * 2ull) == 0
					MAP_HUGETLB | 
					#if (_POOL_SIZE_ + _POOL_EXPANSION_SIZE_) % (1024 * 1024 * 1024) == 0
					(30 << MAP_HUGE_SHIFT)
					#else
					(21 << MAP_HUGE_SHIFT)
					#endif,
					#endif
					
					0, 0);

					#else

					start = (engine::internals::poolBlock*)VirtualAlloc(NULL, _POOL_SIZE_, MEM_COMMIT | MEM_RESERVE
					
					#if (_POOL_SIZE_ + _POOL_EXPANSION_SIZE_) % (1024ull * 1024ull * 1024ull) == 0 || (_POOL_SIZE_ + _POOL_EXPANSION_SIZE_) % (1024ull * 1024ull * 2ull) == 0
					| MEM_LARGE_PAGES
					#endif

					, 0);
					#endif

					limit = ((uintptr_t)start) + _POOL_SIZE_;
					limitExceeded = false;

					start->fmagic = POOL_FREE_BLOCK_MAGIC;
					start->next = (poolBlock*)POOL_END;
					start->fsize = size;
					start->last = NULL;
					head = start;
				}
				~Pool()
				{
					#ifdef CITRUS_ENGINE_UNIX
					munmap(start, size * 32); // Should work because Linux merges continguous mappings with the same permisions
					#else
					VirtualFree(start, _POOL_SIZE_, 0);
					if(limitExceeded)
						VirtualFree((void*)((uintptr_t)start + _POOL_SIZE_), _POOL_EXPANSION_SIZE_, 0);
					#endif
				}
		};

		// Main memory pool
		extern Pool pool;
	};
};

#endif
