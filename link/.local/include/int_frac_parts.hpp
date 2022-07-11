// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get the integer part and fractional part of a floating-point number
/**
\file
\author Steven Ward
*/

#pragma once

#include <cmath>
#include <concepts>

/// get the integer part of a floating-point number
template <std::floating_point T>
constexpr T
int_part(const T x)
{
	T i{};
	(void)std::modf(x, &i);
	return i;
}

/// get the fractional part of a floating-pointing point number
template <std::floating_point T>
constexpr T
frac_part(const T x)
{
	T i{};
	return std::modf(x, &i);
}

/// get the integer and fractional parts of a floating-point number
template <std::floating_point T>
constexpr void
int_frac_parts(const T x, T& i, T& f)
{
	f = std::modf(x, &i);
}
