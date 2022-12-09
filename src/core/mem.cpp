#ifdef __unix__

#include <unistd.h>
#include <sys/mmap.h>

#elif defined(_WIN32)

#include <Windows.h>

#endif

#include <cstdint>

#include "include/core/mem.hpp"
#include "include/core/mem_int.hpp"

void *engine::internals::Pool::allocate(int blocks, int flags)
{
	engine::internals::poolBlock *bptr = head;
	this->wait();
	locked = true;

	if(bptr->next == NULL)
	{
		engine::internals::poolBlock *nptr = bptr + blocks;
		head = nptr;
		nptr->next = NULL;
		nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
		bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->asize = blocks;
		bptr->flags = flags;
		locked = false;
		return (void*)(bptr+1);
	}
	else if(bptr->fsize == blocks)
	{
		head = bptr->next;
		bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->asize = blocks;
		bptr->flags = flags;
		locked = false;
		return (void*)(bptr+1);
	}
	else if(bptr->fsize > blocks + 4)
	{
		engine::internals::poolBlock *nptr = bptr;
		nptr += blocks;
		nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
		nptr->fsize = bptr->fsize - blocks - 1;
		nptr->next = bptr->next;
		bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
		bptr->asize = blocks;
		head = nptr;
		locked = false;
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
				bptr->last->next = nptr;
				nptr->next = NULL;
				nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
				bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
				bptr->asize = blocks;
				bptr->flags = flags;
				locked = false;
				return (void*)(bptr+1);
			}
			else if(bptr->fsize == blocks)
			{
				bptr->last->next = bptr->next;
				bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
				bptr->asize = blocks;
				bptr->flags = flags;
				locked = false;
				return (void*)(bptr+1);
			}
			else if(bptr->fsize > blocks + 4)
			{
				engine::internals::poolBlock *nptr = bptr;
				nptr += blocks;
				nptr->fmagic = POOL_FREE_BLOCK_MAGIC;
				nptr->fsize = bptr->fsize - blocks - 1;
				nptr->next = bptr->next;
				bptr->amagic = POOL_ALLOC_BLOCK_MAGIC;
				bptr->asize = blocks;
				bptr->last->next = nptr;
				locked = false;
				return (void*)(bptr+1);
			}
			bptr = bptr->next;
		}
	}
}

void *engine::memalloc(size_t size, uint16_t flags)
{
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
	
	if(flags & MEM_FLAG_POOL)
		return engine::internals::pool.allocate((size % 32) ? size/32 + 1 : size/32, flags);
	else
	{
		if(size > HEAP_MAX_ALLOCATION_SIZE)
			return engine::internals::pool.allocate((size % 32) ? size/32 + 1 : size/32, flags);
		else
		{
			uintptr_t ret = (uintptr_t)malloc(size + sizeof(engine::internals::allocHeader) + 31);
			uintptr_t tmp = ret;
			ret = flags & MEM_FLAG_ALIGNED ? 
				(((ret + sizeof(engine::internals::allocHeader)) + (32 - 1)) & -32) - sizeof(engine::internals::allocHeader)
				: ret;
			engine::internals::allocHeader *h = (engine::internals::allocHeader*)ret;
			h->align = ret - tmp;
			h->flags = flags;
			h->magic = ALLOC_HEADER_MAGIC_NUMBER;
			h->size = size;
			return (void*)(ret + sizeof(engine::internals::allocHeader));
		}
	}
}