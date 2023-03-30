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
#include "core/extensions.h"
#include "core/simd.h"
#include "core/rustints.h"

#define ROTL(x, b) (x << b) | (x >> (sizeof(x)*8 - b))
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

            // TODO: Use SHA256 to generate the required key

            uint8_t key[32];
            xmm_memcpy(key, bytes, 1);
            for(int i = 16; i < 32; i += 8)
                _rdseed64_step((unsigned long long*)(key + i)); // Fuck, where else will we get more random numbers?

            uint64_t unique[2] = {ctr / 16, nonce};
            internals::AES(key, unique, bytes);

            #endif
        }

        /* Currently this only uses ChaCha20 to generate numbers */
        /* TODO: AES-CTR-256 on AMD64 machines */

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
            for(int i = 0; i < 8; i++)
            {
                if(ctr % BYTES_MOD == 0)
                {
                    shuffle();
                }

                ret <<= 8;
                ret |= bytes[ctr % BYTES_MOD];
                ctr++;
            }
            
            return ret;
        }
        
        u32 genU32()
        {
            uint32_t ret = 0;
            for(int i = 0; i < 4; i++)
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
        u16 genU16()
        {
            uint16_t ret = 0;
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
            /* TODO: Optimize this with SIMD and stuff. */

            for(int i = 0; i < len; i++)
            {
                if(ctr % BYTES_MOD == 0)
                {
                    shuffle();
                }

                buffer[i] = bytes[ctr++ % BYTES_MOD];
            }
        }

        friend void engine::internals::initMainRNG();
        friend void engine::internals::getSeedBytes(uint32_t matrix[]);
    } ALIGN(16);

    using RNG = RandomNumberGenerator;
}

#endif