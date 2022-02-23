// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Integer division with floor, ceil, and round results
/**
\file
\author Steven Ward
*/

#pragma once

#include "sign.hpp"

#include <cmath>
#include <concepts>

constexpr auto iabs(const std::signed_integral auto x)
{
	return std::abs(x);
}

constexpr auto iabs(const std::unsigned_integral auto x)
{
	return x;
}

/// get the quotient and remainder of the _floored_ integer division
/**
\note Division by zero is not checked.
\note Overflow is not checked.
*/
constexpr void floor_div_mod(const std::signed_integral auto x,
                                const std::signed_integral auto y,
                                std::signed_integral auto& quo,
                                std::signed_integral auto& rem)
{
#if 0
	quo = floor_div(x, y);
	rem = x - y * quo;
#else
	quo = x / y;
	rem = x % y;
	if (y < 0)
	{
		if (rem > 0)
		{
			rem += y;
			quo--;
		}
	}
	else
	{
		if (rem < 0)
		{
			rem += y;
			quo--;
		}
	}
#endif
}

/// get the quotient and remainder of the _ceiling_ integer division
/**
\note Division by zero is not checked.
\note Overflow is not checked.
*/
constexpr void ceil_div_mod(const std::signed_integral auto x,
                               const std::signed_integral auto y,
                               std::signed_integral auto& quo,
                               std::signed_integral auto& rem)
{
#if 0
	quo = ceil_div(x, y);
	rem = x - y * quo;
#else
	quo = x / y;
	rem = x % y;
	if (y > 0)
	{
		if (rem > 0)
		{
			rem -= y;
			quo++;
		}
	}
	else
	{
		if (rem < 0)
		{
			rem -= y;
			quo++;
		}
	}
#endif
}

/// get the quotient and remainder of the _rounded_ integer division
/**
\note Division by zero is not checked.
\note Overflow is not checked.
*/
constexpr void round_div_mod(const std::signed_integral auto x,
                                const std::signed_integral auto y,
                                std::signed_integral auto& quo,
                                std::signed_integral auto& rem)
{
#if 0
	quo = round_div(x, y);
	rem = x - y * quo;
#else
	quo = x / y;
	rem = x % y;

	if (y < 0)
	{
		if (rem < 0)
		{
			if ((rem < (y / 2)) || ((rem == (y / 2)) && ((y % 2) == 0)))
			{
				rem -= y;
				quo++;
			}
		}
		else if (rem > 0)
		{
			if ((-rem < (y / 2)) || ((-rem == (y / 2)) && ((y % 2) == 0)))
			{
				rem += y;
				quo--;
			}
		}
	}
	else
	{
		if (rem < 0)
		{
			if ((-rem > (y / 2)) || ((-rem == (y / 2)) && ((y % 2) == 0)))
			{
				rem += y;
				quo--;
			}
		}
		else if (rem > 0)
		{
			if ((rem > (y / 2)) || ((rem == (y / 2)) && ((y % 2) == 0)))
			{
				rem -= y;
				quo++;
			}
		}
	}
#endif
}

/// get the quotient of the _floored_ integer division
/**
\note Division by zero is not checked.
\note Overflow is not checked.
*/
constexpr auto floor_div(const std::signed_integral auto x,
                             const std::signed_integral auto y)
{
	return (x / y) - (!same_sign(x, y) && ((x % y) != 0));
}

/// get the quotient of the _ceiling_ integer division
/**
\note Division by zero is not checked.
\note Overflow is not checked.
*/
constexpr auto ceil_div(const std::signed_integral auto x,
                            const std::signed_integral auto y)
{
	return (x / y) + (same_sign(x, y) && ((x % y) != 0));
}

/// get the quotient of the _rounded_ integer division
/**
\note Division by zero is not checked.
\note Overflow is not checked.
*/
constexpr auto round_div(const std::signed_integral auto x,
                             const std::signed_integral auto y)
{
	return (x / y) + sign(x % y) * sign(y) * (
	           (iabs(x % y) > iabs(y / 2)) ||
	           ((iabs(x % y) == iabs(y / 2)) && ((y % 2) == 0))
	       );
}
