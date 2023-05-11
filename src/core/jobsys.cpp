/*
*   name: src/core/jobsys.cpp
*   origin: Citrus Engine
*   purpose: Provide the code for the job system
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#define __CITRUS_ENGINE_SOURCE_FILE__
#define __FILE_IS_JOBSYS_DOT_CPP__
#define _INTERNALS_ENGINE_THREAD_MAIN_

#include <thread>
#include <atomic>
#include "core/jobsys.hpp"
#include "core/pair.hpp"
#include "core/vector.hpp"
#include "core/errno.hpp"
#include "core/simd.h"
#include "core/sync.hpp"

// TODO: errors
#define getTimeInMils() std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()

extern void waitms(size_t mils);

namespace engine
{
	static inline void refreshJobSystem();
	static inline int jobWrapper(engine::Job ptr, bool isEngineThread);

	namespace internals
	{
		std::atomic_bool jobsBeingAccessed;
		std::atomic_bool executingBeingAccessed;
		Vector<Job> usr;
		Vector<Job> priority;
		Vector<Job> asap;
		Vector<Job> engine;
		Map<hash_t, std::thread::id> executing;

		// number of engine threads
		int engineThreads = 0;
		// threads for user code
		int usrThreads = 0;
	}

	static inline void initJobSystem()
	{
		static bool inited = false;
		if(inited) return;

		inited = true;
		internals::engineThreads = internals::usrThreads = std::thread::hardware_concurrency();
		
		if(internals::engineThreads >= 8)
		{
			internals::usrThreads += std::thread::hardware_concurrency() - (internals::engineThreads = (internals::engineThreads-2)/2);
		}
	}

	int Job::schedule()
	{
		while(internals::jobsBeingAccessed.load()) spinlock_pause();
		internals::jobsBeingAccessed.store(true);

		ctr++;
		internals::usr.push(*this);
		refreshJobSystem();

		internals::jobsBeingAccessed.store(false);
		return 0;
	}

	// Ugly fix but a fix none the less
	static inline bool executing_has(hash_t k)
	{
		while(internals::executingBeingAccessed.load()) spinlock_pause();
		internals::executingBeingAccessed.store(true);

		bool r = internals::executing.has(k);

		internals::executingBeingAccessed.store(false);

		return r;
	}

	int Job::complete()
	{
		this->prioritize();
		size_t targetTime = getTimeInMils() + _JOB_BLOCK_UNTIL_;

		while(executing_has(this->hash()) && getTimeInMils() != targetTime)
			spinlock_pause();

		if(internals::executing.has(this->hash()))
		{
			errorcode() = ENGINE_TIME_OUT;
			return -1;
		}

		while(internals::priority.search(*this) && getTimeInMils() != targetTime)
			spinlock_pause();

		if(internals::priority.search(*this) || internals::executing.has(this->hash()))
		{
			errorcode() = ENGINE_TIME_OUT;
			return -1;
		}

		return 0;
	}

	void Job::prioritize()
	{
		while(internals::jobsBeingAccessed.load()) spinlock_pause();
		internals::jobsBeingAccessed.store(true);

		if(this->prioritzed)
		{
			return;
		}

		if(internals::executing.has(hash()))
		{
			return;
		}

		for(int i = 0; i < internals::usr.getCount(); i++)
		{
			if(internals::usr[i] == *this)
			{
				internals::usr.rm(i);
				this->prioritzed = true;
				internals::priority.push(*this);
				return;
			}
		}

		errorcode() = ENGINE_INVALID_ARG;
		return;
	}

	void Job::ASAP()
	{
		while(internals::jobsBeingAccessed.load()) spinlock_pause();
		internals::jobsBeingAccessed.store(true);

		if(internals::executing.has(hash()))
		{
			return;
		}

		for(int i = 0; i < internals::usr.getCount(); i++)
		{
			if(internals::usr[i] == *this)
			{
				internals::usr.rm(i);
				internals::asap.push(*this);
				return;
			}
		}

		for(int i = 0; i < internals::priority.getCount(); i++)
		{
			if(internals::priority[i] == *this)
			{
				internals::priority.rm(i);
				internals::asap.push(*this);
				return;
			}
		}

		for(int i = 0; i < internals::engine.getCount(); i++)
		{
			if(internals::engine[i] == *this)
			{
				internals::engine.rm(i);
				internals::asap.push(*this);
				return;
			}
		}

		errorcode() = ENGINE_INVALID_ARG;
		return;
	}

	static inline void refreshJobSystem()
	{
		initJobSystem();

		while(internals::usrThreads != 0 && internals::asap.getCount() > 0)
		{
			std::thread nuevo(jobWrapper, internals::asap[0], false);
			nuevo.detach();
			internals::usrThreads--;
		}
		
		while(internals::engineThreads != 0 && internals::engine.getCount() > 0)
		{
			std::thread nuevo(jobWrapper, internals::engine[0], true);
			nuevo.detach();
			internals::engineThreads--;
		}

		while(internals::usrThreads != 0 && internals::priority.getCount() > 0)
		{
			std::thread nuevo(jobWrapper, internals::priority[0], false);
			nuevo.detach();
			internals::engineThreads--;
		}

		while(internals::usrThreads != 0 && internals::usr.getCount() > 0)
		{
			std::thread nuevo(jobWrapper, internals::usr[0], false);
			nuevo.detach();
			internals::engineThreads--;
		}
	}

	static inline int jobWrapper(engine::Job ptr, bool isEngineThread)
	{
		while(internals::jobsBeingAccessed.load()) spinlock_pause();
		internals::jobsBeingAccessed.store(true);

	execute:

		hash_t h = ptr.hash();

		while(internals::executingBeingAccessed.load()) spinlock_pause();
		internals::executingBeingAccessed.store(true);

		internals::executing.add(h, std::this_thread::get_id());

		internals::executingBeingAccessed.store(false);
		internals::jobsBeingAccessed.store(false);

		ptr();

		while(internals::jobsBeingAccessed.load()) spinlock_pause();
		internals::jobsBeingAccessed.store(true);

		while(internals::executingBeingAccessed.load()) spinlock_pause();
		internals::executingBeingAccessed.store(true);

		internals::executing.rm(h);

		internals::executingBeingAccessed.store(false);
		refreshJobSystem();
		
		if((!isEngineThread || internals::usrThreads != 0) && internals::asap.getCount() > 0)
		{
			ptr = internals::asap[0];
			internals::asap.rm(0);
			
			if(isEngineThread)
			{
				internals::engineThreads++;
				internals::usrThreads--;
				isEngineThread = false;
			}

			goto execute;
		}
		
		if((isEngineThread || internals::engineThreads != 0) && internals::engine.getCount() > 0)
		{
			ptr = internals::engine[0];
			internals::engine.rm(0);
			
			if(!isEngineThread)
			{
				internals::engineThreads--;
				internals::usrThreads++;
				isEngineThread = true;
			}

			goto execute;
		}

		if((!isEngineThread || internals::usrThreads != 0) && internals::priority.getCount() > 0)
		{
			ptr = internals::priority[0];
			internals::priority.rm(0);
			
			if(isEngineThread)
			{
				internals::engineThreads++;
				internals::usrThreads--;
				isEngineThread = false;
			}

			goto execute;
		}

		if((!isEngineThread || internals::usrThreads != 0) && internals::usr.getCount() > 0)
		{
			ptr = internals::usr[0];
			internals::usr.rm(0);
			
			if(isEngineThread)
			{
				internals::engineThreads++;
				internals::usrThreads--;
				isEngineThread = false;
			}

			goto execute;
		}

		if(isEngineThread)
			internals::engineThreads++;
		else
			internals::usrThreads++;

		internals::jobsBeingAccessed.store(false);
	}
}