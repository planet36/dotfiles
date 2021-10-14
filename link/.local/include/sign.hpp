// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Sign functions
/**
\file
\author Steven Ward

This is also called "signum" or "sgn".
\sa https://en.wikipedia.org/wiki/Sign_function
\sa https://mathworld.wolfram.com/Sign.html
\sa https://reference.wolfram.com/language/ref/Sign.html

For an integer \c x, <code>sign(x)</code> returns
\li \c -1 if <code>x < 0</code>
\li \c 0 if <code>x == 0</code>
\li \c 1 if <code>x > 0</code>

For a floating point \c x, <code>sign(x)</code> returns
\li \c -1 if <code>x < 0</code>
\li \c 0 if <code>x == 0</code>
\li \c 1 if <code>x > 0</code>
\li \c NaN if <code>x is NaN</code>

Two numbers have the same sign if both are non-positive or non-negative.
*/

#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>

int sign(const std::unsigned_integral auto x)
{
	return x > 0;
}

int sign(const std::signed_integral auto x)
{
	return (x > 0) - (x < 0);
}

#if 1
template <std::floating_point T>
T sign(const T x)
{
	if (std::isnan(x))
		return x;

	if (x == 0)
		return x;

	return (x > 0) - (x < 0);
}
#else
auto sign(const std::floating_point auto x) -> decltype(x)
{
	if (std::isnan(x))
		return x;

	if (x == 0)
		return x;

	return (x > 0) - (x < 0);
}
#endif

bool same_sign([[gnu::unused]] const std::unsigned_integral auto x,
               [[gnu::unused]] const std::unsigned_integral auto y)
{
	return true;
}

bool same_sign(const std::unsigned_integral auto x,
               const std::signed_integral auto y)
{
	return ((x == 0) && (y <= 0)) || (y >= 0);
}

bool same_sign(const std::signed_integral auto x,
               const std::unsigned_integral auto y)
{
	return ((x <= 0) && (y == 0)) || (x >= 0);
}

bool same_sign(const std::signed_integral auto x,
               const std::signed_integral auto y)
{
	return ((x <= 0) && (y <= 0)) || ((x >= 0) && (y >= 0));
}

bool same_sign(const std::floating_point auto x,
               const std::floating_point auto y)
{
	return ((x <= 0) && (y <= 0)) || ((x >= 0) && (y >= 0));
}