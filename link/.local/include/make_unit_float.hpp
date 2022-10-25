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
	return (x >> (32-24)) * 0x1p-24f;
}

constexpr double
make_unit_double(const uint64_t x)
{
	return (x >> (64-53)) * 0x1p-53;
}

constexpr long double
make_unit_long_double(const uint64_t x)
{
	return (x >> (64-64)) * 0x1p-64L;
}
