// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// SFC64 (Small Fast Chaotic) PRNG
/**
\file
\author Steven Ward
\sa https://github.com/numpy/numpy/blob/main/numpy/random/src/sfc64/sfc64.h
*/

#pragma once

#include "def_urbg_class_details.hpp"

#include <bit>

struct sfc64
{
	using state_type = std::array<uint64_t, 4>;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(sfc64)
	// XXX: should not give zero seed

	result_type next()
	{
		const result_type result = s[0] + s[1] + s[3]++;

		s[0] = s[1] ^ (s[1] >> 11);
		s[1] = s[2] + (s[2] << 3);
		s[2] = std::rotl(s[2], 24) + result;

		return result;
	}
};
