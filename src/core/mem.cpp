/*
*   name: src/core/mem.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for include/core/mem.hpp
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifdef __unix__

#include <unistd.h>
#include <sys/mmap.h>

#elif defined(_WIN32)

#include <Windows.h>

#endif

#include <cstring>
#include <cstdint>

// We need to override b2Alloc_Default and b2Free_Default
#include <box2d/b2_settings.h>

#include "include/core/mem.hpp"
#include "include/core/mem_int.hpp"

// Used to make the code in free() and reallocate() clearer
OPERATOR void mergeBlocks(engine::internals::poolBlock *nptr)
{
	engine::internals::poolBlock *tptr = nptr + 1;
	if(!nptr->next) return;

	while(tptr->fmagic != POOL_FREE_BLOCK_MAGIC || tptr->fmagic != POOL_ALLOC_BLOCK_MAGIC) tptr++;

	if(tptr->amagic == POOL_ALLOC_BLOCK_MAGIC) return;
	else if(tptr->next != NULL)
		nptr->next = NULL;
	else
		nptr->fsize += tptr->fsize;

	tptr->next->last = nptr;
	tptr->last->next = (tptr->last != nptr) ? nptr : tptr->last->next;
	nptr->next = tptr->next;
	nptr->last = (tptr->last != nptr) ? tptr->last : nptr->last;
	tptr->fmagic = 0;
}

// Used to make reallocate() fully atomic
OPERATOR void *alloc(int blocks)
{
	engine::internals::poolBlock *bptr = engine::internals::pool.head;
	if(bptr->next == NULL)
	{
		engine::internals::poolBlock *nptr = bptr + blocks;
		engine::internals::pool.head = nptr;
		nptr->next = NULL;
		nptr->last = bptr->last;
		nptr->last->next = nptr;
		nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
		bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->asize = blocks;
		return (void*)(bptr+1);
	}
	else if(bptr->fsize == blocks)
	{
		engine::internals::pool.head = bptr->next;
		bptr->last->next = bptr->next;
		bptr->next->last = bptr->last;
		bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->asize = blocks;
		return (void*)(bptr+1);
	}
	else if(bptr->fsize > blocks + 4)
	{
		engine::internals::poolBlock *nptr = bptr;
		nptr += blocks + 1;
		nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
		nptr->fsize = bptr->fsize - blocks - 1;
		nptr->last = bptr->last;
		bptr->last->next = nptr;
		bptr->next->last = nptr;
		nptr->next = bptr->next;
		bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->asize = blocks;
		engine::internals::pool.head = nptr;
		return (void*)(bptr+1);
	}
	else if(bptr->fsize < blocks)
	{
		bptr = bptr->next;
		while(true)
		{
			if(bptr->next == NULL)
			{
				engine::internals::poolBlock *nptr = bptr + blocks;
				nptr->next = NULL;
				nptr->last = bptr->last;
				nptr->last->next = nptr;
				nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
				bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
				bptr->asize = blocks;
				return (void*)(bptr+1);
			}
			else if(bptr->fsize == blocks)
			{
				bptr->last->next = bptr->next;
				bptr->next->last = bptr->last;
				bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
				bptr->asize = blocks;
				return (void*)(bptr+1);
			}
			else if(bptr->fsize > blocks + 4)
			{
				engine::internals::poolBlock *nptr = bptr;
				nptr += blocks + 1;
				nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
				nptr->fsize = bptr->fsize - blocks - 1;
				nptr->last = bptr->last;
				bptr->last->next = nptr;
				bptr->next->last = nptr;
				nptr->next = bptr->next;
				bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
				bptr->asize = blocks;
				bptr->last->next = nptr;
				return (void*)(bptr+1);
			}
			bptr = bptr->next;
		}
	}
}

void *engine::internals::Pool::allocate(int blocks)
{
	// Wait for the pool to unlock
	wait();
	locked = true;
	void *ret = alloc(blocks);
	locked = false;
	return ret;
}

void *engine::internals::Pool::reallocate(void *ptr, int blocks)
{
	engine::internals::poolBlock *bptr = (engine::internals::poolBlock*)((uintptr_t)ptr - sizeof(engine::internals::poolBlock));
	if(bptr->amagic != POOL_ALLOC_BLOCK_MAGIC)
		return this->allocate(blocks);
	else if(!blocks)
	{
		this->free(bptr);
		return ptr;
	}

	wait();
	locked = true;

	else if(bptr->asize == blocks)
		return ptr;
	else if(bptr->asize > blocks)
	{
		engine::internals::poolBlock *nptr = bptr + blocks + 1;
		nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
		nptr->fsize = bptr->asize - blocks;

		mergeBlocks(nptr);

		return (void*)(bptr+1);
	}
	else if(bptr->asize < blocks)
	{
		engine::internals::poolBlock *nptr = bptr;
		while(nptr->fmagic != POOL_FREE_BLOCK_MAGIC) nptr++;
		if(nptr->next == NULL)
		{
			bptr->asize = blocks;
			nptr->last->next = bptr + blocks + 1;
			nptr = nptr->last->next;
			nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
			nptr->next = NULL;
		}
		else if(nptr->fsize + bptr->asize >= blocks && nptr->fsize + bptr->asize < blocks + 4)
		{
			nptr->fmagic = 0;
			nptr->last->next = nptr->next;
			nptr->next->last = nptr->last;
			bptr->fsize += nptr->asize + 1;
		}
		else if(nptr->fsize + bptr->asize > blocks)
		{
			while(bptr->asize != blocks)
			{
				*(nptr+1) = *nptr;
				nptr->fmagic = 0;
				nptr++;
				nptr->next->last++;
				nptr->last->next++;
				nptr->fsize--;
				bptr->asize++;
			}
		}
		else
		{
			locked = false;
			nptr = (engine::internals::poolBlock*)alloc(blocks);
			memcpy(nptr+1, bptr+1, bptr->asize * 32);
			free(bptr+1);
			bptr = nptr;
		}

		locked = false;
		return (void*)(bptr+1);
	}
}

void engine::internals::Pool::free(engine::internals::poolBlock *bptr)
{
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
B2_API void* b2Alloc_Default(int32 size)
{
	return engine::memalloc(size, MEM_FLAG_UNIT_BYTE);
}

B2_API void b2Free_Default(void *mem)
{
	engine::memfree(mem);
}