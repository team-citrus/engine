#ifndef CITRUS_ENGINE_MEMORY_MANAGEMENT_HPP__
#define CITRUS_ENGINE_MEMORY_MANAGEMENT_HPP__

#define MEM_ALLOC_UNIT_BYTE 0
#define MEM_ALLOC_UNIT_KB 1
#define MEM_ALLOC_UNIT_PAGE 2
#define MEM_ALLOC_UNIT_MB 3

#define HEAP_MAX_ALLOCATION_SIZE 0x1000 

namespace engine
{
	/*	Custom memory allocation for large units
	*	Should be used for anything over HEAP_MAX_ALLOCATION_SIZE
	*	@param size Size of the allocation in units
	*	@param unit One of the unit defines, sets the units to use
	*	@return Pointer to the allocated memory
	*/
	void *lalloc(size_t size, int unit);

	/*	Custom memory allocation for anything that needs to be executed
	*	@param size Size of the allocation in units
	*	@param unit One of the unit defines, sets the units to use
	*	@return Pointer to the allocated memory
	*/
	void *execalloc(size_t size, int unit);

	/*	Custom memory reallocation for large units
	*	Return value should not be ignored, as it contains the new pointer
	*	@param size The new size
	*	@param ptr The old pointer
	*	@param exec True if it needs to be executed, false if not
	*	@param unit One of the unit defines, sets the units to use
	*	@return The new pointer
	*/
	void *crealloc(size_t size, void *ptr, bool exec, int unit);

	/* Frees any memory allocated with lalloc or execalloc */
	void cfree(void *ptr);
}

#endif
