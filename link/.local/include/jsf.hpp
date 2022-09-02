// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// JSF (Jenkins' Small Fast) PRNG
/**
\file
\author Steven Ward
\sa http://burtleburtle.net/bob/rand/smallprng.html
*/

#pragma once

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

// 2-rotate version
struct jsf32_2
{
	using state_type = std::array<uint32_t, 4>;
	using result_type = uint32_t;
	// https://eel.is/c++draft/rand.req.eng#3.1
	static_assert(sizeof(state_type) % sizeof(result_type) == 0);
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG

private:
	state_type s{};

public:
DEF_CTORS(jsf32_2)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto e = s[0] - std::rotl(s[1], 27);
		s[0] = s[1] ^ std::rotl(s[2], 17);
		s[1] = s[2] + s[3];
		s[2] = s[3] + e;
		s[3] = e + s[0];
		return s[3];
	}
};

// 3-rotate version
struct jsf32_3
{
	using state_type = std::array<uint32_t, 4>;
	using result_type = uint32_t;
	// https://eel.is/c++draft/rand.req.eng#3.1
	static_assert(sizeof(state_type) % sizeof(result_type) == 0);
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG

private:
	state_type s{};

public:
DEF_CTORS(jsf32_3)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto e = s[0] - std::rotl(s[1], 23);
		s[0] = s[1] ^ std::rotl(s[2], 16);
		s[1] = s[2] + std::rotl(s[3], 11);
		s[2] = s[3] + e;
		s[3] = e + s[0];
		return s[3];
	}
};

struct jsf64
{
	using state_type = std::array<uint64_t, 4>;
	using result_type = uint64_t;
	// https://eel.is/c++draft/rand.req.eng#3.1
	static_assert(sizeof(state_type) % sizeof(result_type) == 0);
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG

private:
	state_type s{};

public:
DEF_CTORS(jsf64)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto e = s[0] - std::rotl(s[1], 7);
		s[0] = s[1] ^ std::rotl(s[2], 13);
		s[1] = s[2] + std::rotl(s[3], 37);
		s[2] = s[3] + e;
		s[3] = e + s[0];
		return s[3];
	}
};

#undef NAMED_REQ_URBG
#undef DEF_CTORS
#undef DEF_SEEDS
#undef DEF_SEEDS_NONZERO
