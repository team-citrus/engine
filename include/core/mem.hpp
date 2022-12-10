#ifndef CITRUS_ENGINE_MEMORY_MANAGEMENT_HPP__
#define CITRUS_ENGINE_MEMORY_MANAGEMENT_HPP__

#include <cstdint>
#include <cstdlib>

#define MEM_FLAG_UNIT_BYTE 0 << 0
#define MEM_FLAG_UNIT_WORD 1 << 2
#define MEM_FLAG_UNIT_DWORD 1 << 3
#define MEM_FLAG_UNIT_QWORD 1 << 4
#define MEM_FLAG_UNIT_KB 1 << 5
#define MEM_FLAG_UNIT_MB 1 << 6
#define MEM_FLAG_UNIT_PAGE 1 << 7

#define HEAP_MAX_ALLOCATION_SIZE 96

// TODO: add a macro that provides an overload for new, new[], delete, and delete[] or something to that effect.

namespace engine
{
	/*	The main memory allocation function
	*	Really just a wrapper around a couple different functions
	*	@param size Size in bytes
	*	@param flags Flags
	*	@return Pointer to the allocation, NULL if an error occurs
	*	Errno will be set
	*/
	void *memalloc(size_t size, uint16_t flags);

	/* 	The main memory reallocation function
	*	@param ptr The old pointer
	*	@param size Size in bytes
	*	@param flags Flags, 0 to use previous flags
	*	@return Pointer to the new allocation, NULL if an error occurs
	*	Errno will be set
	*/
	void *memrealloc(void *ptr, size_t size, uint16_t flags);

	/*	The main memory freeing function
	*	Really just a wrapper around a couple different functions
	*	@param ptr Pointer to free
	*/
	void memfree(void *ptr);
};

#endif
