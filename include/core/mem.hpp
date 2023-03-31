/*
*   name: include/core/mem.hpp
*   origin: Citrus Engine
*   purpose: Provide memory allocation functions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_MEMORY_MANAGEMENT_HPP__
#define CITRUS_ENGINE_MEMORY_MANAGEMENT_HPP__

#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <cstddef>
#include <memory>
#include "core/extensions.h"

namespace engine
{
	/**	Allocate memory using our custom block allocator
	*	@param size Size in bytes
	*	@param flags Flags
	*	@return Pointer to the allocation, NULL if an error occurs, errorcode will be set
	*/
	__attribute__((malloc, assume_aligned(32), alloc_size(1)))
	void *memalloc(size_t size);

	/**	Reallocate memory allocated previously with memalloc or zmalloc
	*	@param ptr The old pointer
	*	@param size Size in bytes
	*	@param flags Flags, 0 to use previous flags
	*	@return Pointer to the new allocation, NULL if an error occurs, errorcode will be set
	*	@note If new memory is allocated by this function it will not be zero'd, even if the original block was allocated by zmalloc
	*/
	__attribute__((assume_aligned(32), alloc_size(2)))
	void *memrealloc(void *ptr, size_t size);

	/**	Free memory previously allocated with memalloc, zmalloc, or memrealloc
	*	@param ptr Pointer to free
	*	@note A double free won't do anything harmful. Invalid pointers will set errorcode, however only some will be caught
	*/
	void memfree(void *ptr);

	/**	Allocated memory using our custom block allocator and zero it.
	*	@param items Number of items
	*	@param size Size per item
	*	@note This is not the zmalloc() from redis.
	*/
	__attribute__((malloc, assume_aligned(32), alloc_size(1, 2)))
	void *zmalloc(size_t items, size_t size);

	/// posix_memalign but memalloc
	DEPRECATED(Please don't use this, it's only supported so that we can support libraries that might use posix_memalloc or aligned_alloc. It is also extremely inefficient)
	int __memalloc_posix_memalign(void **memptr, size_t alignment, size_t size);

	/** Just another name for zmalloc()
	*	@param items Number of items
	*	@param size Size per item
	*/
	ALIAS(zmalloc) void *memcalloc(size_t items, size_t size);

	/** Get the usable size of a memalloc'd buffer
	*	@param ptr The buffer
	*	@warning It is best practice to only use the amount of specified space to be allocated
	*/
	DEPRECATED(It is best practice to only use the amount of specified space to be allocated)
	size_t memlen(void *ptr);

	// TODO: Add an allocator type
};

NOMANGLE
{
	// malloc is a weak symbol, we can override it
	ALIAS(engine::memalloc) void *malloc(size_t size);

	// realloc is a weak symbol, we can override it
	ALIAS(engine::memrealloc) void *realloc(void *ptr, size_t size);

	// calloc is a weak symbol, we can override it
	ALIAS(engine::memcalloc) void *calloc(size_t items, size_t size);

	// free is a weak symbol, we can override it
	ALIAS(engine::memfree) void free(void *ptr);

	// ok we get the idea weak symbol yada yada yada
	ALIAS(engine::memlen) size_t malloc_usable_size(void *ptr);

	DEPRECATED(Please don't use this, it's only supported so that we can support libraries that might use posix_memalloc or aligned_alloc. It is also extremely inefficient)
	ALIAS(engine::__memalloc_posix_memalign) int posix_memalign(void **memptr, size_t alignment, size_t size);

	DEPRECATED(Please don't use this, it's only supported so that we can support libraries that might use posix_memalloc or aligned_alloc. It is also extremely inefficient)
	void *aligned_alloc(size_t align, size_t size)
	{
		void *ret;
		int pcode;
		if(size % align)
		{
			errno = EINVAL;
			return -1;
		}

		return ((pcode = posix_memalign(&ret, align, size)) != EINVAL && pcode != ENOMEM) ? ret : -1 ;
	}

	DEPRECATED(Please don't use this, it's only supported so that we can support libraries that might use posix_memalloc or aligned_alloc. It is also extremely inefficient)
	ALIAS(aligned_alloc) void *memalign(size_t align size);
}

#endif
