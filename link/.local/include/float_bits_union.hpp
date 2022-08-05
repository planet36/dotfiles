// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// get/set the bit representation of floating-point values
/**
\file
\author Steven Ward
*/

#pragma once

#include <concepts>
#include <cstdint>

static_assert(sizeof(uint32_t) == sizeof(float));
static_assert(sizeof(uint64_t) == sizeof(double));
static_assert(__BYTE_ORDER__ == __FLOAT_WORD_ORDER__);

template <unsigned int N>
union float_bits_union;

template <>
union float_bits_union<4>
{
	uint32_t i = 0;
	float f;
};

template <>
union float_bits_union<8>
{
	uint64_t i = 0;
	double f;
};

template <std::floating_point T>
requires (sizeof(T) == 4 || sizeof(T) == 8)
constexpr auto
float_to_bits(const T x)
{
	return float_bits_union<sizeof(T)>{.f = x}.i;
}

template <std::unsigned_integral T>
requires (sizeof(T) == 4 || sizeof(T) == 8)
constexpr auto
bits_to_float(const T x)
{
	return float_bits_union<sizeof(T)>{.i = x}.f;
}
