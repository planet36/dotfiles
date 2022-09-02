// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Macro that defines some details of a Uniform Random Bit Generator class
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator
\sa https://en.cppreference.com/w/cpp/named_req/RandomNumberEngine
\sa https://eel.is/c++draft/rand.req.urng
\sa https://eel.is/c++draft/rand.req.eng
Note: This does not meet the requirements of a random number engine.
The default ctor does not create an engine with the same initial state as all
other default-constructed engines of the same type.
*/

#pragma once

#include "bytes.hpp"
#include "fill_rand.hpp"

#include <array>
#include <cstdint>
#include <limits>
#include <type_traits>

#if not defined(DEF_URBG_CLASS_DETAILS)

// XXX: state_type and result_type must be declared before invoking this.

#define DEF_URBG_CLASS_DETAILS(CLASS_NAME)                           \
private:                                                             \
	state_type s{};                                                  \
public:                                                              \
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>; \
	/* https://eel.is/c++draft/rand.req.urng */                      \
	static_assert(std::is_unsigned_v<result_type>);                  \
	static constexpr result_type min()                               \
	{ return std::numeric_limits<result_type>::min(); }              \
	static constexpr result_type max()                               \
	{ return std::numeric_limits<result_type>::max(); }              \
	result_type operator()() { return next(); }                      \
	/* https://eel.is/c++draft/rand.req.eng#3.1 */                   \
	static_assert(sizeof(state_type) % sizeof(result_type) == 0);    \
	/* ctors */                                                      \
	CLASS_NAME() { seed(); }                                         \
	CLASS_NAME(const state_type& new_s) { seed(new_s); }             \
	CLASS_NAME(const seed_bytes_type& bytes) { seed(bytes); }        \
	/* seed functions */                                             \
	void seed() { fill_rand(s); }                                    \
	void seed(const state_type& new_s) { s = new_s; }                \
	void seed(const seed_bytes_type& bytes)                          \
	{ s = bytes_to_datum<state_type>(bytes); }                       \
	/* equality operators */                                         \
	bool operator==(const CLASS_NAME& that) const                    \
	{ return this->s == that.s; }                                    \
	bool operator!=(const CLASS_NAME& that) const                    \
	{ return this->s != that.s; }

#endif
