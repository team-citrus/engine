/*
*   name: src/core/input.cpp
*   origin: Citrus Engine
*   purpose: The code for the input system
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
#include "core/input.hpp"
#include "core/simd.h"

// Welcome to portability hell, population, us

// TODO: Lucky me I get to rewrite this
#ifdef CITRUS_ENGINE_WINDOWS

#include <Windows.h>
ALIGN(64) uint8_t engine::internals::currentInput[256];
ALIGN(64) uint8_t engine::internals::prevInput[256]; // Used for getKeyDown and getMouseButtonDown

// Returns true while a key is down
bool engine::getKey(char key)
{
	return (engine::internals::currentInput[key] >> 7) == 1;
}

// Returns true the first frame a key is down
bool engine::getKeyDown(char key)
{
	return ((engine::internals::currentInput[key] >> 7) == 1) && ((engine::internals::prevInput[key] >> 7) == 0);
}

// Returns true when a key is released
bool engine::getKeyUp(char key)
{
	return ((engine::internals::currentInput[key] >> 7) == 0) && ((engine::internals::prevInput[key] >> 7) == 1);
}

// Returns true while a key is down
bool engine::getMouseButton(int num)
{
	switch (num)
	{
		case 1:
		return engine::getKey(VK_LBUTTON);
		case 2:
		return engine::getKey(VK_MBUTTON);
		case 3:
		return engine::getKey(VK_RBUTTON);
		default:
		return false;
	}
}
// Returns true the first frame a key is down
bool engine::getMouseButtonDown(int num)
{
	switch (num)
	{
		case 1:
		return engine::getKeyDown(VK_LBUTTON);
		case 2:
		return engine::getKeyDown(VK_MBUTTON);
		case 3:
		return engine::getKeyDown(VK_RBUTTON);
		default:
		return false;
	}
}
// Returns true when a key is released
bool getMouseButtonUp(int num)
{
	switch (num)
	{
		case 1:
		return engine::getKeyUp(VK_LBUTTON);
		case 2:
		return engine::getKeyUp(VK_MBUTTON);
		case 3:
		return engine::getKeyUp(VK_RBUTTON);
		default:
		return false;
	}
}

bool engine::anyKey()
{
	for(int i = 0; i < 8; i++)
	{
		#if _MAVX_ == 2

		m256i_t buffer = load_i256(engine::internals::currentInput  + (i * 32));
		if(_mm256_movemask_epi8(_mm256_cmpeq_epi8(buffer, broadcast256_i64(0))) != 0)
			return true;

		#elif defined(__x86_64__)

		m128i_t buffer = load_i128((const m128i_t*)(engine::internals::currentInput + (i * 32)));
		if(extractbools_i8(equals_i8(buffer, broadcast_i8(0))) != 0)
			return true;

		buffer = load_i128((const m128i_t*)(engine::internals::currentInput + 16  + (i * 32)));
		if(_mm_movemask_epi8(_mm_cmpeq_epi8(buffer, broadcast_i8(0))) != 0)
			return true;

		#else

		int32_t zero = 0;	
		int32x4_t buffer = vld1q_s32((uint32_t*)(engine::internals::currentInput  + (i * 32)));
		int32x4_t bools = vceqq_s32(buffer, vld1q_dup_s32(&zero));
	
		if(vgetq_lane_u32(bools, 0) != 0) return true;
		if(vgetq_lane_u32(bools, 1) != 0) return true;
		if(vgetq_lane_u32(bools, 2) != 0) return true;
		if(vgetq_lane_u32(bools, 3) != 0) return true;

		buffer = vld1q_s32((uint32_t*)(engine::internals::currentInput + 16 + (i * 32)));
		bools = vceqq_s32(buffer, vld1q_dup_s32(&zero));

		if(vgetq_lane_u32(bools, 0) != 0) return true;
		if(vgetq_lane_u32(bools, 1) != 0) return true;
		if(vgetq_lane_u32(bools, 2) != 0) return true;
		if(vgetq_lane_u32(bools, 3) != 0) return true;

		#endif
	}
	return false;
}

#else

#include "core/XLibglobals.hpp"
#include "core/extensions.h"

ALIGN(32) uint8_t engine::internals::currentInput[32];
ALIGN(32) uint8_t engine::internals::prevInput[32]; // Used for getKeyDown and getMouseButtonDown

// Returns true while a key is down
bool engine::getKey(char key)
{
	return (engine::internals::currentInput[key/8] >> (key % 8)) & 1;
}

bool engine::getKeyDown(char key)
{
	return ((engine::internals::currentInput[key/8] >> (key % 8)) & 1) && (((engine::internals::prevInput[key/8] >> (key % 8)) & 1) == 0);
}

bool engine::getKeyUp(char key)
{
	return (((engine::internals::currentInput[key/8] >> (key % 8)) & 1) == 0) && ((engine::internals::prevInput[key/8] >> (key % 8)) & 1);
}

// Returns true while a key is down
bool engine::getMouseButton(int num)
{
	XEvent in;
	if(XCheckMaskEvent(engine::internals::display, ButtonPressMask, &in))
	{
		if((in.xbutton.button == num) && ((in.xbutton.time - engine::internals::gameStart) >= engine::internals::frameStart))
			return true;
	}
	return false;
}

// Returns true the first frame a key is down
bool engine::getMouseButtonDown(int num)
{
	// TODO: This
}
// Returns true when a key is released
bool engine::getMouseButtonUp(int num)
{
	XEvent in;
	if(XCheckMaskEvent(engine::internals::display, ButtonReleaseMask, &in))
	{
		if((in.xbutton.button == num) && ((in.xbutton.time - engine::internals::gameStart) >= engine::internals::frameStart))
			return true;
	}
	return false;
}

bool engine::anyKey()
{
	#if _MAVX_ == 2

	m256i_t buffer = load_i256(engine::internals::currentInput);
	if(_mm256_movemask_epi8(_mm256_cmpeq_epi8(buffer, broadcast256_i64(0))) != 0)
		return true;

	#elif defined(__x86_64__)

	m128i_t buffer = load_i128((const m128i_t*)engine::internals::currentInput);
	if(extractbools_i8(equals_i8(buffer, broadcast_i8(0))) != 0)
		return true;

	buffer = load_i128((const m128i_t*)(engine::internals::currentInput + 16));
	if(_mm_movemask_epi8(_mm_cmpeq_epi8(buffer, broadcast_i8(0))) != 0)
		return true;

	#else

	int32_t zero = 0;	
	int32x4_t buffer = vld1q_s32((uint32_t*)engine::internals::currentInput);
	int32x4_t bools = vceqq_s32(buffer, vld1q_dup_s32(&zero));
	
	if(vgetq_lane_u32(bools, 0) != 0) return true;
	if(vgetq_lane_u32(bools, 1) != 0) return true;
	if(vgetq_lane_u32(bools, 2) != 0) return true;
	if(vgetq_lane_u32(bools, 3) != 0) return true;

	buffer = vld1q_s32((uint32_t*)(engine::internals::currentInput + 16));
	bools = vceqq_s32(buffer, vld1q_dup_s32(&zero));

	if(vgetq_lane_u32(bools, 0) != 0) return true;
	if(vgetq_lane_u32(bools, 1) != 0) return true;
	if(vgetq_lane_u32(bools, 2) != 0) return true;
	if(vgetq_lane_u32(bools, 3) != 0) return true;

	#endif

	return false;
}

#endif