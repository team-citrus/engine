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

#include <cstring>
#include <cstdint>

// We need to override b2Alloc_Default and b2Free_Default
#include <box2d/b2_settings.h>

#include "core/errno.hpp"
#include "core/mem.hpp"
#include "core/mem_int.hpp"

engine::internals::Pool pool;

// Used to make the code in free() and reallocate() clearer
OPERATOR void mergeBlocks(engine::internals::poolBlock *nptr)
{
	engine::internals::poolBlock *tptr = nptr + 1;
	if(nptr->next == POOL_END) return;

	while(true) // An infinite loop is fine, when the time is right it will return
	{
		while(tptr->fmagic != POOL_FREE_BLOCK_MAGIC || tptr->amagic != POOL_ALLOC_BLOCK_MAGIC) tptr++;

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
					_POOL_EXPANSION_SIZE_, PROT_WRITE | PROT_READ, MAP_ANON | MAP_FIXED_NOREPLACE, 0, 0);

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
	while(head->fmagic != POOL_FREE_BLOCK_MAGIC && head->next != ) head = head->next;

	unlock();
	return (void*)ret;
}

void *engine::internals::Pool::reallocate(void *ptr, int blocks)
{
	engine::internals::poolBlock *bptr = (engine::internals::poolBlock*)ptr - 1;
	
	if(ptr == NULL)
	{
		engine::errorcode() = ENGINE_MEMREALLOC_INVALID_PTR;
		return this->return this->allocate(blocks);
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

		// No need for preprocessor nonsense, ymm_memcpy converts to xmm_memcpy on if AVX is disabled
		ymm_memcpy(rptr, bptr + i, bptr->fsize);

		unlock();
		return rptr;
	}
}

void engine::internals::Pool::free(engine::internals::poolBlock *bptr)
{
	lock();
	if(bptr + 1 == NULL)
	{
		engine::errorcode() = ENGINE_MEMFREE_INVALID_PTR;
		return;
	}
	engine::errorcode() = bptr->fmagic == POOL_FREE_BLOCK_MAGIC ? ENGINE_MEMFREE_INVALID_PTR : engine::errorcode ;
	bptr->fsize = bptr->asize;
	bptr->fmagic = POOL_FREE_BLOCK_MAGIC;

	// Update the variables
	engine::internals::poolBlock *tptr = start;
	while(tptr->fmagic != POOL_FREE_BLOCK_MAGIC) tptr++;
	head = tptr;

	// Merge all the blocks
	while(tptr->next != NULL)
	{
		mergeBlocks(tptr);
		tptr = tptr->next;
	}

	unlock();
	return;
}

void *engine::memalloc(size_t size, uint16_t flags)
{
	// Make a pool allocation with suitable rounding
	return engine::internals::pool.allocate((size << 59) ? (size >> 5) + 1 : size >> 5);
}

void *engine::memrealloc(void *ptr, size_t size, uint16_t flags)
{
	// Perform the actual reallocation with proper rounding, using bitwise operations incase the compiler is dumb and doesn't perform the optimizations
	return engine::internals::pool.reallocate(ptr, (size << 59) ? (size >> 5) + 1 : size >> 5);
}

void engine::memfree(void *ptr)
{
	engine::internals::pool.free((engine::internals::poolBlock*)ptr - 1);
}

// b2Alloc_Default and b2Free_Default overrides
B2_API void* b2Alloc_Default(int32_t size)
{
	return engine::memalloc(size, MEM_FLAG_UNIT_BYTE);
}

B2_API void b2Free_Default(void *mem)
{
	engine::memfree(mem);
}
