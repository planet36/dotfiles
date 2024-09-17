// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Join smaller unsigned ints into larger unsigned ints
/**
\file
\author Steven Ward
*/

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

_Static_assert(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__);

uint16_t
int_join_u8(const uint8_t hi, const uint8_t lo)
{
	const union
	{
		uint16_t whole;
		uint8_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	_Static_assert(sizeof(u.whole) == sizeof(u.parts));
}

uint32_t
int_join_u16(const uint16_t hi, const uint16_t lo)
{
	const union
	{
		uint32_t whole;
		uint16_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	_Static_assert(sizeof(u.whole) == sizeof(u.parts));
}

uint64_t
int_join_u32(const uint32_t hi, const uint32_t lo)
{
	const union
	{
		uint64_t whole;
		uint32_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	_Static_assert(sizeof(u.whole) == sizeof(u.parts));
}

#if defined(__SIZEOF_INT128__)
// https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html
__uint128_t
int_join_u64(const uint64_t hi, const uint64_t lo)
{
	const union
	{
		__uint128_t whole;
		uint64_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	_Static_assert(sizeof(u.whole) == sizeof(u.parts));
}
#endif

#ifdef __cplusplus
} // extern "C"
#endif
