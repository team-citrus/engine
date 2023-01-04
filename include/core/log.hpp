/*
*	name: include/core/log.hpp
*	origin: Citrus Engine
*	purpose: Provide logging facilities
*	author: https://github.com/ComradeYellowCitrusFruit
*	license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_LOGGING_HPP__
#define CITRUS_ENGINE_LOGGING_HPP__

#include <cstdio>

#ifndef _ENGINE_LOG_FILE_
#define _ENGINE_LOG_FILE_ "logs/engine.log"
#endif

#ifndef _GAME_LOG_FILE_
#define _GAME_LOG_FILE_ "logs/game.log"
#endif

#ifndef _NETWORK_LOG_FILE_
#define _NETWORK_LOG_FILE_ "log/network.log"
#endif

#ifndef _CRASH_LOG_FILE_
#define _CRASH_LOG_FILE_ "log/crash.log"
#endif

namespace engine
{
	class logger
	{
	private:
		FILE *bfile;

	public:
		logger(const char *file);
		~logger();

		/*	Log a message, works like printf, however the trailing newline is added
		*	@param module The string of the module/function/component/class the message is being logged from
		*	@param format The format string, in printf style
		*/
		void log(const char *module, const char *format, ...);
	};

	logger engineLog(_ENGINE_LOG_FILE_);
	logger gameLog(_GAME_LOG_FILE_);
	logger networkLog(_NETWORK_LOG_FILE_);
	logger crashLog(_CRASH_LOG_FILE_);
};

#endif