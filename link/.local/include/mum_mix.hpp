// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// MUM mix
/**
\file
\author Steven Ward
\sa https://github.com/vnmakarov/mum-hash
\sa https://github.com/vnmakarov/mum-hash/blob/master/mum.h#L104
\sa https://github.com/vnmakarov/mum-hash/blob/master/mum-prng.h#L74
*/

#pragma once

#include "int_bytes.hpp"

#include <concepts>
#include <limits>

/// Multiply \a a and \a b and return the high and low parts of the product
template <std::unsigned_integral T>
constexpr void
mum(T& a, T& b)
{
	// When T is uint64_t, the multiplication is optimized the same as _mulx_u64.
	/*
	* unsigned long long hi{};
	* const unsigned long long lo = _mulx_u64(a, b, &hi);
	*/
	using T2 = next_larger<T>;
	const T2 r = static_cast<T2>(a) * static_cast<T2>(b);
	const T hi = static_cast<T>(r >> std::numeric_limits<T>::digits);
	const T lo = static_cast<T>(r);
	// https://github.com/wangyi-fudan/wyhash/blob/master/wyhash.h#L56
#if WYHASH_CONDOM > 1
	a ^= hi;
	b ^= lo;
#else
	a = hi;
	b = lo;
#endif
}

/// Multiply \a a and \a b and return the sum of the high and low parts of the product
template <std::unsigned_integral T>
constexpr T
mum_mix_add(T a, T b)
{
	mum(a, b);
	return a + b;
}

/// Multiply \a a and \a b and return the XOR of the high and low parts of the product
template <std::unsigned_integral T>
constexpr T
mum_mix_xor(T a, T b)
{
	mum(a, b);
	return a ^ b;
}
