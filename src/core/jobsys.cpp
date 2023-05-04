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
	static inline int jobWrapper(engine::Job ptr);

	namespace internals
	{
		std::atomic_bool jobsBeingAccessed;
		Vector<Job> jobs;
		Vector<Job> priority;
		Vector<Job> asap;
		Map<hash_t, std::thread::id> executing;

		// Used by the job system to determine how many threads to generate.
		size_t threadsAvalible = 0;
		// Used by the job system to determine how many threads can be generated.
		size_t coreCount = 0;
		// The number of threads that can be generated
		size_t possibleThreads = 0;
	}

	static inline void initJobSystem()
	{
		static bool inited = false;
		if(inited) return;
		inited = true;
		internals::coreCount = std::thread::hardware_concurrency();
		internals::threadsAvalible = internals::coreCount - 4;
	}

	int Job::schedule()
	{
		while(internals::jobsBeingAccessed.load()) spinlock_pause();
		internals::jobsBeingAccessed.store(true);

		internals::jobs.push(*this);
		refreshJobSystem();

		internals::jobsBeingAccessed.store(false);
		return 0;
	}

	int Job::complete()
	{
		size_t startTime;
		while(internals::jobsBeingAccessed.load())
			spinlock_pause();
		
		internals::jobsBeingAccessed.store(true);
		if(internals::executing.has(hash(this, sizeof(*this))))
		{
			internals::jobsBeingAccessed.store(false);

			startTime = getTimeInMils();
			while((getTimeInMils() < startTime + _JOB_BLOCK_UNTIL_ && internals::executing.has(hash(this, sizeof(*this))) || internals::jobsBeingAccessed.load()))
				spinlock_pause();

			internals::jobsBeingAccessed.store(true);
			if(getTimeInMils() >= startTime + _JOB_BLOCK_UNTIL_ && internals::executing.has(hash(this, sizeof(*this))))
			{
				internals::jobsBeingAccessed.store(false);
				engine::errorcode() = ENGINE_TIME_OUT;
				return -1;
			}
			else
			{
				internals::jobsBeingAccessed.store(false);
				return 0;
			}
		}
		else
		{
			if(prioritzed)
			{
			prioritized_code:
				internals::jobsBeingAccessed.store(true);
				if(internals::executing.has(hash(this, sizeof(*this))) || internals::priority.search(*this))
				{
					internals::jobsBeingAccessed.store(false);
					engine::errorcode() = ENGINE_TIME_OUT;
					return -1;
				}
				else
				{
					internals::jobsBeingAccessed.store(false);
					return 0;
				}
			}
			else
			{
				prioritize();
				goto prioritized_code;
			}
		}
	}

	void Job::prioritize()
	{
		for(size_t i = 0; i < internals::jobs.getCount(); i++)
		{
			while(internals::jobsBeingAccessed.load()) spinlock_pause();
			if(internals::jobs[i] == *this)
			{
				while(internals::jobsBeingAccessed.load()) spinlock_pause();
				internals::jobsBeingAccessed.store(true);

				internals::priority.push(*this);
				internals::jobs.rm(i);
				
				internals::jobsBeingAccessed.store(false);
				return;
			}
		}
	}

	void Job::ASAP()
	{
		for(size_t i = 0; i < internals::jobs.getCount(); i++)
		{
			while(internals::jobsBeingAccessed.load()) spinlock_pause();
			if(internals::jobs[i] == *this)
			{
				while(internals::jobsBeingAccessed.load()) spinlock_pause();
				internals::jobsBeingAccessed.store(true);

				internals::asap.push(*this);
				internals::jobs.rm(i);
				
				refreshJobSystem();
				internals::jobsBeingAccessed.store(false);
				return;
			}
		}

		for(size_t i = 0; i < internals::priority.getCount(); i++)
		{
			while(internals::jobsBeingAccessed.load()) spinlock_pause();
			if(internals::jobs[i] == *this)
			{
				while(internals::jobsBeingAccessed.load()) spinlock_pause();
				internals::jobsBeingAccessed.store(true);

				internals::asap.push(*this);
				internals::priority.rm(i);
				
				refreshJobSystem();
				internals::jobsBeingAccessed.store(false);
				return;
			}
		}
	}

	static inline void refreshJobSystem()
	{
		initJobSystem();
		if(internals::threadsAvalible)
		{
			internals::threadsAvalible--;
			Job j;

			if(internals::asap.getCount() != 0)
			{
				j = internals::asap[0];
				internals::asap.rm(0);
			}
			if(internals::priority.getCount() != 0)
			{
				j = internals::priority[0];
				internals::priority.rm(0);
			}
			else
			{
				j = internals::jobs[0];
				internals::jobs.rm(0);
			}

			std::thread(jobWrapper, j).detach();
		}
	}

	static inline int jobWrapper(Job job)
	{
	start:
		// Init errorcodes
		errorcode() = 0;

		while(internals::jobsBeingAccessed.load()) spinlock_pause();
		internals::jobsBeingAccessed.store(true);

		// Tell everyone we are executing
		std::thread::id us = std::this_thread::get_id();
		internals::executing.add(hash(&job, sizeof(job)), us);
		internals::jobsBeingAccessed.store(false);

		job(); // Actually execute

		while(internals::jobsBeingAccessed.load()) spinlock_pause();
		internals::jobsBeingAccessed.store(true);

		if(internals::threadsAvalible < internals::threadsAvalible)
		{
			refreshJobSystem();
			internals::executing.rm(hash(&job, sizeof(job)));
		}

		if(internals::asap.getCount() != 0)
		{
			job = internals::asap[0];
			internals::asap.rm(0);
		}
		if(internals::priority.getCount() != 0)
		{
			job = internals::priority[0];
			internals::priority.rm(0);
		}
		else if(internals::jobs.getCount() != 0)
		{
			job = internals::jobs[0];
			internals::jobs.rm(0);
		}
		else 
		{
			internals::removeErrorcodeForThread();
			return 0;
		}

		goto start;
	}
}