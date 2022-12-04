#ifdef __unix__

extern "C"
{
	#include <unistd.h>
	#include <sys/mmap.h>
}

#elif defined(_WIN32)

extern "C"
{
	#include <Windows.h>
}
	
#endif

#include <cstdlib>
#include <cstring>
#include "include/core/mem.hpp"

using namespace engine;

static inline void *valloc(size_t size, int unit, bool exec)
{
	int usize;
	switch(unit)
	{
		case MEM_ALLOC_UNIT_KB:
			usize = 1024;
			break;
		case MEM_ALLOC_UNIT_PAGE:
			usize = 1024 * 4;
			break;
		case MEM_ALLOC_UNIT_MB:
			usize = 1024 * 1024;
			break;
		case MEM_ALLOC_UNIT_BYTE:
		default:
			usize = 1;
			break;
	}
	#ifdef __unix__
	void *ret = mmap(NULL, size * usize + 8, 
			(exec) ? PROT_READ | PROT_WRITE | PROT_EXEC : PROT_READ_WRITE, MAP_ANONYMOUS, 0, 0);
	#elif defined(_WIN32)
	void *ret = VirtualAlloc(NULL, size * usize + 8, MEM_RESERVE, (exec) ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE);
	#endif

	*(size_t*)ret = size * usize;
	return (void*)((uintptr_t)ret + 8);
}

void *engine::lalloc(size_t size, int unit)
{
	return valloc(size, unit, false);
}

void *engine::execalloc(size_t size, int unit)
{
	return valloc(size, unit, true);
}

void *engine::crealloc(size_t size, void *ptr, bool exec, int unit)
{
	size_t oldsize = *(size_t*)((uintptr_t)ptr - 8);
	if(size == oldsize)
		return ptr;

	void *ret = valloc(size, unit, exec);
	memcpy(ret, ptr, (size > oldsize) ? oldsize : size);
	return ret;
}

void engine::cfree(void *ptr)
{
	ptr = (void*)((uintptr_t)ptr - 8);

	#ifdef __unix__
	munmap(ptr, *(size_t*)ptr);
	#elif __defined(_WIN32)
	VirtualFree(ptr, *(size_t*)ptr, MEM_RELEASE);
	#endif
}
