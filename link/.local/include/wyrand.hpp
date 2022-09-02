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

#include "def_urbg_class_details.hpp"
#include "mum_mix.hpp"

struct wyrand
{
	using state_type = uint64_t;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(wyrand)

	result_type next()
	{
		// large primes with half the bits set (e.g. popcount == 32)
		static constexpr uint64_t p0{0xa0761d6478bd642f};
		static constexpr uint64_t p1{0xe7037ed1a0b428db};

		s += p0;
		return mum_mix_xor(s, s ^ p1);
	}
};
