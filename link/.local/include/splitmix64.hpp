// SPDX-FileCopyrightText: Sebastiano Vigna (vigna@acm.org)
// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: CC0-1.0

/// splitmix64 PRNG
/**
\file
\author Steven Ward
\sa https://prng.di.unimi.it/splitmix64.c
*/

#pragma once

#include "fill_rand.hpp"

#include <cstdint>
#include <limits>
#include <type_traits>

// https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator
#define NAMED_REQ_URBG(RESULT_TYPE)                     \
	using result_type = RESULT_TYPE;                    \
	static_assert(std::is_unsigned_v<result_type>);     \
	static constexpr result_type min()                  \
	{                                                   \
		return std::numeric_limits<result_type>::min(); \
	}                                                   \
	static constexpr result_type max()                  \
	{                                                   \
		return std::numeric_limits<result_type>::max(); \
	}                                                   \
	result_type operator()() { return next(); }

/** This is a fixed-increment version of Java 8's SplittableRandom generator
 * See https://dl.acm.org/doi/10.1145/2714064.2660195 and
 * https://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html
 *
 * It is a very fast generator passing BigCrush, and it can be useful if
 * for some reason you absolutely want 64 bits of state.
 */
struct splitmix64
{
	using T = uint64_t;

NAMED_REQ_URBG(T)

private:
	T s{};

public:
	splitmix64() { fill_rand(s); }

	splitmix64(const decltype(s)& new_s): s(new_s) {}

	void seed(const decltype(s)& new_s) { s = new_s; }

	T next()
	{
		T z = (s += 0x9e3779b97f4a7c15);
		z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
		z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
		return z ^ (z >> 31);
	}
};

#undef NAMED_REQ_URBG
