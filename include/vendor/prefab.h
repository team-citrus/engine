/*
*   name: include/vendor/prefab.hpp
*   origin: Citrus Engine
*   purpose: Vendor interface prefab functions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: MIT
*/

#ifndef __CITRUS_ENGINE_VENDOR_INTERFACE_HEADERS_PREFAB_H__
#define __CITRUS_ENGINE_VENDOR_INTERFACE_HEADERS_PREFAB_H__

#ifdef __cplusplus 
extern "C" {
#endif

typedef struct __citrus_engine_vendor_prefab_t __citrus_engine_vendor_prefab_t;

__citrus_engine_vendor_prefab_t *__citrus_engine_vendor_get_prefab(const char *name);
void __citrus_engine_vendor_prefab_to_object(void *obj);

#ifdef __cplusplus 
}
#endif

#endif