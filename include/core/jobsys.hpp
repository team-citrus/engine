/*
*   name: include/core/jobsys.hpp
*   origin: Citrus Engine
*   purpose: Provide the header for the job system
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_JOB_SYSTEM_HPP__
#define CITRUS_ENGINE_JOB_SYSTEM_HPP__

#include <typeinfo>
#include "../core/hash.hpp"
#include "../core/extensions.h"

#ifndef _JOB_BLOCK_UNTIL_
#define _JOB_BLOCK_UNTIL_ 100
#endif

namespace engine
{	
	typedef void (*JobPtr)();
	class Job
	{
		bool prioritzed;

		#ifdef __FILE_IS_JOBSYS_DOT_CPP__
		friend void refreshJobSystem();
		friend int jobWrapper(engine::Job ptr);
		#endif

		public:
		///	Schedule the job for execution. 
		/// @param exclude Bit flags of which threads to block.
		/// @return Error returns -1 and sets engine::errorcode. Success returns the index it is currently scheduled at.
		int schedule();

		/// Block this thread until the job completes or _JOB_BLOCK_UNTIL_ milliseconds has passed (default defined as 100). Also moves the job to a prioity list if it is not already executing.
		/// @return Error returns -1 and sets engine::errorcode. Success returns 0.
		int complete();

		/// Prioritize this job
		void prioritize();

		virtual void operator()()
		{
			return;
		}

		virtual bool operator==(Job &otra);

		virtual int getTypeSignature();

		#if defined(CITRUS_ENGINE_FINE_TUNE) || defined(_INTERNALS_ENGINE_THREAD_MAIN_)
		/// Set this job to be done ASAP
		void ASAP();
		#endif
	};

	#ifdef _INTERNALS_ENGINE_THREAD_MAIN_
	namespace internals
	{
		extern std::atomic_bool jobsBeingAccessed;
		extern Vector<Job> jobs;
		extern Vector<Job> priority;
		extern Vector<Job> asap;
		extern Map<hash_t, std::thread::id> executing;

		// Used by the job system to determine how many threads to generate.
		extern size_t threadsAvalible = 0;
		// Used by the job system to determine how many threads can be generated.
		extern size_t coreCount = 0;
		// The number of threads that can be generated
		extern size_t possibleThreads = 0;
	}
	#endif
}

#endif