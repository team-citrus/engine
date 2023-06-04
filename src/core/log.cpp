#include "core/log.hpp"

FILE *logfile;
char buff[_LOG_BUFFER_LENGTH_];

extern "C" void rust_log(const char *module, const char *str)
{
	log(module, str);
}