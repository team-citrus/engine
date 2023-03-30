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

#include "core/rng.hpp"

engine::RNG mainRNG ALIGN(64);

void engine::internals::initMainRNG()
{
    #ifndef _WIN32

    FILE *urand = fopen("/dev/urandom", "r");
    fread(&mainRNG, sizeof(engine::RNG), 1, urand);
    fclose(urand);

    #else

    BCryptGenRandom(NULL, &mainRNG, sizeof(engine::RNG), BCRYPT_USE_SYSTEM_PREFERRED_RNG);

    #endif

    mainRNG.matrix[0] = 0x61707865;
    mainRNG.matrix[1] = 0x3320646e;
    mainRNG.matrix[2] = 0x79622d32;
    mainRNG.matrix[3] = 0x6b206574;
    mainRNG.matrix[12] = 0;
    mainRNG.ctr = 0;
}

void engine::internals::getSeedBytes(uint32_t matrix[])
{
    if((uintptr_t)matrix & 0x3F) zmm_memcpy(matrix, mainRNG.matrix, 64);
    else if((uintptr_t)matrix & 0x1F) ymm_memcpy(matrix, mainRNG.matrix, 64);
    else xmm_memcpy(matrix, mainRNG.matrix, 64);
    mainRNG.shuffle();
}