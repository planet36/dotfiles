// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Romu PRNG
/**
\file
\author Steven Ward
\sa https://www.romu-random.org/code.c
*/

#include "def_urbg_class_details.hpp"

struct romu_quad
{
	using state_type = std::array<uint64_t, 4>;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(romu_quad)

	result_type next()
	{
		static constexpr uint64_t M1 = 0xd3833e804f4c574b; // not prime (popcount = 31)
		static_assert(M1 & 1, "must be odd");
		static constexpr unsigned int R1 = 52;
		static constexpr unsigned int R2 = 19;

		s[0]++; // (SDW)
		const auto old_s = s;

		s[0] = M1 * old_s[3];                      // a-mult
		s[1] = old_s[3] + std::rotl(old_s[0], R1); // b-rotl, c-add
		s[2] = old_s[2] - old_s[1];                // d-sub
		s[3] = std::rotl(old_s[2] + old_s[0], R2); // e-add, f-rotl (SDW)
		return old_s[1];
	}
};

struct romu_trio
{
	using state_type = std::array<uint64_t, 3>;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(romu_trio)

	result_type next()
	{
		static constexpr uint64_t M1 = 0xd3833e804f4c574b; // not prime (popcount = 31)
		static_assert(M1 & 1, "must be odd");
		static constexpr unsigned int R1 = 12;
		static constexpr unsigned int R2 = 44;

		s[0]++; // (SDW)
		const auto old_s = s;

		s[0] = M1 * old_s[2];
		s[1] = std::rotl(old_s[1] - old_s[0], R1); // (SDW)
		s[2] = std::rotl(old_s[2] - old_s[1], R2); // (SDW)
		return old_s[0];
	}
};

struct romu_duo
{
	using state_type = std::array<uint64_t, 2>;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(romu_duo)

	result_type next()
	{
		static constexpr uint64_t M1 = 0xd3833e804f4c574b; // not prime (popcount = 31)
		static_assert(M1 & 1, "must be odd");
		static constexpr unsigned int R1 = 36;
		static constexpr unsigned int R2 = 15;

		s[0]++; // (SDW)
		const auto old_s = s;

		s[0] = M1 * old_s[1];
		s[1] = std::rotl(old_s[1], R1) + std::rotl(old_s[1], R2) - old_s[0]; // (SDW)
		return old_s[0];
	}
};

struct romu_duo_jr
{
	using state_type = std::array<uint64_t, 2>;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(romu_duo_jr)

	result_type next()
	{
		static constexpr uint64_t M1 = 0xd3833e804f4c574b; // not prime (popcount = 31)
		static_assert(M1 & 1, "must be odd");
		static constexpr unsigned int R1 = 27;

		s[0]++; // (SDW)
		const auto old_s = s;

		s[0] = M1 * old_s[1];
		s[1] = std::rotl(old_s[1] - old_s[0], R1); // (SDW)
		return old_s[0];
	}
};
