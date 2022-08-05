// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Join smaller unsigned ints into larger unsigned ints
/**
\file
\author Steven Ward
*/

#pragma once

static_assert(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__);

#include "int_parts_union.hpp"

#include <concepts>
#include <cstdint>

#if 0
constexpr uint16_t
int_join(const uint8_t hi, const uint8_t lo)
{
	const union
	{
		uint16_t whole;
		uint8_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	static_assert(sizeof(u.whole) == sizeof(u.parts));
}

constexpr uint32_t
int_join(const uint16_t hi, const uint16_t lo)
{
	const union
	{
		uint32_t whole;
		uint16_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	static_assert(sizeof(u.whole) == sizeof(u.parts));
}

constexpr uint64_t
int_join(const uint32_t hi, const uint32_t lo)
{
	const union
	{
		uint64_t whole;
		uint32_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	static_assert(sizeof(u.whole) == sizeof(u.parts));
}

#if defined(__SIZEOF_INT128__)
// https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html
constexpr __uint128_t
int_join(const uint64_t hi, const uint64_t lo)
{
	const union
	{
		__uint128_t whole;
		uint64_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	static_assert(sizeof(u.whole) == sizeof(u.parts));
}
#endif

#else

template <std::unsigned_integral T>
constexpr auto
int_join(const T hi, const T lo)
{
#if 1
	return int_parts<T>{.parts = {lo, hi}}.whole;
#else
	using result_type = uint_bytes<sizeof(T) * 2>;

	const union
	{
		result_type whole;
		T parts[2];
	} u = {.parts = {lo, hi}};

	return u.whole;
	static_assert(sizeof(u.whole) == sizeof(u.parts));
#endif
}

#endif
