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

#include "def_urbg_class_details.hpp"

struct lehmer64
{
	using state_type = __uint128_t;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(lehmer64)
	// XXX: must not give zero seed

	result_type next()
	{
		s *= 0xda942042e4dd58b5; // not prime
		return s >> 64;
	}
};
