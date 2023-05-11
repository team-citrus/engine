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
#define _JOB_BLOCK_UNTIL_ 8
#endif

namespace engine
{	
	typedef void (*JobPtr)();
	class Job
	{
		bool prioritzed;
		int ctr; // Neat trick to prevent hash-reuse

		#ifdef __FILE_IS_JOBSYS_DOT_CPP__
		friend void refreshJobSystem();
		friend int jobWrapper(engine::Job ptr, bool isEngineThread);
		#endif

		public:
		///	Schedule the job for execution. 
		/// @param exclude Bit flags of which threads to block.
		/// @return Error returns -1 and sets engine::errorcode. Success returns the index it is currently scheduled at.
		int schedule();

		/// Block this thread until the job completes or _JOB_BLOCK_UNTIL_ milliseconds has passed (default defined as 8). Also moves the job to a prioity list if it is not already executing.
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

		virtual hash_t hash()
		{
			return engine::hash(this, sizeof(*this));
		}

		#if defined(CITRUS_ENGINE_FINE_TUNE) || defined(_INTERNALS_ENGINE_THREAD_MAIN_)
		/// Set this job to be done ASAP
		void ASAP();
		#endif

		#if defined(_INTERNALS_ENGINE_THREAD_MAIN_)
		/// Schedule a system job
		void sysSchedule();
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

		// number of engine threads
		extern int engineThreads;
		// threads for user code
		extern int usrThreads;
	}
	#endif
}

#endif