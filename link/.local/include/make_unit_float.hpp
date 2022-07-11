// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// From the given bits, make a floating-point number in the interval [0, 1).
/**
\file
\author Steven Ward
Inspired by <https://prng.di.unimi.it/>
*/

#pragma once

#include "float_bits_union.hpp"

#if 0
// general form

#include "float_bytes.hpp"

#include <concepts>
#include <limits>

template <std::unsigned_integral T>
requires (sizeof(T) == 4 || sizeof(T) == 8)
constexpr auto make_unit_float(const T x)
{
	using f_t = float_bytes<sizeof(x)>;
	static_assert(sizeof(f_t) == sizeof(T));

	// float: 23
	// double: 52
	constexpr auto shift_l = std::numeric_limits<f_t>::digits - 1;

	static_assert(std::numeric_limits<T>::digits >= shift_l);

	// float: 32-23 = 9
	// double: 64-52 = 12
	constexpr auto shift_r = std::numeric_limits<T>::digits - shift_l;

	// float: UINT32_C(0x7F)
	// double: UINT64_C(0x3FF)
	[[maybe_unused]] constexpr auto sign_exp_bits = T{std::numeric_limits<f_t>::max_exponent - 1};

	if constexpr (__BYTE_ORDER__ == __FLOAT_WORD_ORDER__)
		return bits_to_float(sign_exp_bits << shift_l | x >> shift_r) - 1;
	else
		return (x >> shift_r) / f_t{T{1} << shift_l};
}
#else
constexpr float
make_unit_float(const uint32_t x)
{
	if constexpr (__BYTE_ORDER__ == __FLOAT_WORD_ORDER__)
		return bits_to_float(UINT32_C(0x7F) << 23 | x >> 9) - 1;
	else
		return (x >> 9) / 0x1p+23f;
}

constexpr double
make_unit_float(const uint64_t x)
{
	if constexpr (__BYTE_ORDER__ == __FLOAT_WORD_ORDER__)
		return bits_to_float(UINT64_C(0x3FF) << 52 | x >> 12) - 1;
	else
		return (x >> 12) / 0x1p+52;
}
#endif
