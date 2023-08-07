// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// MUM mix
/**
\file
\author Steven Ward
\sa https://github.com/vnmakarov/mum-hash
\sa https://github.com/vnmakarov/mum-hash/blob/master/mum.h#L104
\sa https://github.com/vnmakarov/mum-hash/blob/master/mum-prng.h#L74
\sa https://github.com/gcc-mirror/gcc/blob/master/gcc/config/i386/bmi2intrin.h#L83
*/

#pragma once

#include "int_bytes.hpp"
#include "simd-types.hpp"

#include <concepts>
#include <cstdint>
#include <immintrin.h>
#include <limits>

/// Multiply \a a and \a b and return the high and low parts of the product
template <std::unsigned_integral T>
constexpr void
mul(T& a, T& b)
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
	mul(a, b);
	return a + b;
}

/// Multiply \a a and \a b and return the XOR of the high and low parts of the product
template <std::unsigned_integral T>
constexpr T
mum_mix_xor(T a, T b)
{
	mul(a, b);
	return a ^ b;
}

/// Multiply \a a and \a b and return the difference of the high and low parts of the product
template <std::unsigned_integral T>
constexpr T
mum_mix_sub(T a, T b)
{
	mul(a, b);
	return a - b;
}

// The hi bits will go in a, and the lo bits will go in b
void clmul(uint64_t& a, uint64_t& b)
{
	const simd128 tmp{.u64{a, b}}; // order of a, b doesn't matter

	// https://github.com/gcc-mirror/gcc/blob/master/gcc/config/i386/wmmintrin.h#L103
	// _mm_clmulepi64_si128(__m128i a, __m128i b, int imm8)
	// imm8: 0x00 => b[0] * a[0]
	// imm8: 0x01 => b[0] * a[1]
	// imm8: 0x10 => b[1] * a[0]
	// imm8: 0x11 => b[1] * a[1]

	// MSB in result is always 0
	const __m128i result = _mm_clmulepi64_si128(tmp.i64, tmp.i64, 0x10);

	a = result[1]; // hi
	b = result[0]; // lo
}

uint64_t clmul_mix_xor(uint64_t a, uint64_t b) { clmul(a, b); return a ^ b; }
uint64_t clmul_mix_add(uint64_t a, uint64_t b) { clmul(a, b); return a + b; }
uint64_t clmul_mix_sub(uint64_t a, uint64_t b) { clmul(a, b); return a - b; }
