/*
*   name: include/core/rc.hpp
*   origin: Citrus Engine
*   purpose: Simple reference counter class
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_REFRENCE_COUNTER_HPP__
#define CITRUS_ENGINE_REFRENCE_COUNTER_HPP__

#include "core/mem.hpp"

namespace engine
{
	template<typename T>
	class RefernceCounter
	{
		public:

		typedef void (*FiniFunc)(T*);
		typedef void (*InitFunc)(T*);

		NEVER_INLINE void dummy_func(T *a)
		{
			asm("nop"); // both arm and x86 have nop instructions!
		}

		private:
		InitFunc init;
		FiniFunc fini;

		int ctr;
		public:
		T obj;

		static RefernceCounter &getNew(T o)
		{
			RefernceCounter *esta = memalloc(sizeof(ReferenceCounter<T>));
			esta->obj = o;
			ctr = 1;
			esta->init = dummy_func;
			esta->fini = dummy_func;
		}

		static RefernceCounter &getNew(T o, InitFunc ini, FiniFunc fin)
		{
			RefernceCounter *esta = memalloc(sizeof(ReferenceCounter<T>));
			esta->obj = o;
			ctr = 1;
			esta->init = ini;
			esta->fini = fin;
			ini(&esta->obj);
		}

		OPERATOR void removeReference()
		{
			ctr--;
			if(ctr == 0)
			{
				fini(&obj);
				memfree(this);
			}
		}

		OPERATOR void addReference()
		{
			ctr++;
		}

		OPERATOR void operator--()
		{
			removeReference();
		}

		OPERATOR void operator++()
		{
			ctr++;
		}
	};
}

#endif