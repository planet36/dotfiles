// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// splitmix64 PRNG
/**
\file
\author Steven Ward
\sa http://hg.openjdk.java.net/jdk8/jdk8/jdk/file/tip/src/share/classes/java/util/SplittableRandom.java
\sa https://gee.cs.oswego.edu/dl/papers/oopsla14.pdf
*/

#pragma once

#include "def_urbg_class_details.hpp"
#include "gamma.hpp"

struct splitmix64
{
	using state_type = uint64_t;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(splitmix64)

	result_type next()
	{
		static constexpr uint64_t inc = gamma64;
		static_assert(inc & 1, "must be odd");

		static constexpr uint64_t M1 = 0xbf58476d1ce4e5b9; // not prime (popcount = 36)
		static constexpr uint64_t M2 = 0x94d049bb133111eb; // not prime (popcount = 29)
		static constexpr unsigned int S1 = 30;
		static constexpr unsigned int S2 = 27;
		static constexpr unsigned int S3 = 31;
		static_assert(M1 & 1, "must be odd");
		static_assert(M2 & 1, "must be odd");

		auto x = (s += inc);

		x ^= x >> S1;
		x *= M1;
		x ^= x >> S2;
		x *= M2;
		x ^= x >> S3;
		return x;
	}
};
