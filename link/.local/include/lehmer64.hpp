// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Lehmer PRNG
/**
\file
\author Steven Ward
\sa https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/
\sa https://github.com/lemire/testingRNG/blob/master/source/lehmer64.h
*/

#pragma once

#if !defined(__SIZEOF_INT128__)
#error "__SIZEOF_INT128__ not defined"
#endif

#include "bytes.hpp"
#include "fill_rand.hpp"

#include <array>
#include <bit>
#include <limits>

// https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator
#define NAMED_REQ_URBG                                  \
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

#define DEF_CTORS(CLASS_NAME) \
	CLASS_NAME() { seed(); } \
	CLASS_NAME(const state_type& new_s) { seed(new_s); } \
	CLASS_NAME(const seed_bytes_type& bytes) { seed(bytes); }

#define DEF_SEEDS \
	void seed() { fill_rand(s); } \
	void seed(const state_type& new_s) { s = new_s; } \
	void seed(const seed_bytes_type& bytes) { s = bytes_to_datum<state_type>(bytes); }

#define DEF_SEEDS_NONZERO \
	void seed() { fill_rand(s); while (s == state_type{}) [[unlikely]] { fill_rand(s); } } \
	void seed(const state_type& new_s) { s = new_s; } \
	void seed(const seed_bytes_type& bytes) { s = bytes_to_datum<state_type>(bytes); }

struct lehmer64
{
	using state_type = __uint128_t;
	using result_type = uint64_t;
	// https://eel.is/c++draft/rand.req.eng#3.1
	static_assert(sizeof(state_type) % sizeof(result_type) == 0);
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG

private:
	state_type s{};

public:
DEF_CTORS(lehmer64)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		s *= 0xda942042e4dd58b5; // not prime
		return s >> 64;
	}
};

#undef NAMED_REQ_URBG
#undef DEF_CTORS
#undef DEF_SEEDS
#undef DEF_SEEDS_NONZERO
