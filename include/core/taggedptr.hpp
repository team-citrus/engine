/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

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