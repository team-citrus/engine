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

#include "core/errorcode.hpp"
#include "core/mem.hpp"
#include "core/mem_int.hpp"

engine::internals::Pool pool;

// Used to make the code in free() and reallocate() clearer
OPERATOR void mergeBlocks(engine::internals::poolBlock *nptr)
{
	engine::internals::poolBlock *tptr = nptr + 1;
	if(nptr->next == ENGINE_POOL_END) return;

	while(true) // An infinite loop is fine, when the time is right it will return
	{
		while(tptr->fmagic != POOL_FREE_BLOCK_MAGIC || tptr->amagic != POOL_ALLOC_BLOCK_MAGIC) tptr++;

		if(tptr->amagic == POOL_ALLOC_BLOCK_MAGIC) return;

		nptr->fsize += tptr->fsize;
		nptr->next = tptr->next;

		if(nptr->next != ENGINE_POOL_END)	tptr->next->last = nptr;
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
			if(_POOL_LIMIT_IS_HARD_)
			{
				engine::errorcode = ENGINE_NO_MEM;
				return -1;
			}
			else
			{
				// TODO: Expand past limit
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
		engine::errorcode = ENGINE_MEMREALLOC_INVALID_PTR;
		return this->return this->allocate(blocks);
	}
	else if(bptr->amagic != POOL_ALLOC_BLOCK_MAGIC)
	{
		engine::errorcode = ENGINE_MEMREALLOC_INVALID_PTR;
		return this->allocate(blocks);
	}
	else if(!blocks)
	{
		this->free(bptr);
		engine::errorcode = ENGINE_MEMREALLOC_INVALID_PTR;
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
		void *rptr = alloc(blocks);
		bptr->fsize = bptr->asize;
		bptr->fmagic = POOL_FREE_BLOCK_MAGIC;

		memcpy(rptr, (void*)(bptr + 1), bptr->fsize);
		unlock();
		return rptr;
	}
}

void engine::internals::Pool::free(engine::internals::poolBlock *bptr)
{
	lock();
	if(bptr + 1 == NULL)
	{
		engine::errorcode = ENGINE_MEMREALLOC_INVALID_PTR;
		return;
	}
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
	// Apply the flags
	if(flags & MEM_FLAG_UNIT_DWORD)
		size *= 4;
	else if(flags & MEM_FLAG_UNIT_QWORD)
		size *= 8;
	else if(flags & MEM_FLAG_UNIT_WORD)
		size *= 2;
	else if(flags & MEM_FLAG_UNIT_PAGE)
		size *= 0x1000;
	else if(flags & MEM_FLAG_UNIT_KB)
		size *= 1024;
	else if(flags & MEM_FLAG_UNIT_MB)
		size *= 1024 * 1024;

	// Make a pool allocation with suitable rounding
	return engine::internals::pool.allocate((size % 32) ? size/32 + 1 : size/32);
}

void *engine::memrealloc(void *ptr, size_t size, uint16_t flags)
{
	// Apply the flags
	if(flags & MEM_FLAG_UNIT_DWORD)
		size *= 4;
	else if(flags & MEM_FLAG_UNIT_QWORD)
		size *= 8;
	else if(flags & MEM_FLAG_UNIT_WORD)
		size *= 2;
	else if(flags & MEM_FLAG_UNIT_PAGE)
		size *= 0x1000;
	else if(flags & MEM_FLAG_UNIT_KB)
		size *= 1024;
	else if(flags & MEM_FLAG_UNIT_MB)
		size *= 1024 * 1024;

	// Perform the actual reallocation with proper rounding
	return engine::internals::pool.reallocate(ptr, (size % 32) ? size/32 + 1 : size/32);
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
