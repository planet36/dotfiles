// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Join smaller unsigned ints into larger unsigned ints
/**
\file
\author Steven Ward
*/

#pragma once

#include <stdint.h>

uint16_t int8_join(const uint8_t hi, const uint8_t lo)
{
	const union {
		uint16_t whole;
		uint8_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	_Static_assert(sizeof (u.whole) == sizeof (u.parts));
}

uint32_t int16_join(const uint16_t hi, const uint16_t lo)
{
	const union {
		uint32_t whole;
		uint16_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	_Static_assert(sizeof (u.whole) == sizeof (u.parts));
}

uint64_t int32_join(const uint32_t hi, const uint32_t lo)
{
	const union {
		uint64_t whole;
		uint32_t parts[2];
	} u = {.parts = {lo, hi}};
	return u.whole;
	_Static_assert(sizeof (u.whole) == sizeof (u.parts));
}
