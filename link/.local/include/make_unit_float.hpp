// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// From the given bits, make a floating-point number within the interval [0, 1).
/**
\file
\author Steven Ward
Inspired by <https://prng.di.unimi.it/>
*/

#pragma once

#include <cstdint>

constexpr float
make_unit_float(const uint32_t x)
{
	// std::numeric_limits<uint32_t>::digits == 32
	// std::numeric_limits<float>::digits == 24
	return static_cast<float>(x >> (32 - 24)) * 0x1p-24F;
}

constexpr double
make_unit_double(const uint64_t x)
{
	// std::numeric_limits<uint64_t>::digits == 64
	// std::numeric_limits<double>::digits == 53
	return (x >> (64 - 53)) * 0x1p-53;
}

constexpr long double
make_unit_long_double(const uint64_t x)
{
	// std::numeric_limits<uint64_t>::digits == 64
	// std::numeric_limits<long double>::digits == 64
	return (x >> (64 - 64)) * 0x1p-64L;
}
