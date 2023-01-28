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
#include "core/extensions.hpp"

#ifndef _LOG_FILE_
#define _LOG_FILE_ "log.log"
#endif

namespace engine
{
	namespace internals
	{
		FILE *logfile;
		char buff[1024];
		_OPTIMIZE_(2) OPERATOR void initLogging()
		{
			logfile = fopen(_LOG_FILE_, "a+");
			setvbuf(logfile, buff, _IOFBF, 1024);
		}
		_OPTIMIZE_(2) OPERATOR void finiLogging()
		{
			fclose(logfile);
		}
	}

	// Logs a message, works like printf, and appends a newline

	_OPTIMIZE_(2) template <typename... T>
	OPERATOR void log(const char *module, const char *format, T... args)
	{
		time_t t = time(NULL);
		tm T = *localtime(&t);

		fprintf(internals::logfile, "[%d-%d-%d-%d-%d:%d] %s: ", T.tm_year + 1900, T.tm_mon + 1, T.tm_mday, T.tm_hour, T.tm_min, T.tm_sec, module);
		fprintf(internals::logfile, format, args...);
		putc('\n', internals::logfile);
	}

	// Logs a message, and appends a newline, use this only in Rust code
	_OPTIMIZE_(2) extern "C" void rust_log(const char *str)
	{
		time_t t = time(NULL);
		tm T = *localtime(&t);

		fprintf(internals::logfile, "[%d-%d-%d-%d-%d:%d] Rust: %s\n", T.tm_year + 1900, T.tm_mon + 1, T.tm_mday, T.tm_hour, T.tm_min, T.tm_sec, str);
	}
};

#endif