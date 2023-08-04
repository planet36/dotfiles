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

inline auto
rdrand16()
{
	unsigned short ret{};
	while (_rdrand16_step(&ret) == 0)
	{}
	return ret;
}

inline auto
rdrand32()
{
	unsigned int ret{};
	while (_rdrand32_step(&ret) == 0)
	{}
	return ret;
}

inline auto
rdrand64()
{
	unsigned long long ret{};
	while (_rdrand64_step(&ret) == 0)
	{}
	return ret;
}

inline auto
rdseed16()
{
	unsigned short ret{};
	while (_rdseed16_step(&ret) == 0)
	{}
	return ret;
}

inline auto
rdseed32()
{
	unsigned int ret{};
	while (_rdseed32_step(&ret) == 0)
	{}
	return ret;
}

inline auto
rdseed64()
{
	unsigned long long ret{};
	while (_rdseed64_step(&ret) == 0)
	{}
	return ret;
}
