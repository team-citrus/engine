#ifndef CITRUS_ENGINE_THREADING_HPP__
#define CITRUS_ENGINE_THREADING_HPP__

#include <cstdint>

namespace engine
{
	namespace internals
	{
		typedef threadID_t uint64_t;
		
		class thread
		{
			private:
				void *stack;
				bool joinable;
				threadID_t ID;
			public:
				thread(void (*entrypoint)(void*), void *arg);
				~thread();
				threadID_t getID();
				bool joinable();
				void join();
				void detach();
		};	
	};
};

#endif
