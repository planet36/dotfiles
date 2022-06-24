// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Cast floating-point to integer of sufficient size
/**
\file
\author Steven Ward
*/

#pragma once

#include <cstdint>
#include <limits>

constexpr auto
f_to_i(const float x)
{
	using result_type = int32_t;
	static_assert(std::numeric_limits<decltype(x)>::digits <
	              std::numeric_limits<result_type>::digits);
	static_assert(std::numeric_limits<result_type>::is_signed);
	return static_cast<result_type>(x);
}

constexpr auto
f_to_i(const double x)
{
	using result_type = int64_t;
	static_assert(std::numeric_limits<decltype(x)>::digits <
	              std::numeric_limits<result_type>::digits);
	static_assert(std::numeric_limits<result_type>::is_signed);
	return static_cast<result_type>(x);
}
