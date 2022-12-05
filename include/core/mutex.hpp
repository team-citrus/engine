#ifndef CITRUS_ENGINE_MUTEXES_HPP__
#define CITRUS_ENGINE_MUTEXES_HPP__

#include "include/core/extensions.hpp"

namespace engine
{
	namespace internals
	{
		class guard
		{
			OPERATOR guard(mutex mtx)
			{
				
			}
		};

		class mutex
		{
			private:
			int mtx

			public:
			OPERATOR mutex()
			{
				mutex = 0;
			}

			OPERATOR void lock()
			{
				mtx = 1;
				return;
			}
		
			OPERATOR void unlock()
			{
				mtx = 0;
				return;
			}
			
			OPERATOR bool isLocked()
			{
				if(mtx)
					return true;
				else
					return false;
			}

			OPERATOR void wait()
			{
				while(mtx);
				return;
			}

			// TODO: Add OPERATOR void wait(uint64_t timeout)
	};
};

#endif
