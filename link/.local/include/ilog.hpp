// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// functions to get integral part of logarithm
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/numeric/math/ilogb
\sa https://en.cppreference.com/w/cpp/numeric/math/log2
\sa https://en.cppreference.com/w/cpp/numeric/math/log10
*/

#pragma once

#include <cmath>
#include <limits>
#include <type_traits>

/// return the base-2 logarithm of \a x as a signed integer
template <typename FloatingPointType>
requires std::is_floating_point_v<FloatingPointType>
int ilog2(const FloatingPointType x)
{
	if constexpr (std::numeric_limits<FloatingPointType>::radix == 2)
	{
		return std::ilogb(x);
	}
	else
	{
		return std::floor(std::log2(x));
	}
}

/// return the base-10 logarithm of \a x as a signed integer
template <typename FloatingPointType>
requires std::is_floating_point_v<FloatingPointType>
int ilog10(const FloatingPointType x)
{
	if constexpr (std::numeric_limits<FloatingPointType>::radix == 10)
	{
		return std::ilogb(x);
	}
	else
	{
		return std::floor(std::log10(x));
	}
}
