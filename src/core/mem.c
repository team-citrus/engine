/*
*   name: src/core/mem.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for core/mem.hpp
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
#include "core/os.h"

#ifdef CITRUS_ENGINE_UNIX

#include <unistd.h>
#include <sys/mman.h>

#else

#include <Windows.h>

#endif

#include <stdint.h>
#include <stdatomic.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "core/extensions.h"
#include "core/simd.h"

#define POOL_FREE_BLOCK_MAGIC 0x465245454E554D00ull
#define POOL_ALLOC_BLOCK_MAGIC 0x414C4C4F43454400ull
#define POOL_END ((void*)-1ull)

#ifndef _POOL_SIZE_
#define _POOL_SIZE_ (1024ull * 1024ull * 1024ull * 2ull)
#endif

#ifndef _POOL_EXPANSION_SIZE_
#define _POOL_EXPANSION_SIZE_ _POOL_SIZE_
#endif

#ifndef _POOL_LIMIT_IS_HARD_
#define _POOL_LIMIT_IS_HARD_ true
#endif

// Pool block
typedef struct PoolBlock
{
	union
	{
		// Header for a contigous free section
		struct
		{
			uint64_t magic;
			// Size of section, in blocks
			uint32_t size;
			// Next contigous section, POOL_END if last
			struct PoolBlock *next;
			struct PoolBlock *last;
		};
		
		// Expand the size to 32 bytes
		uint_least8_t __force_size[32];
	};
} PoolBlock;

typedef struct Pool
{
	// The start of the pool
	PoolBlock *start;
	// The first free section header block
	PoolBlock *head;
	// Size, allocated immediately so as to stay contigous, in blocks
	size_t size;
	// Limit of the pool, if an address goes above this, bad things happen.
	uintptr_t limit;
	// For a soft limit
	bool limitExceeded;
} Pool;

Pool init()
{
	Pool ret;
	ret.size = _POOL_SIZE_/32;

	#ifdef CITRUS_ENGINE_UNIX
	ret.start = (poolBlock*)mmap(NULL, _POOL_SIZE_, PROT_WRITE | PROT_READ, MAP_ANON |
					
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

	ret.start = VirtualAlloc(NULL, _POOL_SIZE_, MEM_COMMIT | MEM_RESERVE
			
	#if (_POOL_SIZE_ + _POOL_EXPANSION_SIZE_) % (1024ull * 1024ull * 1024ull) == 0 || (_POOL_SIZE_ + _POOL_EXPANSION_SIZE_) % (1024ull * 1024ull * 2ull) == 0
	| MEM_LARGE_PAGES
	#endif

	, 0);
	#endif

	ret.limit = ((uintptr_t)ret.start) + _POOL_SIZE_;
	ret.limitExceeded = false;

	ret.start->magic = POOL_FREE_BLOCK_MAGIC;
	ret.start->next = POOL_END;
	ret.start->size = ret.size;
	ret.start->last = NULL;
	ret.head = ret.start;
}

Pool pool;
static _Atomic bool mutex;

__attribute__((__always_inline__)) void accquire()
{
	while(mutex)
		spinlock_pause();

	mutex = true;
}

__attribute__((__always_inline__)) void release()
{
	mutex = false;
}

__attribute__((__always_inline__)) bool validatePointer(uintptr_t ptr)
{
	return (ptr != NULL) && (ptr < (uintptr_t)(pool.start + pool.size)) && (ptr > (uintptr_t)(pool.start));
}

// Used to make the code in free() and reallocate() clearer
__attribute__((__always_inline__)) void mergeBlocks(PoolBlock *nptr)
{
	PoolBlock *tptr = nptr->next;
	if(nptr->next == POOL_END) return;

	while(true) // An infinite loop is fine, when the time is right it will return
	{
		tptr = tptr->next;

		if(tptr->magic == POOL_ALLOC_BLOCK_MAGIC) return;

		nptr->size += tptr->size;
		nptr->next = tptr->next;

		if(nptr->next != POOL_END)	tptr->next->last = nptr;
		else return;
	}
}

// Used to make reallocate() fully atomic
__attribute__((__always_inline__)) void *alloc(int blocks)
{
	PoolBlock *bptr = pool.head;

alloc_goto:
	if(bptr->next == POOL_END)
	{
		if((uintptr_t)(bptr + blocks + 1) > pool.limit)
		{
			if(_POOL_LIMIT_IS_HARD_ || pool.limitExceeded)
			{
				return -1;
			}
			else
			{
				pool.limitExceeded = true;

				#ifdef CITRUS_ENGINE_UNIX

				void *ptr = mmap((void*)((uintptr_t)engine::internals::pool.start + _POOL_SIZE_), 
					_POOL_EXPANSION_SIZE_, PROT_WRITE | PROT_READ, MAP_ANON | MAP_FIXED_NOREPLACE |
					
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

				void *ptr = VirtualAlloc((LPVOID)((uintptr_t)pool.start + _POOL_EXPANSION_SIZE_),
					_POOL_EXPANSION_SIZE_, MEM_COMMIT, PAGE_READWRITE);
				#endif

				if((uintptr_t)ptr != ((uintptr_t)pool.start + _POOL_SIZE_))
				{
					#ifdef CITRUS_ENGINE_UNIX
					munmap(ptr, _POOL_EXPANSION_SIZE_);
					#else
					VirtualFree(ptr, _POOL_EXPANSION_SIZE_, 0);
					#endif

					return (void*)-1;
				}

				pool.size += _POOL_EXPANSION_SIZE_/32;
			}
		}

		PoolBlock *nptr = bptr + blocks + 1;

		nptr->next = POOL_END;
		nptr->last = bptr;
		nptr->last->next = nptr;
		nptr->size = bptr->size - blocks - 1;
		nptr->magic = POOL_FREE_BLOCK_MAGIC;
		bptr->magic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->size = blocks;
		return (void*)(bptr+1);
	}
	else if(bptr->size == blocks)
	{
		bptr->magic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->size = blocks;

		return (void*)(bptr+1);
	}
	else if(bptr->size > blocks + 4)
	{
		PoolBlock *nptr = bptr + blocks + 1;

		nptr->magic = POOL_FREE_BLOCK_MAGIC;
		nptr->size = bptr->size - blocks - 1;
		nptr->last = bptr;
		nptr->next = bptr->next;
		bptr->next = nptr;
		nptr->next->last = nptr;
		bptr->magic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->size = blocks;

		return (void*)(bptr+1);
	}
	else if(bptr->size + bptr->next->size + 1 > blocks + 4 && bptr->next->magic == POOL_FREE_BLOCK_MAGIC)
	{
		PoolBlock *nptr = bptr + blocks + 1;
		size_t totalSize = bptr->size + bptr->next->size + 1;

		bptr->next = bptr->next->next;
		bptr->next->last = nptr;
		bptr->size = blocks;
		bptr->magic = POOL_ALLOC_BLOCK_MAGIC;
		nptr->size = totalSize - 1 - blocks;
		nptr->magic = POOL_FREE_BLOCK_MAGIC;
		nptr->next = bptr->next;
		bptr->next = nptr;

		return (void*)(bptr+1);
	}
	else if(bptr->size + bptr->next->size + 1 >= blocks && bptr->next->magic == POOL_FREE_BLOCK_MAGIC)
	{
		size_t size = bptr->size + bptr->next->size + 1;

		bptr->next = bptr->next->next;
		bptr->next->last = bptr;
		bptr->size = size;
		bptr->magic = POOL_ALLOC_BLOCK_MAGIC;
		
		return (void*)(bptr+1);
	}
	else
	{
		bptr = bptr->next;
		while(bptr->magic != POOL_FREE_BLOCK_MAGIC) bptr = bptr->next;
		goto alloc_goto;
	}
}

void *allocate(int blocks)
{
	// Wait for the pool to unlock and lock it.
	accquire();

	void *ret = alloc(blocks);
	pool.head = pool.start;
	while(pool.head->magic != POOL_FREE_BLOCK_MAGIC && pool.head->next != POOL_END) pool.head = pool.head->next;

	release();
	return (void*)ret;
}

void *reallocate(void *ptr, int blocks)
{
	PoolBlock *bptr = (PoolBlock*)ptr - 1;
	
	if(!validatePointer((uintptr_t)ptr))
	{
		return allocate(blocks);
	}
	else if(bptr->magic != POOL_ALLOC_BLOCK_MAGIC)
	{
		return allocate(blocks);
	}
	else if(!blocks)
	{
		_free(bptr);
		return ptr;
	}

	accquire();

	if(bptr->size == blocks || (bptr->size <= blocks + 4 && bptr->size > blocks) || (bptr->size >= blocks - 4 && bptr->size < blocks))
	{
		release();
		return ptr;
	}
	else if(bptr->size < blocks - 4)
	{
		PoolBlock *nptr = bptr + blocks + 1;
		nptr->next = bptr->next;
		bptr->next->last = nptr;
		bptr->next = nptr;
		nptr->last = bptr;
		nptr->size = bptr->size - blocks - 1;
		nptr->magic = POOL_FREE_BLOCK_MAGIC;
		bptr->size = blocks;
		release();
		return ptr;
	}
	else
	{
		PoolBlock *rptr = (PoolBlock*)alloc(blocks);
		bptr->size = bptr->size;
		bptr->magic = POOL_FREE_BLOCK_MAGIC;

		// No need for preprocessor nonsense, ymm_memcpy converts to xmm_memcpy if AVX is disabled
		ymm_memcpy(rptr, bptr + 1, bptr->size);

		release();
		return rptr;
	}
}

void _free(PoolBlock *bptr)
{
	accquire();

	if(!validatePointer((uintptr_t)bptr))
	{
		release();
		return;
	}
	
	if(bptr->magic == POOL_ALLOC_BLOCK_MAGIC)
	{
		bptr->size = bptr->size;
		bptr->magic = POOL_FREE_BLOCK_MAGIC;
	}

	// Update the variables
	PoolBlock *tptr = pool.start;
	while(tptr->magic != POOL_FREE_BLOCK_MAGIC) tptr = tptr->next;
	pool.head = tptr;

	// Merge all the blocks
	while(tptr->next != POOL_END)
	{
		mergeBlocks(tptr);
		tptr = tptr->next;
	}

	release();
	return;
}

void *memalloc(size_t size)
{
	// Make a pool allocation with suitable rounding
	return allocate((size & 0x1F) ? (size >> 5) + 1 : size >> 5);
}

void *memrealloc(void *ptr, size_t size)
{
	// Perform the actual reallocation with proper rounding, using bitwise operations incase the compiler is dumb and doesn't perform the optimizations
	return reallocate(ptr, (size & 0x1F) ? (size >> 5) + 1 : size >> 5);
}

void memfree(void *ptr)
{
	_free((PoolBlock*)ptr - 1);
}

void zmalloc(size_t items, size_t size)
{
	size_t m = ((size * items) & 0x1F) ? ((size * items) >> 5) + 1 : (size * items) >> 5;
	void *ret = allocate(m);
	ymm_memset(ret, 0, m);
	return ret;
}

size_t memlen(void *ptr)
{
	return (((PoolBlock*)ptr) - 1)->magic == POOL_FREE_BLOCK_MAGIC ? (((PoolBlock*)ptr) - 1)->size << 5 : ~0ull;
}

size_t allocated()
{
	size_t ret;
	PoolBlock *ptr = pool.start;

	while(ptr != POOL_END)
	{
		if(ptr->magic == POOL_ALLOC_BLOCK_MAGIC)
			ret += ptr->size;

		ptr = ptr->next;
	}

	return ret << 5;
}

size_t freed()
{
	size_t ret;
	PoolBlock *ptr = pool.start;

	while(ptr != POOL_END)
	{
		if(ptr->magic == POOL_FREE_BLOCK_MAGIC)
			ret += ptr->size;
			
		ptr = ptr->next;
	}

	return ret << 5;
}

// malloc is a weak symbol, we can override it
ALIAS(memalloc) void *malloc(size_t size);

// realloc is a weak symbol, we can override it
ALIAS(memrealloc) void *realloc(void *ptr, size_t size);

// calloc is a weak symbol, we can override it
ALIAS(zmalloc) void *calloc(size_t items, size_t size);

// free is a weak symbol, we can override it
ALIAS(memfree) void free(void *ptr);