/*
*   name: include/core/jobsys.hpp
*   origin: Citrus Engine
*   purpose: Provide the header for the job system
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_JOB_SYSTEM_HPP__
#define CITRUS_ENGINE_JOB_SYSTEM_HPP__

#include "core/extensions.h"

#ifndef _JOB_BLOCK_UNTIL_
#define _JOB_BLOCK_UNTIL_ 100
#endif

namespace engine
{
	#define CITRUS_ENGINE_BLOCK_RENDERING 0x1
	#define CITRUS_ENGINE_BLOCK_MIXING 0x2
	#define CITRUS_ENGINE_BLOCK_PHYSICS 0x4
	#define CITRUS_ENGINE_BLOCK_GAMEPLAY 0x8
	
	typedef void (*JobPtr)();
	class Job
	{
		JobPtr ptr;

		#ifdef __FILE_IS_JOBSYS_DOT_CPP__
		friend void refreshJobSystem();
		friend int jobWrapper(engine::Job ptr);
		#endif

		public:
		OPERATOR Job()
		{
			return;
		}
		OPERATOR Job(JobPtr func)
		{
			ptr = func;
		}
		OPERATOR void setFunc(JobPtr func)
		{
			ptr = func;
		}

		///	Schedule the job for execution. 
		/// @param exclude Bit flags of which threads to block.
		/// @return Error returns -1 and sets engine::errorcode. Success returns the index it is currently scheduled at.
		int schedule();

		/// Block this thread until the job completes or _JOB_BLOCK_UNTIL_ milliseconds has passed (default defined as 100). Also moves the job to a prioity list if it is not already executing.
		/// @return Error returns -1 and sets engine::errorcode. Success returns 0.
		int complete();
	};
}

#endif