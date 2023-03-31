/*
*   name: include/core/hash.cpp
*   origin: Citrus Engine
*   purpose: Provide the code for the functions in core/hash.hpp
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include <cstddef>
#include <cstdint>
#include "core/hash.hpp"
#include "core/vector.hpp"
#include "core/mem.hpp"
#include "core/simd.h"

#define ROTATE(x, b) (uint64_t)( ((x) << (b)) | ( (x) >> (64 - (b))) )

#define HALF_ROUND(a,b,c,d,s,t)			\
	a += b; c += d;				\
	b = ROTATE(b, s) ^ a;			\
	d = ROTATE(d, t) ^ c;			\
	a = ROTATE(a, 32);

#define DOUBLE_ROUND(v0,v1,v2,v3)		\
	HALF_ROUND(v0,v1,v2,v3,13,16);		\
	HALF_ROUND(v2,v1,v0,v3,17,21);		\
	HALF_ROUND(v0,v1,v2,v3,13,16);		\
	HALF_ROUND(v2,v1,v0,v3,17,21);

engine::hash_t engine::hash(void *data, size_t bytes)
{
	static uintptr_t _key_[] = { ROTATE((uintptr_t)engine::hash, 32), ROTATE((uintptr_t)engine::memalloc, 32) };
	uint64_t *key = (uint64_t*)_key_;
	uint64_t k0 = key[0];
	uint64_t k1 = key[1];
	uint64_t b = (uint64_t)bytes << 56;
	uint64_t *in = (uint64_t*)data;

	uint64_t v0 = k0 ^ 0x736f6d6570736575ULL;
	uint64_t v1 = k1 ^ 0x646f72616e646f6dULL;
	uint64_t v2 = k0 ^ 0x6c7967656e657261ULL;
	uint64_t v3 = k1 ^ 0x7465646279746573ULL;

	while (bytes >= 8)
	{
		uint64_t mi = *in;
		in += 1; bytes -= 8;
		v3 ^= mi;
		DOUBLE_ROUND(v0,v1,v2,v3);
		v0 ^= mi;
	}

	uint64_t t = 0; uint8_t *pt = (uint8_t *)&t; uint8_t *m = (uint8_t *)in;
	switch (bytes)
	{
		case 7: pt[6] = m[6];
		case 6: pt[5] = m[5];
		case 5: pt[4] = m[4];
		case 4: *((uint32_t*)&pt[0]) = *((uint32_t*)&m[0]); break;
		case 3: pt[2] = m[2];
		case 2: pt[1] = m[1];
		case 1: pt[0] = m[0];
	}
	b |= t;

	v3 ^= b;
	DOUBLE_ROUND(v0,v1,v2,v3);
	v0 ^= b; v2 ^= 0xff;
	DOUBLE_ROUND(v0,v1,v2,v3);
	DOUBLE_ROUND(v0,v1,v2,v3);
	return (v0 ^ v1) ^ (v2 ^ v3);
}