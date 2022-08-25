// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// SFC64 (Small Fast Chaotic) PRNG
/**
\file
\author Steven Ward
\sa https://github.com/numpy/numpy/blob/main/numpy/random/src/sfc64/sfc64.h
*/

#pragma once

#include "bytes.hpp"
#include "fill_rand.hpp"

#include <array>
#include <bit>
#include <limits>

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

struct sfc64
{
	using state_type = std::array<uint64_t, 4>;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(uint64_t)

private:
	state_type s{};

public:
DEF_CTORS(sfc64)

	// XXX: should not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const result_type result = s[0] + s[1] + s[3]++;

		s[0] = s[1] ^ (s[1] >> 11);
		s[1] = s[2] + (s[2] << 3);
		s[2] = std::rotl(s[2], 24) + result;

		return result;
	}
};

#undef NAMED_REQ_URBG
#undef DEF_CTORS
#undef DEF_SEEDS
#undef DEF_SEEDS_NONZERO
