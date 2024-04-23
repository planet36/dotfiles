// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Map an unsigned integer to an interval
/**
\file
\author Steven Ward
*/

#pragma once

#include "int_bytes.hpp"

#include <concepts>
#include <limits>

/// map \a x to the inverval <code>[0, s)</code>
/**
\retval x if <code>s == 0</code>
*/
template <std::unsigned_integral T>
constexpr T
map_int(const T x, const T s)
{
	if (s == 0) [[unlikely]]
		// no mapping needed
		return x;

	const auto product = widen(x) * widen(s);
	return static_cast<T>(product >> std::numeric_limits<T>::digits);
}

/// map \a x to the inverval <code>[a, b]</code>
/**
\pre \a a <= \a b
\retval x if <code>a == MIN</code> and <code>b == MAX</code>
*/
template <std::unsigned_integral T>
constexpr T
map_int(const T x, const T a, const T b)
{
	if ((a == std::numeric_limits<T>::min()) && (b == std::numeric_limits<T>::max()))
		// no mapping needed
		return x;

	const T interval_range = b - a + 1;
	const auto product = widen(x) * widen(interval_range);
	return static_cast<T>(product >> std::numeric_limits<T>::digits) + a;
}
