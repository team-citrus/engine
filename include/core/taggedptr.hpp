#ifndef CITRUS_ENGINE_CORE_TAGGED_POINTERS_HPP__
#define CITRUS_ENGINE_CORE_TAGGED_POINTERS_HPP__

#include <cstdint>

/* Defines for tagging pointers */

#define PHYSICS_SIM_TAG 0x100000000000000
#define CORE_CRITICAL_TAG 0xFF000000000000
#define CORE_RESOURCE_LOC_TABLE_TAG 0x7E000000000000
#define CORE_FUNC_PTR_TAG 0x7F000000000000

#define DETAG_PTR(ptr) (ptr & 0xFFFFFFFFFFFFFF)
#define TAG_PTR(ptr, tag) (ptr | tag)
#define EXTRACT_TAG(ptr) (ptr & ~0xFFFFFFFFFFFFFF)
#define TAG_TO_UINT8(ptr) ((uint16_t)(EXTRACT_TAG(ptr) >> 38))
#define CHECK_TAG(ptr, tag) (!(ptr ^ tag))

#endif