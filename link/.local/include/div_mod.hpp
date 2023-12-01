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

/// get the quotient and remainder of the _truncated_ integer division
constexpr auto
trunc_div_mod(const std::integral auto x, const std::integral auto y)
{
	const auto quo = x / y;
	const auto rem = x % y;
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _floored_ integer division
/**
\sa https://python-history.blogspot.com/2010/08/why-pythons-integer-division-floors.html
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
constexpr auto
floor_div_mod(const std::integral auto x, const std::integral auto y)
{
	auto quo = x / y;
	auto rem = x % y;

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

	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _ceiling_ integer division
constexpr auto
ceil_div_mod(const std::integral auto x, const std::integral auto y)
{
	auto quo = x / y;
	auto rem = x % y;

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

	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _rounded_ integer division
constexpr auto
round_div_mod(const std::integral auto x, const std::integral auto y)
{
	auto quo = x / y;
	auto rem = x % y;

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

	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _truncated_ floating-point division
constexpr auto
trunc_div_mod(const std::floating_point auto x,
              const std::floating_point auto y)
{
	const auto quo = std::trunc(x / y);
	const auto rem = x - quo * y;
	// fmod is less accurate than division and trunc
	//const auto rem = std::fmod(x, y);
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _floored_ floating-point division
constexpr auto
floor_div_mod(const std::floating_point auto x,
              const std::floating_point auto y)
{
	const auto quo = std::floor(x / y);
	const auto rem = x - quo * y;
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _ceiling_ floating-point division
constexpr auto
ceil_div_mod(const std::floating_point auto x, const std::floating_point auto y)
{
	const auto quo = std::ceil(x / y);
	const auto rem = x - quo * y;
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _rounded_ floating-point division
constexpr auto
round_div_mod(const std::floating_point auto x,
              const std::floating_point auto y)
{
	const auto quo = std::round(x / y);
	const auto rem = x - quo * y;
	return std::make_pair(quo, rem);
}

/// get the quotient of the _truncated_ division
constexpr auto
trunc_div(const auto x, const auto y)
{
	const auto [quo, rem] = trunc_div_mod(x, y);
	return quo;
}

/// get the quotient of the _floored_ division
constexpr auto
floor_div(const auto x, const auto y)
{
	const auto [quo, rem] = floor_div_mod(x, y);
	return quo;
}

/// get the quotient of the _ceiling_ division
constexpr auto
ceil_div(const auto x, const auto y)
{
	const auto [quo, rem] = ceil_div_mod(x, y);
	return quo;
}

/// get the quotient of the _rounded_ division
constexpr auto
round_div(const auto x, const auto y)
{
	const auto [quo, rem] = round_div_mod(x, y);
	return quo;
}

/// get the remainder of the _truncated_ division
constexpr auto
trunc_mod(const auto x, const auto y)
{
	const auto [quo, rem] = trunc_div_mod(x, y);
	return rem;
}

/// get the remainder of the _floored_ division
constexpr auto
floor_mod(const auto x, const auto y)
{
	const auto [quo, rem] = floor_div_mod(x, y);
	return rem;
}

/// get the remainder of the _ceiling_ division
constexpr auto
ceil_mod(const auto x, const auto y)
{
	const auto [quo, rem] = ceil_div_mod(x, y);
	return rem;
}

/// get the remainder of the _rounded_ division
constexpr auto
round_mod(const auto x, const auto y)
{
	const auto [quo, rem] = round_div_mod(x, y);
	return rem;
}

/// get the adjusted remainder of the _truncated_ division
constexpr auto
trunc_amod(const auto x, const auto y)
{
	const auto result = trunc_mod(x, y);
	return result == 0 ? y : result;
}

/// get the adjusted remainder of the _floored_ division
constexpr auto
floor_amod(const auto x, const auto y)
{
	const auto result = floor_mod(x, y);
	return result == 0 ? y : result;
}

/// get the adjusted remainder of the _ceiling_ division
constexpr auto
ceil_amod(const auto x, const auto y)
{
	const auto result = ceil_mod(x, y);
	return result == 0 ? y : result;
}

/// get the adjusted remainder of the _rounded_ division
constexpr auto
round_amod(const auto x, const auto y)
{
	const auto result = round_mod(x, y);
	return result == 0 ? y : result;
}
