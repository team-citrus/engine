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
#include <ctime>
#include <cstdarg>
#include "core/extensions.h"

#ifndef _LOG_FILE_
#define _LOG_FILE_ "game.log"
#endif

#ifndef _LOG_BUFFER_LENGTH_
#define _LOG_BUFFER_LENGTH_ 4096
#endif

namespace engine
{
	namespace internals
	{
		FILE *logfile;
		char buff[_LOG_BUFFER_LENGTH_];
		OPTIMIZE(2) OPERATOR void initLogging()
		{
			logfile = fopen(_LOG_FILE_, "a+");
			setvbuf(logfile, buff, _IOFBF, _LOG_BUFFER_LENGTH_);
		}
		OPTIMIZE(2) OPERATOR void finiLogging()
		{
			fclose(logfile);
		}
	}

	// Logs a message, works like printf, and appends a newline

	OPTIMIZE(2) template <typename... T>
	OPERATOR void log(const char *module, const char *format, T... args)
	{
		time_t t = time(NULL);
		tm T = *localtime(&t);

		fprintf(internals::logfile, "[%d-%d-%d-%d-%d:%d] %s: ", T.tm_year + 1900, T.tm_mon + 1, T.tm_mday, T.tm_hour, T.tm_min, T.tm_sec, module);
		fprintf(internals::logfile, format, args...);
		putc('\n', internals::logfile);
	}

	// Logs a message, and appends a newline, use this only in Rust code
	OPTIMIZE(2) extern "C" void rust_log(const char *module, const char *str)
	{
		log(module, str);
	}
};

#endif
