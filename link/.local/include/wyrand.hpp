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
#include "wyprimes.hpp"

struct wyrand
{
	using state_type = uint64_t;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(wyrand)

	result_type next()
	{
		s += _wyp[0];
		return mum_mix_xor(s, s ^ _wyp[1]);
	}
};
