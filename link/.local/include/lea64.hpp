// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// lea64 PRNG
/**
\file
\author Steven Ward
\sa https://mostlymangling.blogspot.com/2021/11/applying-rrc-64-test-to-degski64-and.html
*/

#pragma once

#include "def_urbg_class_details.hpp"
#include "scaled-const.hpp"

struct lea64
{
	using state_type = uint64_t;
	using result_type = uint64_t;

	DEF_URBG_CLASS_DETAILS(lea64)

	result_type next()
	{
		static constexpr uint64_t inc = GoldenRatio_64;
		static_assert((inc & 1) != 0, "must be odd");

		static constexpr uint64_t M1 = 0xdaba0b6eb09322e3; // not prime (popcount = 32)
		static constexpr uint64_t M2 = 0xdaba0b6eb09322e3; // not prime (popcount = 32)
		static constexpr unsigned int S1 = 32;
		static constexpr unsigned int S2 = 32;
		static constexpr unsigned int S3 = 32;
		static_assert((M1 & 1) != 0, "must be odd");
		static_assert((M2 & 1) != 0, "must be odd");

		auto x = (s += inc);

		x ^= x >> S1;
		x *= M1;
		x ^= x >> S2;
		x *= M2;
		x ^= x >> S3;
		return x;
	}
};
