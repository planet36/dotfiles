// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get a random number from the hardware RNG
/**
\file
\author Steven Ward
\sa https://stackoverflow.com/a/72265912
\sa https://en.wikipedia.org/wiki/RDRAND
*/

#pragma once

#include <immintrin.h>

// _rd{rand,seed}{16,32,64}_step returns 0 if a random value was NOT generated

#if defined(__RDRND__)
static unsigned short
rdrand16()
{
	unsigned short ret = 0;
	static_assert(sizeof(ret) * 8 == 16);
	while (_rdrand16_step(&ret) == 0)
	{}
	return ret;
}

static unsigned int
rdrand32()
{
	unsigned int ret = 0;
	static_assert(sizeof(ret) * 8 == 32);
	while (_rdrand32_step(&ret) == 0)
	{}
	return ret;
}

static unsigned long long
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
static unsigned short
rdseed16()
{
	unsigned short ret = 0;
	static_assert(sizeof(ret) * 8 == 16);
	while (_rdseed16_step(&ret) == 0)
	{}
	return ret;
}

static unsigned int
rdseed32()
{
	unsigned int ret = 0;
	static_assert(sizeof(ret) * 8 == 32);
	while (_rdseed32_step(&ret) == 0)
	{}
	return ret;
}

static unsigned long long
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
