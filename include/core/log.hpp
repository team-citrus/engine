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
#include "../core/extensions.h"

#ifndef _LOG_FILE_
#define _LOG_FILE_ "game.log"
#endif

#ifndef _LOG_BUFFER_LENGTH_
#define _LOG_BUFFER_LENGTH_ 4096
#endif

extern FILE *logfile;
extern char buff[_LOG_BUFFER_LENGTH_];

OPERATOR void initLogging()
{
	logfile = fopen(_LOG_FILE_, "a+");
	setvbuf(logfile, buff, _IOFBF, _LOG_BUFFER_LENGTH_);
}
	
OPERATOR void finiLogging()
{
	fclose(logfile);
}

// Logs a message, works like printf, and appends a newline

template <typename... T>
OPERATOR void log(const char *module, const char *format, T... args)
{
	time_t t = time(NULL);
	tm tmtime = *localtime(&t);

	fprintf(logfile, "[%d-%d-%d %d:%d:%d] %s: ", tmtime.tm_year + 1900, tmtime.tm_mon + 1, tmtime.tm_mday, tmtime.tm_hour, tmtime.tm_min, tmtime.tm_sec, module); // ISO 8601 standard date format
	fprintf(logfile, format, args...);
	putc('\n', logfile);
}

// Logs a message, and appends a newline, use this only in Rust code
extern "C" void rust_log(const char *module, const char *str);
#endif
