// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// next less/greater than functions
/**
\file
\author Steven Ward
*/

#pragma once

#include <cmath>
#include <concepts>
#include <limits>

template <std::floating_point T>
constexpr T
next_less(const T x)
{
	return std::nextafter(x, -std::numeric_limits<T>::infinity());
}

template <std::floating_point T>
constexpr T
next_greater(const T x)
{
	return std::nextafter(x, std::numeric_limits<T>::infinity());
}
