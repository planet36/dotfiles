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
#include <utility>

/// get the quotient and remainder of the _truncated_ floating point division
template <std::floating_point T>
constexpr void
trunc_div_mod(const T x, const T y, T& quo, T& rem)
{
	quo = std::trunc(x / y);
	rem = x - quo * y;
	// fmod is less accurate than division and trunc
	//rem = std::fmod(x, y);
}

/// get the quotient and remainder of the _floored_ floating point division
template <std::floating_point T>
constexpr void
floor_div_mod(const T x, const T y, T& quo, T& rem)
{
	quo = std::floor(x / y);
	rem = x - quo * y;
}

/// get the quotient and remainder of the _ceiling_ floating point division
template <std::floating_point T>
constexpr void
ceil_div_mod(const T x, const T y, T& quo, T& rem)
{
	quo = std::ceil(x / y);
	rem = x - quo * y;
}

/// get the quotient and remainder of the _rounded_ floating point division
template <std::floating_point T>
constexpr void
round_div_mod(const T x, const T y, T& quo, T& rem)
{
	quo = std::round(x / y);
	rem = x - quo * y;
}

/// get the quotient and remainder of the _truncated_ division
template <typename T>
constexpr auto
trunc_div_mod(const T x, const T y)
{
	T quo;
	T rem;
	trunc_div_mod(x, y, quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _floored_ division
template <typename T>
constexpr auto
floor_div_mod(const T x, const T y)
{
	T quo;
	T rem;
	floor_div_mod(x, y, quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _ceiling_ division
template <typename T>
constexpr auto
ceil_div_mod(const T x, const T y)
{
	T quo;
	T rem;
	ceil_div_mod(x, y, quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _rounded_ division
template <typename T>
constexpr auto
round_div_mod(const T x, const T y)
{
	T quo;
	T rem;
	round_div_mod(x, y, quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient of the _truncated_ division
template <typename T>
constexpr auto
trunc_div(const T x, const T y)
{
	T quo;
	T rem;
	trunc_div_mod(x, y, quo, rem);
	return quo;
}

/// get the quotient of the _floored_ division
template <typename T>
constexpr auto
floor_div(const T x, const T y)
{
	T quo;
	T rem;
	floor_div_mod(x, y, quo, rem);
	return quo;
}

/// get the quotient of the _ceiling_ division
template <typename T>
constexpr auto
ceil_div(const T x, const T y)
{
	T quo;
	T rem;
	ceil_div_mod(x, y, quo, rem);
	return quo;
}

/// get the quotient of the _rounded_ division
template <typename T>
constexpr auto
round_div(const T x, const T y)
{
	T quo;
	T rem;
	round_div_mod(x, y, quo, rem);
	return quo;
}

/// get the remainder of the _truncated_ division
template <typename T>
constexpr auto
trunc_mod(const T x, const T y)
{
	T quo;
	T rem;
	trunc_div_mod(x, y, quo, rem);
	return rem;
}

/// get the remainder of the _floored_ division
template <typename T>
constexpr auto
floor_mod(const T x, const T y)
{
	T quo;
	T rem;
	floor_div_mod(x, y, quo, rem);
	return rem;
}

/// get the remainder of the _ceiling_ division
template <typename T>
constexpr auto
ceil_mod(const T x, const T y)
{
	T quo;
	T rem;
	ceil_div_mod(x, y, quo, rem);
	return rem;
}

/// get the remainder of the _rounded_ division
template <typename T>
constexpr auto
round_mod(const T x, const T y)
{
	T quo;
	T rem;
	round_div_mod(x, y, quo, rem);
	return rem;
}

/// get the adjusted remainder of the _truncated_ division
template <typename T>
constexpr auto
trunc_amod(const T x, const T y)
{
	return trunc_mod(x, y) == 0 ? y : trunc_mod(x, y);
}

/// get the adjusted remainder of the _floored_ division
template <typename T>
constexpr auto
floor_amod(const T x, const T y)
{
	return floor_mod(x, y) == 0 ? y : floor_mod(x, y);
}

/// get the adjusted remainder of the _ceiling_ division
template <typename T>
constexpr auto
ceil_amod(const T x, const T y)
{
	return ceil_mod(x, y) == 0 ? y : ceil_mod(x, y);
}

/// get the adjusted remainder of the _rounded_ division
template <typename T>
constexpr auto
round_amod(const T x, const T y)
{
	return round_mod(x, y) == 0 ? y : round_mod(x, y);
}
