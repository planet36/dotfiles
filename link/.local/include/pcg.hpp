// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// PCG PRNG
/**
\file
\author Steven Ward
\sa https://www.pcg-random.org/
*/

#pragma once

#include "def_urbg_class_details.hpp"

#if defined(__SIZEOF_INT128__)
#include "int_join.hpp"
#endif

#include <bit>

/*
* Multiplier and increment values taken from here:
* https://github.com/imneme/pcg-cpp/blob/master/include/pcg_random.hpp#L158
* https://github.com/imneme/pcg-cpp/blob/master/include/pcg_random.hpp#L161
*/

/// PCG-XSH-RR
struct pcg32
{
	using state_type = uint64_t;
	using result_type = uint32_t;

	DEF_URBG_CLASS_DETAILS(pcg32)

	result_type next()
	{
		static constexpr state_type mul = UINT64_C(6364136223846793005); // not prime
		static constexpr state_type inc = UINT64_C(1442695040888963407); // not prime
		static_assert((inc & 1) != 0, "must be odd");

		const auto old_s = s;
		s = s * mul + inc;

		// (5 + 32) / 2 == 18
		// 32 - 5 == 27
		// 64 - 5 == 59
		const result_type output = (old_s ^ (old_s >> 18)) >> 27;
		const int rot = old_s >> 59;
		return std::rotr(output, rot);
	}
};

/// PCG-XSH-RS
struct pcg32_fast
{
	using state_type = uint64_t;
	using result_type = uint32_t;

	DEF_URBG_CLASS_DETAILS(pcg32_fast)

	result_type next()
	{
		static constexpr state_type mul = UINT64_C(6364136223846793005); // not prime
		static constexpr state_type inc = UINT64_C(1442695040888963407); // not prime
		static_assert((inc & 1) != 0, "must be odd");

		const auto old_s = s;
		s = s * mul + inc;

		// 32 - 3 - 7 == 22
		// 64 - 3 == 61
		const result_type output = (old_s ^ (old_s >> 22)) >> (22 + (old_s >> 61));
		return output;
	}
};

#if defined(__SIZEOF_INT128__)
/// PCG-XSL-RR
struct pcg64
{
	using state_type = __uint128_t;
	using result_type = uint64_t;

	DEF_URBG_CLASS_DETAILS(pcg64)

	result_type next()
	{
		/* "There is no support in GCC for expressing an integer constant of
		*  type __int128 for targets with long long integer less than 128 bits
		*  wide."
		*  https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html
		*/
		static constexpr __uint128_t mul = int_join(
		    UINT64_C(2549297995355413924),
		    UINT64_C(4865540595714422341)); // not prime
		static constexpr __uint128_t inc = int_join(
		    UINT64_C(6364136223846793005),
		    UINT64_C(1442695040888963407)); // not prime
		static_assert((inc & 1) != 0, "must be odd");

		const auto old_s = s;
		s = s * mul + inc;

		// 128 / 2 == 64
		// 128 - 6 == 122
		const result_type output = old_s ^ (old_s >> 64);
		const int rot = old_s >> 122;
		return std::rotr(output, rot);
	}
};

/// PCG-DXSM
/**
* Adapted from
* https://github.com/numpy/numpy/issues/13635#issuecomment-506088698
* https://github.com/imneme/pcg-cpp/blob/master/include/pcg_random.hpp#L1031
* https://dotat.at/@/2023-06-21-pcg64-dxsm.html
* https://dotat.at/cgi/git/pcg-dxsm.git/blob/HEAD:/pcg64_dxsm.h
* https://github.com/imneme/pcg-cpp/commit/871d0494ee9c9a7b7c43f753e3d8ca47c26f8005
*/
struct pcg64dxsm
{
	using state_type = __uint128_t;
	using result_type = uint64_t;

	DEF_URBG_CLASS_DETAILS(pcg64dxsm)

	result_type next()
	{
		// "cheap multiplier"
		static constexpr uint64_t mul = 0xda942042e4dd58b5; // not prime (popcount = 29)
		static_assert((mul & 1) != 0, "must be odd");
		static constexpr __uint128_t inc = int_join(
		    UINT64_C(6364136223846793005),
		    UINT64_C(1442695040888963407)); // not prime
		static_assert((inc & 1) != 0, "must be odd");

		const auto old_s = s;
		s = s * mul + inc;

		uint64_t hi = static_cast<uint64_t>(old_s >> 64);
		const uint64_t lo = static_cast<uint64_t>(old_s | 1);

		hi ^= hi >> 32; // 64 / 2 == 32
		hi *= mul;
		hi ^= hi >> 48; // 3 * (64 / 4) == 48
		hi *= lo;

		return hi;
	}
};
#endif
