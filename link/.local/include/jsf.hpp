// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// JSF (Jenkins' Small Fast) PRNG by Bob Jenkins
/**
\file
\author Steven Ward
\sa https://burtleburtle.net/bob/rand/smallprng.html
*/

#pragma once

#include "def_urbg_class_details.hpp"

#include <bit>

// 2-rotate version
struct jsf32_2
{
	using state_type = std::array<uint32_t, 4>;
	using result_type = uint32_t;

DEF_URBG_CLASS_DETAILS(jsf32_2)
	// XXX: must not give zero seed

	result_type next()
	{
		static constexpr unsigned int R1 = 27;
		static constexpr unsigned int R2 = 17;

		const auto e = s[0] - std::rotl(s[1], R1);
		s[0] = s[1] ^ std::rotl(s[2], R2);
		s[1] = s[2] + s[3];
		s[2] = s[3] + e;
		s[3] = e + s[0];
		return s[3];
	}
};

// 3-rotate version
struct jsf32_3
{
	using state_type = std::array<uint32_t, 4>;
	using result_type = uint32_t;

DEF_URBG_CLASS_DETAILS(jsf32_3)
	// XXX: must not give zero seed

	result_type next()
	{
		static constexpr unsigned int R1 = 23;
		static constexpr unsigned int R2 = 16;
		static constexpr unsigned int R3 = 11;

		const auto e = s[0] - std::rotl(s[1], R1);
		s[0] = s[1] ^ std::rotl(s[2], R2);
		s[1] = s[2] + std::rotl(s[3], R3);
		s[2] = s[3] + e;
		s[3] = e + s[0];
		return s[3];
	}
};

struct jsf64
{
	using state_type = std::array<uint64_t, 4>;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(jsf64)
	// XXX: must not give zero seed

	result_type next()
	{
		static constexpr unsigned int R1 = 7;
		static constexpr unsigned int R2 = 13;
		static constexpr unsigned int R3 = 37;

		const auto e = s[0] - std::rotl(s[1], R1);
		s[0] = s[1] ^ std::rotl(s[2], R2);
		s[1] = s[2] + std::rotl(s[3], R3);
		s[2] = s[3] + e;
		s[3] = e + s[0];
		return s[3];
	}
};
