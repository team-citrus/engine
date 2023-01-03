#include <thread>
#include <cstdio>
#include <cstdarg>
#include <ctime>
#include "include/core/log.hpp"

using namespace engine;

logger::logger(const char *file)
{
    bfile = fopen(file, "a+");
}

logger::~logger()
{
    fclose(bfile);
}

void logger::log(int code, const char *module, const char *format, ...)
{
    time_t t = time(NULL);
    tm T = *localtime(&t);
    va_list v;
    va_start(v, format);

    fprintf(bfile, "[%d-%d-%d-%d-%d:%d] %s: ", T.tm_year + 1900, T.tm_mon + 1, T.tm_mday, T.tm_hour, T.tm_min, T.tm_sec, module);
    vfprintf(bfile, format, v);
    putc('\n', bfile);
}