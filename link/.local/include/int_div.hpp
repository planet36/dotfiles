// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Integer division with floor, ceil, and round results
/**
\file
\author Steven Ward
\note Division by zero is not checked.
\note Overflow is not checked.
*/

#pragma once

#include "sign.hpp"

#include <cmath>
#include <concepts>

constexpr
auto iabs(const std::signed_integral auto x)
{
	return std::abs(x);
}

constexpr
auto iabs(const std::unsigned_integral auto x)
{
	return x;
}

constexpr
auto int_div_floor(const std::integral auto x, const std::integral auto y)
{
	return (x / y) - (!same_sign(x, y) && ((x % y) != 0));
}

constexpr
auto int_div_ceil(const std::integral auto x, const std::integral auto y)
{
	return (x / y) + (same_sign(x, y) && ((x % y) != 0));
}

constexpr
auto int_div_round(const std::integral auto x, const std::integral auto y)
{
	return (x / y) + sign(x % y) * sign(y) * (
	           (iabs(x % y) > iabs(y / 2)) ||
	           ((iabs(x % y) == iabs(y / 2)) && ((y % 2) == 0))
	       );
}
