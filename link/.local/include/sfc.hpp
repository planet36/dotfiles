// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// SFC (Small Fast Chaotic) PRNG by Chris Doty-Humphrey
/**
\file
\author Steven Ward
\sa https://github.com/numpy/numpy/blob/main/numpy/random/src/sfc64/sfc64.h
\sa https://sourceforge.net/projects/pracrand/files/
*/

#pragma once

#include "def_urbg_class_details.hpp"

#include <bit>

// Adapted from:
// PractRand-pre0.95/src/RNGs/sfc.cpp
struct sfc32
{
	using state_type = std::array<uint32_t, 4>;
	using result_type = uint32_t;

DEF_URBG_CLASS_DETAILS(sfc32)
	// XXX: If a zero seed is given, it takes about 7 iterations for the bits
	// to avalanche.

	result_type next()
	{
		static constexpr unsigned int S1 = 9;
		static constexpr unsigned int S2 = 3;
		static constexpr unsigned int R1 = 21;

		const result_type result = s[0] + s[1] + s[3]++;
		s[0] = s[1] ^ (s[1] >> S1);
		s[1] = s[2] + (s[2] << S2);
		s[2] = std::rotl(s[2], R1) + result;
		return result;
	}
};

struct sfc64
{
	using state_type = std::array<uint64_t, 4>;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(sfc64)
	// XXX: If a zero seed is given, it takes about 10 iterations for the bits
	// to avalanche.

	result_type next()
	{
		static constexpr unsigned int S1 = 11;
		static constexpr unsigned int S2 = 3;
		static constexpr unsigned int R1 = 24;

		const result_type result = s[0] + s[1] + s[3]++;
		s[0] = s[1] ^ (s[1] >> S1);
		s[1] = s[2] + (s[2] << S2);
		s[2] = std::rotl(s[2], R1) + result;
		return result;
	}
};
