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

namespace engine
{
    namespace internals
    {
        void initMainRNG();
        void getSeedBytes(uint32_t matrix[]);
    }

    class RandomNumberGenerator
    {
        union
        {
            uint32_t matrix[16];
            uint8_t bytes[64];
        };
        
        int ctr;

        void QR(int a, int b, int c, int d)
        {
            // TODO: SIMD optimizations
            matrix[a] += matrix[b]; matrix[d] ^= matrix[a]; matrix[d] = ROTL(matrix[d], 16);
            matrix[c] += matrix[d]; matrix[b] ^= matrix[c]; matrix[b] = ROTL(matrix[d], 12);
            matrix[a] += matrix[b]; matrix[d] ^= matrix[a]; matrix[d] = ROTL(matrix[d], 8);
            matrix[c] += matrix[d]; matrix[b] ^= matrix[c]; matrix[b] = ROTL(matrix[d], 7);
        }

        void shuffle()
        {
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
		        QR(2, 7, 8, 13]);
		        QR(3, 4, 9], 14);
            }

            #ifndef __x86_64__

            // Use Neon on non-AMD64 systems
            uint32x4_t *nmatrix = &matrix[0];
            uint32x4_t *iomatrix = &omatrix[0];

            for(int i = 0; i < 4; i++)
                vst1q_u32((uint32_t*)nmatrix + (i * 4), vaddq_u32(vld1q_u32((uint32_t*)nmatrix + (i * 4), vld1q_u32((uint32_t*)iomatrix + (i * 4)))));
            
            #elif _MAVX_ >= 512

            _mm512_storeu_si512(&matrix[0], _mm512_add_epi32(_mm512_loadu_si512(&matrix[0]), _mm512_loadu_si512(&omatrix[0])));

            #elif _MAVX_ == 2

            m256i_t *nmatrix = &matrix[0];
            m256i_t *iomatrix = &omatrix[0];

            ustore_i256(nmatrix, add256_i32(uload_i256(nmatrix), uload_i256(iomatrix)));
            ustore_i256(nmatrix + 1, add256_i32(uload_i256(nmatrix + 1), uload_i256(iomatrix + 1)));

            #else

            m128i_t *nmatrix = &matrix[0];
            m128i_t *iomatrix = &omatrix[0];

            for(int i = 0; i < 4; i++)
                store_i128(nmatrix + i, add_i32(load_i128(nmatrix + i), load_i128(iomatrix + i)));

            #endif
        }

        /* Currently this only uses ChaCha20 to generate numbers */
        /* TODO: AES-CTR-256 on AMD64 machines */

        public:

        RandomNumberGenerator()
        {
            internals::getSeedBytes(matrix);

            matrix[0] = 0x61707865;
            matrix[1] = 0x3320646e;
            matrix[2] = 0x79622d32;
            matrix[3] = 0x6b206574;
            matrix[12] = 0;
            ctr = 0;
        }

        u64 genU64()
        {
            uint64_t ret = 0;
            for(int i = 0; i < 8; i++)
            {
                if(ctr % 64 == 0)
                {
                    shuffle();
                }

                ret <<= 8;
                ret |= bytes[ctr % 64];
                ctr++;
            }
            
            return ret;
        }
        
        u32 genU32()
        {
            uint32_t ret = 0;
            for(int i = 0; i < 4; i++)
            {
                if(ctr % 64 == 0)
                {
                    shuffle();
                }

                ret <<= 8;
                ret |= bytes[ctr % 64];
                ctr++;
            }
        }
        u16 genU16()
        {
            uint16_t ret = 0;
            for(int i = 0; i < 2; i++)
            {
                if(ctr % 64 == 0)
                {
                    shuffle();
                }

                ret <<= 8;
                ret |= bytes[ctr % 64];
                ctr++;
            }
        }
        u8 genU8()
        {
            if(ctr % 64 == 0)
            {
                shuffle();
            }

            return bytes[ctr++ % 64];
        }
        
        void genBytes(uint8_t *buffer, size_t len)
        {
            /* TODO: Optimize this with SIMD and stuff. */

            for(int i = 0; i < len; i++)
            {
                if(ctr % 64 == 0)
                {
                    shuffle();
                }

                buffer[i] = bytes[ctr++ % 64];
            }
        }

        friend void engine::internals::initMainRNG();
        friend void engine::internals::getSeedBytes(uint32_t matrix[]);
    } ALIGN(16);

    using RNG = RandomNumberGenerator;
}

#endif