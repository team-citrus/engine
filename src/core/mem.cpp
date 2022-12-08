#ifdef __unix__

#include <unistd.h>
#include <sys/mmap.h>

#elif defined(_WIN32)

#include <Windows.h>

#endif

#include "include/core/mem.hpp"
#include "include/core/mem_int.hpp"

static inline void* alignPtr(void *ptr)
{
	uintptr_t ret = (uintptr_t)ptr;
	ret = (ret + (16-1)) & - 16;
	return (void*)ret;
}

/*	Use page allocation
*	@param size Size passed to memalloc
*	@param flags Flags passed to memalloc, with the high bits set accordingly.
*/
static inline void *pageAlloc(size_t size, uint16_t flags)
{
	allocHeader *h;
	#ifdef __unix__
	// Map the memory, with enough space to align and hold the header
	h = mmap(ALLOC_PAGE_START(),
			size + 15 + sizeof(allocHeader), 
			PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS,
			-1, 0);
	#elif defined(_WIN32)
	// Map the memory, with enough space to align and hold the header
	h = VirtualAlloc(ALLOC_PAGE_START(),
			size + 15 + sizeof(allocHeader),
			MEM_RESERVE,
			PAGE_READWRITE);
	#endif
	
	h->align = 0;
	
	// Align to 16 byte boundary
	if(flags & MEM_FLAG_ALIGNED)
	{
		uintptr_t intptr = (uintptr_t)alignPtr((void*)((uintptr_t)h + sizeof(allocHeader));
		allocHeader *nh = (allocHeader*)(intptr - sizeof(allocHeader));
		nh.align = (uintptr_t)nh - (uintptr_t)h;
		h = nh;
	}

	h->size = size + 15;
	h->magic = ALLOC_HEADER_MAGIC_NUMBER;
	h->flags = flags;

	return (void*)((uintptr_t)h + sizeof(allocHeader));
}

/*	Use pool allocation
*	@param size Size to allocate in the pool
*	@param flags Flags passed to memalloc, with the high bits set.
*/
static inline void *poolAlloc(size_t size, uint16_t flags)
{
	// TODO: add error checking:
	// - Pool size
	// - Contiguous pool size
	
	// Use some pointer madness to get the pool state
	poolHeader *state = (poolHeader*)((uintptr_t)pool - sizeof(poolHeader));
	while(state->locked);
	state->locked = true;

	// Even more pointer madness
	poolAHeader *h = (poolAHeader*)pool;
	while(!h.isLast()) h = h->next;
	h->next = (poolAHeader*)((uintptr_t)h + h->size);
	uintptr_t oh = (uintptr_t)(h->next);
	h->next = (flags & MEM_FLAG_ALIGNED) ? (poolAHeader*)(((((uintptr_t)h->next + sizeof(poolAHeader)) + (16-1)) & - 16) - sizeof(poolAHeader)) : h->next;

	// Set up the header
	h->next->last = h;	
	h = h->next;
	h->size = size;
	h->magic = ALLOC_HEADER_MAGIC_NUMBER;
	h->flags = flags;
	// Used purely to update the size
	h->align = (uintptr_t)h - oh;
	h->next = NULL;

	// Update the pool state and return
	state->free -= h->align + size;
	state->locked = false;
	return (void*)((uintptr_t)h + sizeof(poolAHeader));
}

/*	Use heap allocation
*	@param size Size
*	@param flags Flags passed to memalloc, with the high bits set accordingly
*/
static inline void *heapAlloc(size_t size, uint16_t flags)
{
	// Allocate with size to align
	allocHeader *oh = malloc(size + sizeof(allocHeader) + 15);
	allocHeader *h = (flags & MEM_FLAG_ALIGNED) ? (allocHeader*)alignPtr((void*)oh) : oh;

	h->magic = ALLOC_HEADER_MAGIC_NUMBER;
	h->size = size;
	h->flags = flags;
	h->align = (uintptr_t)h - (uintptr_t)oh;
	return (void*)((uintptr_t)h + sizeof(allocHeader));
}

void *engine::memalloc(size_t size, uint16_t flags)
{
	// Evaluate flags
	if(flags & MEM_FLAG_NO_HEAP)
	{
		if(flags & MEM_FLAG_PERM)
			return pageAlloc(size, flags | 1 << 15);
		else
			return poolAlloc(size, flags | 1 << 14);
	
	}
	if(flags & MEM_FLAG_TEMP || flags & MEM_FLAG_ARR || flags & MEM_FLAG_HEAP)
	{
		if(size > HEAP_MAX_ALLOCATION * 2)
			return poolAlloc(size, flags | 1 << 14);
		else
			return heapAlloc(size, flags);
	}
	if(flags & MEM_FLAG_SCENE)
	{
		if(size > HEAP_MAX_ALLOCATION/4)
			return poolAlloc(size, flags | 1 << 14);
		else
			return heapAlloc(size, flags);
	}
	else
	{
		if(size > HEAP_MAX_ALLOCATION)
			return poolAlloc(sizem flags | 1 << 14);
		else
			return heapAlloc(size, flags);
	}
}
