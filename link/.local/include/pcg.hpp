// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// PCG PRNG
/**
\file
\author Steven Ward
\sa https://www.pcg-random.org/
*/

#pragma once

#include <bit>
#include <limits>

#include "bytes.hpp"
#include "fill_rand.hpp"
#include "int_join.hpp"

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

/*
* Multiplier and increment values taken from here:
* https://github.com/imneme/pcg-cpp/blob/master/include/pcg_random.hpp#L158
* https://github.com/imneme/pcg-cpp/blob/master/include/pcg_random.hpp#L161
*/

/// PCG-XSH-RR
struct pcg32
{
	using state_type = uint64_t;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(uint32_t)

private:
	state_type s{};
	static constexpr uint64_t multiplier = UINT64_C(6364136223846793005); // not prime
	static constexpr uint64_t increment = UINT64_C(1442695040888963407); // not prime
	static_assert(increment & 1U); // must be odd

public:
DEF_CTORS(pcg32)

DEF_SEEDS

	result_type next()
	{
		const auto old_s = s;
		s = s * multiplier + increment;

		// (5 + 32) / 2 == 18
		// 32 - 5 == 27
		// 64 - 5 == 59
		const result_type output = (old_s ^ (old_s >> 18)) >> 27;
		const unsigned int rot = old_s >> 59;
		return std::rotr(output, rot);
	}
};

/// PCG-XSH-RS
struct pcg32_fast
{
	using state_type = uint64_t;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(uint32_t)

private:
	state_type s{};
	static constexpr uint64_t multiplier = UINT64_C(6364136223846793005); // not prime
	static constexpr uint64_t increment = UINT64_C(1442695040888963407); // not prime
	static_assert(increment & 1U); // must be odd

public:
DEF_CTORS(pcg32_fast)

DEF_SEEDS

	result_type next()
	{
		const auto old_s = s;
		s = s * multiplier + increment;

		// 32 - 3 - 7 == 22
		// 64 - 3 == 61
		const result_type output = (old_s ^ (old_s >> 22)) >> (22 + (old_s >> 61));
		return output;
	}
};

#if defined(__SIZEOF_INT128__)
/// PCG-XSL-RR
struct pcg64
{
	using state_type = __uint128_t;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(uint64_t)

private:
	state_type s{};
	/* "There is no support in GCC for expressing an integer constant of type
	*  __int128 for targets with long long integer less than 128 bits wide."
	*  https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html
	*/
	static constexpr __uint128_t multiplier = int_join(UINT64_C(2549297995355413924), UINT64_C(4865540595714422341));
	static constexpr __uint128_t increment = int_join(UINT64_C(6364136223846793005), UINT64_C(1442695040888963407));
	static_assert(increment & 1U); // must be odd

public:
DEF_CTORS(pcg64)

DEF_SEEDS

	result_type next()
	{
		const auto old_s = s;
		s = s * multiplier + increment;

		// 128 / 2 == 64
		// 128 - 6 == 122
		const result_type output = old_s ^ (old_s >> 64);
		const unsigned int rot = old_s >> 122;
		return std::rotr(output, rot);
	}
};

#endif

#undef NAMED_REQ_URBG
#undef DEF_CTORS
#undef DEF_SEEDS
#undef DEF_SEEDS_NONZERO
