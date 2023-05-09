/*
*   name: include/vendor/fs.hpp
*   origin: Citrus Engine
*   purpose: Vendor interface filesystem functions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: MIT
*/

#ifndef __CITRUS_ENGINE_VENDOR_INTERFACE_HEADERS_UTIL_H__
#define __CITRUS_ENGINE_VENDOR_INTERFACE_HEADERS_UTIL_H__

#ifdef __cplusplus
#include <cstddef>

extern "C" {

typedef bool __citrus_engine_vendor_bool;

#else

#include <stddef.h>

typedef _Bool __citrus_engine_vendor_bool;

#endif

#define __CITRUS_ENGINE_VENDOR_SEEK_SET 0
#define __CITRUS_ENGINE_VENDOR_SEEK_CUR 1
#define __CITRUS_ENGINE_VENDOR_SEEK_END 2
#define __CITRUS_ENGINE_VENDOR_READ 04
#define __CITRUS_ENGINE_VENDOR_WRITE 02
#define __CITRUS_ENGINE_VENDOR_EXECUTE 01

typedef struct __citrus_engine_vendor_file_t __citrus_engine_vendor_file_t;

void *__citrus_engine_vendor_map_file_to_mem(char *name, size_t offset, size_t len, int perms);
void __citrus_engine_vendor_unmap_file_from_mem(void *f, size_t len);

char *__citrus_engine_vendor_get_file_name(char *precompile_filename);
__citrus_engine_vendor_file_t *__citrus_engine_vendor_fopen(char *name, const char *perm);
void __citrus_engine_vendor_fclose(__citrus_engine_vendor_file_t *file);
__citrus_engine_vendor_bool __citrus_engine_vendor_feof(__citrus_engine_vendor_file_t *file);
int __citrus_engine_vendor_fgetpos(__citrus_engine_vendor_file_t *file, size_t *pos);
int __citrus_engine_vendor_fseek(__citrus_engine_vendor_file_t *file, size_t offset, int whence);
size_t __citrus_engine_vendor_ftell(__citrus_engine_vendor_file_t *file);

// TODO: rest of C file operations.

#ifdef __cplusplus 
}
#endif

#endif