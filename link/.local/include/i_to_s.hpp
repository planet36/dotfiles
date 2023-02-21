// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// int-to-string wrapper function for std::to_chars
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/utility/to_chars
*/

#pragma once

#include <charconv>
#include <climits>
#include <concepts>
#include <limits>
#include <string>

/**
\pre \a base must be within the interval [2, 36]
*/
std::string
i_to_s(const std::integral auto x, const int base = 10)
{
	// x=-9223372036854775808  base=2  size=65  result="-1000000000000000000000000000000000000000000000000000000000000000"
	// x=18446744073709551615  base=2  size=64  result="1111111111111111111111111111111111111111111111111111111111111111"

	// For signed integer types, std::numeric_limits<decltype(x)>::digits is
	// CHAR_BIT * sizeof(x) - 1
	// We don't want to subtract 1, so we use CHAR_BIT * sizeof(x)
	constexpr unsigned int buf_size =
	    CHAR_BIT * sizeof(x) + std::numeric_limits<decltype(x)>::is_signed;

	char buf[buf_size] = {'\0'};
	const std::to_chars_result r = std::to_chars(buf, buf + buf_size, x, base);
	return std::string(buf, r.ptr);
}
