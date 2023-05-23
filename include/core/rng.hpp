/*
*   name: include/core/rng.hpp
*   origin: Citrus Engine
*   purpose: Provide a CSPRNG for the Citrus Engine
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_CSPRNG_HPP__
#define CITRUS_ENGINE_CSPRNG_HPP__

#include <cstring>
#include "../core/extensions.h"
#include "../core/simd.h"
#include "../core/rustints.h"
#include "../core/hash.hpp"

#ifndef __x86_64__
#define BYTES_MOD 64
#else
#define BYTES_MOD 16
#endif

namespace engine
{
	namespace internals
	{
		void initMainRNG();
		void getSeedBytes(uint32_t matrix[]);

		#ifdef __x86_64__
		void AES(uint8_t key[], uint64_t unique[], uint8_t output[]);
		#endif
	}

	void SHA256(uint8_t input[], size_t inlen, uint8_t hash[]);

	class RandomNumberGenerator
	{
		union
		{
			uint32_t matrix[BYTES_MOD/4];
			uint8_t bytes[BYTES_MOD];
		};
		
		uint64_t ctr;

		#ifdef __x86_64__

		uint64_t nonce;

		#endif

		#ifndef __x86_64__

		void QR(int a, int b, int c, int d)
		{
			// TODO: SIMD optimizations
			matrix[a] += matrix[b]; matrix[d] ^= matrix[a]; matrix[d] = ROTL(matrix[d], 16);
			matrix[c] += matrix[d]; matrix[b] ^= matrix[c]; matrix[b] = ROTL(matrix[d], 12);
			matrix[a] += matrix[b]; matrix[d] ^= matrix[a]; matrix[d] = ROTL(matrix[d], 8);
			matrix[c] += matrix[d]; matrix[b] ^= matrix[c]; matrix[b] = ROTL(matrix[d], 7);
		}

		#endif

		void shuffle()
		{
			#ifndef __x86_64__
			uint32_t omatrix[16];
			memcpy(omatrix, matrix, 64);
			for(int i = 0; i < 10; i++)
			{
				// TODO: Assembly version with no load stores until the end
				QR(0, 4, 8, 12);
				QR(1, 5, 9, 13);
				QR(2, 6, 10, 14);
				QR(3, 7, 11, 15);
				QR(0, 5, 10, 15);
				QR(1, 6, 11, 12);
				QR(2, 7, 8, 13);
				QR(3, 4, 9, 14);	
			}

			// Use Neon on non-AMD64 systems
			uint32x4_t *nmatrix = &matrix[0];
			uint32x4_t *iomatrix = &omatrix[0];

			for(int i = 0; i < 4; i++)
				vst1q_u32((uint32_t*)nmatrix + (i * 4), vaddq_u32(vld1q_u32((uint32_t*)nmatrix + (i * 4), vld1q_u32((uint32_t*)iomatrix + (i * 4)))));
			
			#else

			uint8_t key[32];
			SHA256(bytes, BYTES_MOD, key);

			uint64_t unique[2] = {ctr / 16, nonce};
			internals::AES(key, unique, bytes);

			#endif
		}

		public:

		RandomNumberGenerator()
		{
			#ifndef __x86_64__
			internals::getSeedBytes(matrix);

			matrix[0] = 0x61707865;
			matrix[1] = 0x3320646e;
			matrix[2] = 0x79622d32;
			matrix[3] = 0x6b206574;
			matrix[12] = 0;
			ctr = 0;

			#else

			internals::getSeedBytes((uint32_t*)this);
			ctr = 0;

			#endif
		}

		u64 genU64()
		{
			uint64_t ret = 0;
			if(ctr & BYTES_MOD <= 8)
			{
				ret = *(uint64_t*)(bytes + (ctr & BYTES_MOD));
				ctr += 8;
			}
			else
			{
				for(int i = 0; i < 8; i++)
				{
					if(ctr & BYTES_MOD == 0)
					{
						shuffle();
					}

					ret <<= 8;
					ret |= bytes[ctr & BYTES_MOD];
					ctr++;
				}
			}
			return ret;
		}
		
		u32 genU32()
		{
			uint32_t ret = 0;
			if(ctr % BYTES_MOD <= 4)
			{
				ret = *(uint64_t*)(bytes + (ctr & BYTES_MOD));
				ctr += 4;
			}
			else
			{
				for(int i = 0; i < 4; i++)
				{
					if(ctr & BYTES_MOD == 0)
					{
						shuffle();
					}

					ret <<= 4;
					ret |= bytes[ctr & BYTES_MOD];
					ctr++;
				}
			}
			return ret;
		}
		u16 genU16()
		{
			uint16_t ret = 0;
			if(ctr % BYTES_MOD <= 2)
			{
				ret = *(uint16_t*)(bytes + (ctr & BYTES_MOD));
				ctr += 2;
			}
			else
			{
				for(int i = 0; i < 2; i++)
				{
					if(ctr % BYTES_MOD == 0)
					{
						shuffle();
					}

					ret <<= 8;
					ret |= bytes[ctr % BYTES_MOD];
					ctr++;
				}
			}
			return ret;
		}
		u8 genU8()
		{
			if(ctr % BYTES_MOD == 0)
			{
				shuffle();
			}

			return bytes[ctr++ % BYTES_MOD];
		}
		
		void genBytes(uint8_t *buffer, size_t len)
		{
			if(len > BYTES_MOD)
			{
				ctr = (ctr + (BYTES_MOD-1)) & ~(BYTES_MOD-1);
				shuffle();
				size_t i;
				for(i = 0; i < len/BYTES_MOD; i++, shuffle())
				{
					memcpy(buffer + (i * BYTES_MOD), matrix, BYTES_MOD);
					ctr += BYTES_MOD;
				}

				if(len & BYTES_MOD)
					genBytes(buffer + (i * BYTES_MOD), len & BYTES_MOD);
			}
			#ifndef __x86_64__
			else if(len > 16)
			{
				size_t i;
				ctr = ((ctr + (16-1)) & ~(16-1);
				for(i = 0; i < len >> 4; i++, ctr += 16)
				{
					if(ctr & (BYTES_MOD) == 0)
						shuffle();

					vst1q_u64((buffer + (i << 4)), vld1q_u64(bytes + (ctr & BYTES_MOD)));
				}

				if(len & 0xF)
					genBytes(buffer + (i << 4), len & 0xF);
			}
			#endif

			else if(len > 8)
			{
				size_t i;
				ctr = ((ctr + (8-1)) & ~(8-1));
				for(i = 0; i < len/8; i++, ctr += 8)
				{
					if(ctr & BYTES_MOD == 0)
						shuffle();

					((uint64_t*)buffer)[i] = *(uint64_t*)(bytes + (ctr & BYTES_MOD));
				}
				genBytes(buffer + (i << 3), len & 0x7);
			}
			else if(len > 4)
			{
				size_t i;
				ctr = ((ctr + (4-1)) & ~(4-1));
				for(i = 0; i < len/4; i++, ctr += 4)
				{
					if(ctr & BYTES_MOD == 0)
						shuffle();

					((uint32_t*)buffer)[i] = *(uint32_t*)(matrix + (ctr & BYTES_MOD));
				}
				genBytes(buffer + (i << 2), len & 0x3);
			}
			else
			{
				for(size_t i = 0; i < len; i++, ctr++)
				{
					if(ctr % BYTES_MOD == 0)
						shuffle();

					buffer[i] = bytes[i];
				}
			}
		}

		friend void engine::internals::initMainRNG();
		friend void engine::internals::getSeedBytes(uint32_t matrix[]);
	} ALIGN(16);

	using RNG = RandomNumberGenerator;
}

#endif
