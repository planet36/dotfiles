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
\li \c 1, if <code>x > 0</code>
\li \c -1, if <code>x < 0</code>
\li \c 0, otherwise

For a floating point \c x, <code>sign(x)</code> returns
\li \c 1, if <code>x > 0</code>
\li \c -1, if <code>x < 0</code>
\li \c 0, otherwise (including \c NaN)

Two numbers have the same sign if both are non-positive or non-negative.
*/

#pragma once

#include <concepts>
#include <type_traits>

constexpr int sign(const std::unsigned_integral auto x)
{
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

constexpr int sign(const std::signed_integral auto x)
{
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

#if 0
template <std::floating_point T>
constexpr T sign(const T x)
#else
constexpr int sign(const std::floating_point auto x)
#endif
{
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

constexpr bool same_sign([[maybe_unused]] const std::unsigned_integral auto x,
                         [[maybe_unused]] const std::unsigned_integral auto y)
{
	return true;
}

constexpr bool same_sign(const std::unsigned_integral auto x,
                         const std::signed_integral auto y)
{
	return ((x == 0) && (y <= 0)) || (y >= 0);
}

constexpr bool same_sign(const std::signed_integral auto x,
                         const std::unsigned_integral auto y)
{
	return ((x <= 0) && (y == 0)) || (x >= 0);
}

constexpr bool same_sign(const std::signed_integral auto x,
                         const std::signed_integral auto y)
{
	return ((x <= 0) && (y <= 0)) || ((x >= 0) && (y >= 0));
}

constexpr bool same_sign(const std::floating_point auto x,
                         const std::floating_point auto y)
{
	return ((x <= 0) && (y <= 0)) || ((x >= 0) && (y >= 0));
}
