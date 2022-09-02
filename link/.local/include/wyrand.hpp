// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// WyRand PRNG
/**
\file
\author Steven Ward
\sa https://github.com/lemire/testingRNG/blob/master/source/wyrand.h
\sa https://github.com/wangyi-fudan/wyhash/blob/master/wyhash.h
\sa https://github.com/rurban/smhasher/blob/master/wyhash.h
*/

#pragma once

#include "bytes.hpp"
#include "fill_rand.hpp"
#include "mum_mix.hpp"

#include <array>
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

struct wyrand
{
	using state_type = uint64_t;
	using result_type = uint64_t;
	// https://eel.is/c++draft/rand.req.eng#3.1
	static_assert(sizeof(state_type) % sizeof(result_type) == 0);
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG

private:
	state_type s{};

	// large primes with half the bits set (e.g. popcount == 32)
	static constexpr uint64_t p0{0xa0761d6478bd642f};
	static constexpr uint64_t p1{0xe7037ed1a0b428db};

public:
DEF_CTORS(wyrand)

DEF_SEEDS

	result_type next()
	{
		s += p0;
		return mum_mix_xor(s, s ^ p1);
	}
};

#undef NAMED_REQ_URBG
#undef DEF_CTORS
#undef DEF_SEEDS
#undef DEF_SEEDS_NONZERO
