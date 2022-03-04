// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Division and remainder (mod) functions using various rounding methods
/**
\file
\author Steven Ward
\note Division by zero is not checked.
\note Overflow is not checked.
*/

#pragma once

#include <cmath>
#include <concepts>

/// get the quotient and remainder of the _truncated_ floating point division
constexpr void
trunc_div_mod(const std::floating_point auto x,
              const std::floating_point auto y,
              std::floating_point auto& quo,
              std::floating_point auto& rem)
{
	quo = std::trunc(x / y);
	rem = x - quo * y;
	// fmod is less accurate than division and trunc
	//rem = std::fmod(x, y);
}

/// get the quotient and remainder of the _floored_ floating point division
constexpr void
floor_div_mod(const std::floating_point auto x,
              const std::floating_point auto y,
              std::floating_point auto& quo,
              std::floating_point auto& rem)
{
	quo = std::floor(x / y);
	rem = x - quo * y;
}

/// get the quotient and remainder of the _ceiling_ floating point division
constexpr void
ceil_div_mod(const std::floating_point auto x,
             const std::floating_point auto y,
             std::floating_point auto& quo,
             std::floating_point auto& rem)
{
	quo = std::ceil(x / y);
	rem = x - quo * y;
}

/// get the quotient and remainder of the _rounded_ floating point division
constexpr void
round_div_mod(const std::floating_point auto x,
              const std::floating_point auto y,
              std::floating_point auto& quo,
              std::floating_point auto& rem)
{
	quo = std::round(x / y);
	rem = x - quo * y;
}