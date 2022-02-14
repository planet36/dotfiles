// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// div function to get quotient and remainder
/**
\file
\author Steven Ward
*/

#pragma once

#include <cmath>
#include <concepts>

/// get the quotient and remainder of the _truncated_ integer division
/**
\note Division by zero is not checked.
\note Overflow is not checked.
*/
constexpr void div(const std::integral auto x,
                   const std::integral auto y,
                   std::integral auto& quot,
                   std::integral auto& rem)
{
	quot = x / y;
	rem = x % y;
}

/// get the quotient and remainder of the _truncated_ division
/**
\note Division by zero is not checked.
\note Overflow is not checked.
*/
constexpr void div(const std::floating_point auto x,
                   const std::floating_point auto y,
                   std::floating_point auto& quot,
                   std::floating_point auto& rem)
{
	quot = x / y;
	rem = x - std::trunc(x / y) * y;
	// fmod is less accurate than division and trunc
	//rem = std::fmod(x, y);
}
