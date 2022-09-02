// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// JSF (Jenkins' Small Fast) PRNG
/**
\file
\author Steven Ward
\sa http://burtleburtle.net/bob/rand/smallprng.html
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
		const auto e = s[0] - std::rotl(s[1], 27);
		s[0] = s[1] ^ std::rotl(s[2], 17);
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
		const auto e = s[0] - std::rotl(s[1], 23);
		s[0] = s[1] ^ std::rotl(s[2], 16);
		s[1] = s[2] + std::rotl(s[3], 11);
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
		const auto e = s[0] - std::rotl(s[1], 7);
		s[0] = s[1] ^ std::rotl(s[2], 13);
		s[1] = s[2] + std::rotl(s[3], 37);
		s[2] = s[3] + e;
		s[3] = e + s[0];
		return s[3];
	}
};
