/*
*   name: src/core/mem.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for core/mem.hpp
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifdef __unix__

#include <unistd.h>
#include <sys/mman.h>

#elif defined(_WIN32)

#include <Windows.h>

#endif

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <cstdint>

// We need to override b2Alloc_Default and b2Free_Default
#include <box2d/b2_settings.h>

#include "core/errno.hpp"
#include "core/mem.hpp"
#include "core/mem_int.hpp"

engine::internals::Pool pool;

OPERATOR bool validatePointer(uintptr_t ptr)
{
	return (ptr != NULL) && (ptr < (uintptr_t)(pool.start + pool.size)) && (ptr > (uintptr_t)(pool.start));
}

// Used to make the code in free() and reallocate() clearer
OPERATOR void mergeBlocks(engine::internals::poolBlock *nptr)
{
	engine::internals::poolBlock *tptr = nptr->next;
	if(nptr->next == POOL_END) return;

	while(true) // An infinite loop is fine, when the time is right it will return
	{
		while(tptr->fmagic != POOL_FREE_BLOCK_MAGIC || tptr->amagic != POOL_ALLOC_BLOCK_MAGIC) tptr = tptr->next;

		if(tptr->amagic == POOL_ALLOC_BLOCK_MAGIC) return;

		nptr->fsize += tptr->fsize;
		nptr->next = tptr->next;

		if(nptr->next != POOL_END)	tptr->next->last = nptr;
		else return;
		tptr->fmagic = 0;
	}
}

// Used to make reallocate() fully atomic
OPERATOR void *alloc(int blocks)
{
	engine::internals::poolBlock *bptr = engine::internals::pool.head;

alloc_goto:
	if(bptr->next == POOL_END)
	{
		if(bptr.fsize + blocks + 1 > engine::internals::pool.limit)
		{
			if(_POOL_LIMIT_IS_HARD_ || limitExceeded)
			{
				engine::errorcode() = ENGINE_NO_MEM;
				return -1;
			}
			else
			{
				engine::errorcode() = ENGINE_SOFT_MEM_LIMIT_REACHED;
				limitExceeded = true;
				#ifndef _WIN32

				void *ptr = mmap((void*)((uintptr_t)engine::internals::pool.start + _POOL_SIZE_), 
					_POOL_EXPANSION_SIZE_, PROT_WRITE | PROT_READ, MAP_ANON | MAP_FIXED_NOREPLACE |
					
					#if (_POOL_SIZE_ + _POOL_EXPANSION_SIZE_) % (1024ull * 1024ull * 1024ull) == 0 || (_POOL_SIZE_ + _POOL_EXPANSION_SIZE_) % (1024ull * 1024ull * 2ull) == 0
					MAP_HUGETLB | 
					#if (_POOL_SIZE_ + _POOL_EXPANSION_SIZE_) % (1024 * 1024 * 1024) == 0
					(30 << MAP_HUGE_SHIFT)
					#else
					(21 << MAP_HUGE_SHIFT)
					#endif,
					
					0, 0);

				#else

				void *ptr = VirtualAlloc((void*)((uintptr_t)engine::internals::pool.start + _POOL_SIZE_)
					_POOL_EXPANSION_SIZE_, MEM_COMMIT, PAGE_READWRITE);
				#endif

				if((uintptr_t)ptr != ((uintptr_t)pool.start + _POOL_SIZE_))
				{
					engine::errorcode() = ENGINE_NO_MEM;
					
					#ifndef _WIN32
					munmap(ptr, _POOL_EXPANSION_SIZE_);
					#else
					VirtualFree(ptr, _POOL_EXPANSION_SIZE_, 0);
					#endif

					return -1;
				}

				engine::internals::pool.size += _POOL_EXPANSION_SIZE_/32;
			}
		}

		nptr->next = POOL_END;
		nptr->last = bptr;
		nptr->last->next = nptr;
		nptr->fsize = bptr->fsize - blocks - 1;
		nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
		bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->asize = blocks;
		return (void*)(bptr+1);
	}
	else if(bptr->fsize == blocks)
	{
		bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->asize = blocks;
		return (void*)(bptr+1);
	}
	else if(bptr->fsize > blocks + 4)
	{
		engine::internals::poolBlock *nptr = bptr + blocks + 1;
		nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
		nptr->fsize = bptr->fsize - blocks - 1;
		nptr->last = bptr;
		nptr->next = bptr->next;
		bptr->next = nptr;
		nptr->next->last = nptr;
		bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->asize = blocks;
		return (void*)(bptr+1);
	}
	else if(bptr->fsize + bptr->next->fsize + 1 > blocks + 4 && bptr->next->fmagic == POOL_FREE_BLOCK_MAGIC)
	{
		engine::internals::poolBlock *nptr = bptr + blocks + 1;
		size_t totalSize = bptr->fsize + bptr->next->fsize + 1;
		bptr->next = bptr->next->next;
		bptr->next->last = nptr;
		bptr->asize = blocks;
		bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
		nptr->fsize = totalSize - 1 - blocks;
		nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
		nptr->next = bptr->next;
		bptr->next = nptr;
		return (void*)(bptr+1);
	}
	else if(bptr->fsize + bptr->next->fsize + 1 => blocks && bptr->next->fmagic == POOL_FREE_BLOCK_MAGIC)
	{
		size_t size = bptr->fsize + bptr->next->fsize + 1;
		bptr->next = bptr->next->next;
		bptr->next->last = bptr;
		bptr->asize = size;
		bptr->amagic POOL_ALLOC_BLOCK_MAGIC;
		return (void*)(bptr+1);
	}
	else
	{
		bptr = bptr->next;
		while(bptr->fmagic != POOL_FREE_BLOCK_MAGIC) bptr = bptr->next;
		goto alloc_goto;
	}
}

void *engine::internals::Pool::allocate(int blocks)
{
	// Wait for the pool to unlock and lock it.
	lock();

	void *ret = alloc(blocks);
	head = start;
	while(head->fmagic != POOL_FREE_BLOCK_MAGIC && head->next != POOL_END) head = head->next;

	unlock();
	return (void*)ret;
}

void *engine::internals::Pool::reallocate(void *ptr, int blocks)
{
	engine::internals::poolBlock *bptr = (engine::internals::poolBlock*)ptr - 1;
	
	if(!validatePointer((uintptr_t)ptr))
	{
		engine::errorcode() = ENGINE_MEMREALLOC_INVALID_PTR;
		return this->allocate(blocks);
	}
	else if(bptr->amagic != POOL_ALLOC_BLOCK_MAGIC)
	{
		engine::errorcode() = ENGINE_MEMREALLOC_INVALID_PTR;
		return this->allocate(blocks);
	}
	else if(!blocks)
	{
		this->free(bptr);
		engine::errorcode() = ENGINE_MEMREALLOC_INVALID_PTR;
		return ptr;
	}

	lock();

	if(bptr->asize == blocks || (bptr->asize <= blocks + 4 && bptr->asize > blocks) || (bptr->asize => blocks - 4 && bptr->asize < blocks))
	{
		unlock();
		return ptr;
	}
	else if(bptr->asize < blocks - 4)
	{
		engine::internals::poolBlock *nptr = bptr + blocks + 1;
		nptr->next = bptr->next;
		bptr->next->last = nptr;
		bptr->next = nptr;
		nptr->last = bptr;
		nptr->fsize = bptr->asize - blocks - 1;
		nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
		bptr->asize = blocks;
		unlock();
		return ptr;
	}
	else
	{
		engine::internals::poolBlock *rptr = alloc(blocks);
		bptr->fsize = bptr->asize;
		bptr->fmagic = POOL_FREE_BLOCK_MAGIC;

		// No need for preprocessor nonsense, ymm_memcpy converts to xmm_memcpy if AVX is disabled
		ymm_memcpy(rptr, bptr + i, bptr->fsize);

		unlock();
		return rptr;
	}
}

void engine::internals::Pool::free(engine::internals::poolBlock *bptr)
{
	lock();

	if(!validatePointer((uintptr_t)bptr))
	{
		engine::errorcode() = ENGINE_MEMFREE_INVALID_PTR;
		unlock();
		return;
	}
	
	if(bptr->amagic == POOL_ALLOC_BLOCK_MAGIC)
	{
		bptr->fsize = bptr->asize;
		bptr->fmagic = POOL_FREE_BLOCK_MAGIC;
	}
	else
	{
		engine::errorcode() = ENGINE_MEMFREE_INVALID_PTR;
	}

	// Update the variables
	engine::internals::poolBlock *tptr = start;
	while(tptr->fmagic != POOL_FREE_BLOCK_MAGIC) tptr = tptr->next;
	head = tptr;

	// Merge all the blocks
	while(tptr->next != POOL_END)
	{
		mergeBlocks(tptr);
		tptr = tptr->next;
	}

	unlock();
	return;
}

void *engine::memalloc(size_t size)
{
	// Make a pool allocation with suitable rounding
	return engine::internals::pool.allocate((size & 0x1F) ? (size >> 5) + 1 : size >> 5);
}

void *engine::memrealloc(void *ptr, size_t size)
{
	// Perform the actual reallocation with proper rounding, using bitwise operations incase the compiler is dumb and doesn't perform the optimizations
	return engine::internals::pool.reallocate(ptr, (size & 0x1F) ? (size >> 5) + 1 : size >> 5);
}

void engine::memfree(void *ptr)
{
	engine::internals::pool.free((engine::internals::poolBlock*)ptr - 1);
}

void *engine::zmalloc(size_t items, size_t size)
{
	size_t m = ((size * items) & 0x1F) ? ((size * items) >> 5) + 1 : (size * items) >> 5;
	void *ret = engine::internals::pool.allocate(m);
	ymm_memset(ret, 0, m);
	return ret;
}

size_t engine::memlen(void *ptr)
{
	return (((engine::internals::poolBlock*)ptr) - 1)->fmagic == POOL_FREE_BLOCK_MAGIC ? (((engine::internals::poolBlock*)ptr) - 1)->asize << 5 : (engine::errorcode = ENGINE_MEMFREE_INVALID_PTR);
}

int engine::__memalloc_posix_memalign(void **memptr, size_t alignment, size_t size)
{
	void **ptrs = engine::memalloc(8);
	size_t ptr = 0;

	if(alignment % sizeof(void*))
	{
		errno = EINVAL;
		return EINVAL;
	}

	// Unfortunately, we need to iterate through a bunch of different buffers, wasting a ton of memory.
	while(
		(uintptr_t)(ptrs[ptr - 1] = engine::memalloc(size)) % alignment
		&& engine::errorcode != ENGINE_NO_MEM
	) ptrs = engine::memrealloc(ptrs, ++ptr);

	if(engine::errorcode != ENGINE_NO_MEM)
	{
		for(size_t i = 0; i < ptr; i++)
			engine::memfree(ptrs[i]);

		engine::memfree(ptrs);
		errno = ENOMEM;
		return ENOMEM;
	}
	else
	{
		ptr--;
		for(size_t i = 0; i < ptr; i++)
			engine::memfree(ptrs[i]);

		*memptr = ptrs[ptr];
		engine::memfree(ptrs);
		return 0;
	}
}

// b2Alloc_Default and b2Free_Default overrides
B2_API void* b2Alloc_Default(int32_t size)
{
	return engine::memalloc(size);
}

B2_API void b2Free_Default(void *mem)
{
	engine::memfree(mem);
}