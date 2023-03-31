/*
*   name: include/core/rng.cpp
*   origin: Citrus Engine
*   purpose: Provide a CSPRNG for the Citrus Engine
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif

#include <cstdio>
#include <atomic>
#include "core/rng.hpp"

engine::RNG mainRNG ALIGN(64);
std::atomic_bool rngLock;

#ifdef __x86_64__

ALWAYS_INLINE uint8_t rcon(int round)
{
	if(round <= 1) return 1;
	else (round<<1) ^ (0x11b & -(round>>7));
}

ALWAYS_INLINE void roundKey(uint8_t key[], uint8_t rkey[], int round)
{
	uint32_t *K = key;
	uint32_t *W = rkey;

	if(round * 4 < 8)
	{
		if((uintptr_t)K & 0xF && (uintptr_t)W & 0xF)
		{
			xmm_memcpy(W, K + (round * 4), 1);
		}
		else
		{
			ustore_i128(W, uload_i128(K + (round * 4)));
		}
	}
	else
	{
		// That's how it works right? We'll have to check later
		ustore_i128((m128i_t*)W, _mm_aeskeygenassist_si128(uload_i128(K + ((round & 1) * 4)), rcon(round)));
	}
}

#endif


void engine::internals::initMainRNG()
{
	#ifndef _WIN32

	FILE *urand = fopen("/dev/urandom", "r");
	fread(&mainRNG, sizeof(engine::RNG), 1, urand);
	fclose(urand);

	#else

	BCryptGenRandom(NULL, &mainRNG, sizeof(engine::RNG), BCRYPT_USE_SYSTEM_PREFERRED_RNG);

	#endif

	#ifndef __x86_64__

	mainRNG.matrix[0] = 0x61707865;
	mainRNG.matrix[1] = 0x3320646e;
	mainRNG.matrix[2] = 0x79622d32;
	mainRNG.matrix[3] = 0x6b206574;
	mainRNG.matrix[12] = 0;
	mainRNG.ctr = 0;

	#endif

	rngLock.store(false);
}

void engine::internals::getSeedBytes(uint32_t matrix[])
{
	while(rngLock.load())
		spinlock_pause();

	rngLock.store(true);

	#ifndef __x86_64__

	if((uintptr_t)matrix & 0x3F) zmm_memcpy(matrix, mainRNG.matrix, 1);
	else if((uintptr_t)matrix & 0x1F) ymm_memcpy(matrix, mainRNG.matrix, 2);
	else xmm_memcpy(matrix, mainRNG.matrix, 4);
	mainRNG.shuffle();

	#else

	if((uintptr_t)matrix & 0x1F) ymm_memcpy(matrix, &mainRNG, sizeof(mainRNG)/32);
	else xmm_memcpy(matrix, &mainRNG, sizeof(mainRNG)/16);
	mainRNG.ctr += 16;
	mainRNG.shuffle();

	#endif

	rngLock.store(false);
}

#ifdef __x86_64__

void engine::internals::AES(uint8_t key[], uint64_t unique[], uint8_t output[])
{
	ustore_i128(output, uload_i128(unique));
	for(int i = 0; i < 14; i++)
	{
		uint8_t keybuff[16];
		roundKey(key, keybuff, i);
		
		switch(i)
		{
			case 13:

			ustore_i128(output, _mm_aesenclast_si128(uload_i128(output), uload_i128(keybuff)));

			break;

			default:

			ustore_i128(output, _mm_aesenc_si128(uload_i128(output), uload_i128(keybuff)));

			break;
		}
	}
}

#endif