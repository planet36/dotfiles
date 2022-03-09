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
#include <type_traits>

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

/// get the quotient of the _truncated_ floating point division
constexpr auto
trunc_div(const std::floating_point auto x,
          const std::floating_point auto y)
{
	std::common_type_t<decltype(x), decltype(y)> quo;
	std::common_type_t<decltype(x), decltype(y)> rem;
	trunc_div_mod(x, y, quo, rem);
	return quo;
}

/// get the quotient of the _floored_ floating point division
constexpr auto
floor_div(const std::floating_point auto x,
          const std::floating_point auto y)
{
	std::common_type_t<decltype(x), decltype(y)> quo;
	std::common_type_t<decltype(x), decltype(y)> rem;
	floor_div_mod(x, y, quo, rem);
	return quo;
}

/// get the quotient of the _ceiling_ floating point division
constexpr auto
ceil_div(const std::floating_point auto x,
         const std::floating_point auto y)
{
	std::common_type_t<decltype(x), decltype(y)> quo;
	std::common_type_t<decltype(x), decltype(y)> rem;
	ceil_div_mod(x, y, quo, rem);
	return quo;
}

/// get the quotient of the _rounded_ floating point division
constexpr auto
round_div(const std::floating_point auto x,
          const std::floating_point auto y)
{
	std::common_type_t<decltype(x), decltype(y)> quo;
	std::common_type_t<decltype(x), decltype(y)> rem;
	round_div_mod(x, y, quo, rem);
	return quo;
}

/// get the remainder of the _truncated_ floating point division
constexpr auto
trunc_mod(const std::floating_point auto x,
          const std::floating_point auto y)
{
	std::common_type_t<decltype(x), decltype(y)> quo;
	std::common_type_t<decltype(x), decltype(y)> rem;
	trunc_div_mod(x, y, quo, rem);
	return rem;
}

/// get the remainder of the _floored_ floating point division
constexpr auto
floor_mod(const std::floating_point auto x,
          const std::floating_point auto y)
{
	std::common_type_t<decltype(x), decltype(y)> quo;
	std::common_type_t<decltype(x), decltype(y)> rem;
	floor_div_mod(x, y, quo, rem);
	return rem;
}

/// get the remainder of the _ceiling_ floating point division
constexpr auto
ceil_mod(const std::floating_point auto x,
         const std::floating_point auto y)
{
	std::common_type_t<decltype(x), decltype(y)> quo;
	std::common_type_t<decltype(x), decltype(y)> rem;
	ceil_div_mod(x, y, quo, rem);
	return rem;
}

/// get the remainder of the _rounded_ floating point division
constexpr auto
round_mod(const std::floating_point auto x,
          const std::floating_point auto y)
{
	std::common_type_t<decltype(x), decltype(y)> quo;
	std::common_type_t<decltype(x), decltype(y)> rem;
	round_div_mod(x, y, quo, rem);
	return rem;
}

/// get the adjusted remainder of the _truncated_ floating point division
constexpr auto
trunc_amod(const std::floating_point auto x,
           const std::floating_point auto y)
{
	return trunc_mod(x, y) != 0 ? trunc_mod(x, y) : y;
}

/// get the adjusted remainder of the _floored_ floating point division
constexpr auto
floor_amod(const std::floating_point auto x,
           const std::floating_point auto y)
{
	return floor_mod(x, y) != 0 ? floor_mod(x, y) : y;
}

/// get the adjusted remainder of the _ceiling_ floating point division
constexpr auto
ceil_amod(const std::floating_point auto x,
          const std::floating_point auto y)
{
	return ceil_mod(x, y) != 0 ? ceil_mod(x, y) : y;
}

/// get the adjusted remainder of the _rounded_ floating point division
constexpr auto
round_amod(const std::floating_point auto x,
           const std::floating_point auto y)
{
	return round_mod(x, y) != 0 ? round_mod(x, y) : y;
}
