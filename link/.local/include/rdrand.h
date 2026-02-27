// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Get a random number from the hardware RNG
/**
* \file
* \author Steven Ward
* \sa https://stackoverflow.com/a/72265912
* \sa https://en.wikipedia.org/wiki/RDRAND
*/

#pragma once

#include <immintrin.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// _rd{rand,seed}{16,32,64}_step returns 0 if a random value was NOT generated

#if defined(__RDRND__)
static uint16_t
rdrand16()
{
    unsigned short ret = 0;
    static_assert(sizeof(ret) * 8 == 16);
    while (_rdrand16_step(&ret) == 0)
    {}
    return ret;
}

static uint32_t
rdrand32()
{
    unsigned int ret = 0;
    static_assert(sizeof(ret) * 8 == 32);
    while (_rdrand32_step(&ret) == 0)
    {}
    return ret;
}

static uint64_t
rdrand64()
{
    unsigned long long ret = 0;
    static_assert(sizeof(ret) * 8 == 64);
    while (_rdrand64_step(&ret) == 0)
    {}
    return ret;
}
#else
#warning "__RDRND__ not defined"
#endif

#if defined(__RDSEED__)
static uint16_t
rdseed16()
{
    unsigned short ret = 0;
    static_assert(sizeof(ret) * 8 == 16);
    while (_rdseed16_step(&ret) == 0)
    {}
    return ret;
}

static uint32_t
rdseed32()
{
    unsigned int ret = 0;
    static_assert(sizeof(ret) * 8 == 32);
    while (_rdseed32_step(&ret) == 0)
    {}
    return ret;
}

static uint64_t
rdseed64()
{
    unsigned long long ret = 0;
    static_assert(sizeof(ret) * 8 == 64);
    while (_rdseed64_step(&ret) == 0)
    {}
    return ret;
}
#else
#warning "__RDSEED__ not defined"
#endif

#ifdef __cplusplus
} // extern "C"
#endif
