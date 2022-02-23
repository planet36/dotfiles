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

#include "sign.hpp"

#include <cmath>
#include <concepts>

/// get the quotient and remainder of the _truncated_ integer division
constexpr void trunc_div_mod(const std::integral auto x,
                   const std::integral auto y,
                   std::integral auto& quo,
                   std::integral auto& rem)
{
	quo = x / y;
	rem = x % y;
}

/// get the quotient and remainder of the _truncated_ division
constexpr void trunc_div_mod(const std::floating_point auto x,
                   const std::floating_point auto y,
                   std::floating_point auto& quo,
                   std::floating_point auto& rem)
{
	quo = x / y;
	rem = x - std::trunc(x / y) * y;
	// fmod is less accurate than division and trunc
	//rem = std::fmod(x, y);
}

constexpr auto iabs(const std::signed_integral auto x)
{
	return std::abs(x);
}

constexpr auto iabs(const std::unsigned_integral auto x)
{
	return x;
}

/// get the quotient and remainder of the _floored_ integer division
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
constexpr auto floor_div(const std::signed_integral auto x,
                             const std::signed_integral auto y)
{
	return (x / y) - (!same_sign(x, y) && ((x % y) != 0));
}

/// get the quotient of the _ceiling_ integer division
constexpr auto ceil_div(const std::signed_integral auto x,
                            const std::signed_integral auto y)
{
	return (x / y) + (same_sign(x, y) && ((x % y) != 0));
}

/// get the quotient of the _rounded_ integer division
constexpr auto round_div(const std::signed_integral auto x,
                             const std::signed_integral auto y)
{
	return (x / y) + sign(x % y) * sign(y) * (
	           (iabs(x % y) > iabs(y / 2)) ||
	           ((iabs(x % y) == iabs(y / 2)) && ((y % 2) == 0))
	       );
}

/// get the remainder of the _floored_ integer division
/**
\sa http://python-history.blogspot.com/2010/08/why-pythons-integer-division-floors.html
\sa https://eel.is/c++draft/expr.mul#4
\sa https://stackoverflow.com/a/3602857
\sa https://reference.wolfram.com/language/ref/Quotient.html
\sa https://www.wolframalpha.com/input?i=Quotient%5B9%2C+5%5D%2C+Quotient%5B-9%2C+5%5D%2C+Quotient%5B9%2C+-5%5D%2C+Quotient%5B-9%2C+-5%5D
\sa https://reference.wolfram.com/language/ref/Mod.html
\sa https://www.wolframalpha.com/input?i=Mod%5B9%2C+5%5D%2C+Mod%5B-9%2C+5%5D%2C+Mod%5B9%2C+-5%5D%2C+Mod%5B-9%2C+-5%5D

In C, integer division is truncated, not floored.  So the "%" operator can't be
used without adjustment.

Example of truncated division:
\verbatim
 9 /  5 =  1
-9 /  5 = -1
 9 / -5 = -1
-9 / -5 =  1

 9 %  5 =  4
-9 %  5 = -4
 9 % -5 =  4
-9 % -5 = -4

x % y == x - y * (x / y)
\endverbatim

Example of floored division:
\verbatim
 9 /  5 ==  1
-9 /  5 == -2
 9 / -5 == -2
-9 / -5 ==  1

 9 mod  5 ==  4
-9 mod  5 ==  1
 9 mod -5 == -1
-9 mod -5 == -4

Mod[x, y] == x - y * Quotient[x, y]
\endverbatim
*/
constexpr auto floor_mod(const std::signed_integral auto x,
                   const std::signed_integral auto y)
{
#if 0
	return x - y * floor_div(x, y);
#else
	auto rem = x % y;
	if (y < 0)
	{
		if (rem > 0)
		{
			rem += y;
		}
	}
	else
	{
		if (rem < 0)
		{
			rem += y;
		}
	}

	return rem;
#endif
}

/// get the adjusted remainder of the _floored_ integer division
constexpr auto floor_amod(const std::signed_integral auto x,
                    const std::signed_integral auto y)
{
	return floor_mod(x, y) != 0 ? floor_mod(x, y) : y;
}
