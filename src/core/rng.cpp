/*
*   name: include/core/rng.cpp
*   origin: Citrus Engine
*   purpose: Provide a CSPRNG for the Citrus Engine
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#define __CITRUS_ENGINE_SOURCE_FILE__

#include "core/os.h"

#ifdef CITRUS_ENGINE_WINDOWS

#include <Bcrypt.h>

#endif

#include <cstdio>
#include <cstring>
#include <atomic>
#include "core/rng.hpp"
#include "core/mem.hpp"
#include "core/extensions.h"

engine::RNG mainRNG ALIGN(64);
std::atomic_bool rngLock;

#ifdef __x86_64__

#define rcon(round) ((round <= 1) ? 1 : (round<<1) ^ (0x11b & -(round>>7)))

ALWAYS_INLINE void roundKey(uint8_t key[], uint8_t rkey[], int round)
{
	uint32_t *K = (uint32_t*)key;
	uint32_t *W = (uint32_t*)rkey;

	if(round * 4 < 8)
	{
		if(((uintptr_t)K) & 0xF && (uintptr_t)W & 0xF)
		{
			xmm_memcpy(W, K + (round * 4), 1);
		}
		else
		{
			memcpy(W, K + (round * 4), 16);
		}
	}
	else
	{
		// That's how it works right? We'll have to check later
		ustore_i128((m128i_t*)(void*)W, _mm_aeskeygenassist_si128(uload_i128(K + ((round & 1) * 4)), rcon(round)));
	}
}

#endif


void engine::internals::initMainRNG()
{
	#ifdef CITRUS_ENGINE_UNIX

	FILE *urand = fopen("/dev/urandom", "r");
	fread(&mainRNG, sizeof(engine::RNG), 1, urand);
	fclose(urand);

	#else

	BCryptGenRandom(NULL, (PUCHAR)&mainRNG, sizeof(engine::RNG), BCRYPT_USE_SYSTEM_PREFERRED_RNG);

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

	if((uintptr_t)matrix & 0x3F == 0) zmm_memcpy(matrix, mainRNG.matrix, 1);
	else if((uintptr_t)matrix & 0x1F == 0) ymm_memcpy(matrix, mainRNG.matrix, 2);
	else xmm_memcpy(matrix, mainRNG.matrix, 4);
	mainRNG.shuffle();

	#else

	xmm_memcpy(matrix, &mainRNG, sizeof(mainRNG)/16);
	mainRNG.ctr += 16;
	mainRNG.shuffle();

	#endif

	rngLock.store(false);
}

#ifdef __x86_64__

void engine::internals::AES(uint8_t key[], uint64_t unique[], uint8_t output[])
{
	m128i_t *rOutput = (m128i_t*)output;
	memcpy(rOutput, unique, 16);
	for(int i = 0; i < 14; i++)
	{
		uint8_t keybuff[16];
		roundKey(key, keybuff, i);
		
		if(i == 13)
			ustore_i128(rOutput, _mm_aesenclast_si128(uload_i128(rOutput), uload_i128(keybuff))); // TODO: alignment checks
		else
			ustore_i128(rOutput, _mm_aesenc_si128(uload_i128(rOutput), uload_i128(keybuff))); // TODO: alignment checks
	}
}

#endif

void SHA256(uint8_t input[], size_t inlen, uint8_t hash[])
{
	uint32_t *digest = (uint32_t*)hash;
	digest[0] = 0x6a09e667;
	digest[1] = 0xbb67ae85;
	digest[2] = 0x3c6ef372;
	digest[3] = 0xa54ff53a;
	digest[4] = 0x510e527f;
	digest[5] = 0x9b05688c;
	digest[6] = 0x1f83d9ab;
	digest[7] = 0x5be0cd19;
	uint32_t k[] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
	size_t realLen;

	uint8_t *buffer = (uint8_t*)engine::memalloc((realLen = inlen + ((inlen + 8) % 64) + 8));
	if((uint64_t)input & 0xF == 0 && inlen % 16 == 0)
		xmm_memcpy(buffer, input, inlen/16);
	else
		memcpy(buffer, input, inlen);

	buffer[inlen] = 0x80;
	memset(buffer + inlen + 1, 0, realLen - inlen - 1);

	((uint64_t*)buffer)[(realLen/8) - 1] = inlen;
	for(size_t i = 0; i < realLen; i += 64)
	{
		uint32_t schedule[64];
		memcpy(schedule, buffer, 64);
		for (size_t i = 16; i < 64; i++)
		{
        	uint32_t s0 = ROTR(schedule[i-15], 7) ^ ROTR(schedule[i-15], 18) ^ ROTR(schedule[i-15], 3);
        	uint32_t s1 = ROTR(schedule[i-2], 17) ^ ROTR(schedule[i-2], 19) ^ ROTR(schedule[i-2], 10);
        	schedule[i] = schedule[i-16] + s0 + schedule[i-7] + s1;
		}

		uint32_t a = digest[0];
		uint32_t b = digest[1];
		uint32_t c = digest[2];
		uint32_t d = digest[3];
		uint32_t e = digest[4];
		uint32_t f = digest[5];
		uint32_t g = digest[6];
		uint32_t h = digest[7];

		for(size_t i = 0; i < 64; i++)
		{
			uint32_t S1 = ROTR(e, 6) ^ ROTR(e, 11) ^ ROTR(e, 25);
			uint32_t ch = (e & f) ^ ((~e) & g);
			uint32_t temp1 = h + S1 + ch + k[i] + schedule[i];
			uint32_t S0 = ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t temp2 = S0 + maj;
 
			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}

		#ifdef __x86_64__

		#ifdef __AVX2__

		m256i_t ymm0;
		m256i_t ymm1;
		uint32_t array[] = {a, b, c, d, e, f, g, h};

		ymm0 = uload_i256(array);
		ymm1 = ((uintptr_t)digest & 0x1F == 0) ? load_i256(digest) : uload_i256(digest);
		ymm1 = add256_i32(ymm0, ymm1);
		if((uintptr_t)digest & 0x1F == 0)
			store_i256(digest, ymm1);
		else
			ustore_i256(digest, ymm1);

		#else

		m128i_t xmm0;
		m128i_t xmm1;
		m128i_t xmm2;
		m128i_t xmm3;

		xmm0 = _mm_setr_epi32(d, c, b, a);
		xmm1 = ((uintptr_t)digest & 0xF == 0) ? load_i128((m128i_t*)(void*)digest) : uload_i128((m128i_t*)(void*)digest);
		xmm2 = _mm_setr_epi32(h, g, f, e);
		xmm3 = ((uintptr_t)digest % 0xF == 0) ? load_i128((m128i_t*)(void*)digest + 4) : uload_i128((m128i_t*)(void*)(digest + 4));

		xmm1 = add_i32(xmm0, xmm1);
		xmm3 = add_i32(xmm2, xmm3);
		
		if((uintptr_t)digest & 0xF == 0)
		{
			store_i128((m128i_t*)(void*)digest, xmm1);
			store_i128((m128i_t*)(void*)(digest + 4), xmm3);
		}
		else
		{
			ustore_i128((m128i_t*)(void*)digest, xmm1);
			ustore_i128((m128i_t*)(void*)(digest + 4), xmm3);
		}

		#endif

		#else

		uint32x4_t Q0;
		uint32x4_t Q1;
		uint32x4_t Q2;
		uint32x4_t Q3;

		Q0 = vld1q_u32({a, b, c, d});
		Q1 = vld1q_u32(digest);
		Q2 = vld1q_u32({e, f, g, h});
		Q3 = vld1q_u32(digest + 4);

		Q1 = vaddq_i32(Q0, Q1);
		Q3 = vaddq_i32(Q2, Q3);
		

		vst1q_u32(digest, Q1);
		vst1q_u32(digest + 4, Q3);

		#endif
	}

	engine::memfree(buffer);
}
