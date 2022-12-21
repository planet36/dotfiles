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
template <std::integral T>
constexpr void
trunc_div_mod(const T x, const T y, T& quo, T& rem)
{
	quo = x / y;
	rem = x % y;
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
template <std::integral T>
constexpr void
floor_div_mod(const T x, const T y, T& quo, T& rem)
{
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
}

/// get the quotient and remainder of the _ceiling_ integer division
template <std::integral T>
constexpr void
ceil_div_mod(const T x, const T y, T& quo, T& rem)
{
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
}

/// get the quotient and remainder of the _rounded_ integer division
template <std::integral T>
constexpr void
round_div_mod(const T x, const T y, T& quo, T& rem)
{
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
}

/// get the quotient and remainder of the _truncated_ floating-point division
template <std::floating_point T>
constexpr void
trunc_div_mod(const T x, const T y, T& quo, T& rem)
{
	quo = std::trunc(x / y);
	rem = x - quo * y;
	// fmod is less accurate than division and trunc
	//rem = std::fmod(x, y);
}

/// get the quotient and remainder of the _floored_ floating-point division
template <std::floating_point T>
constexpr void
floor_div_mod(const T x, const T y, T& quo, T& rem)
{
	quo = std::floor(x / y);
	rem = x - quo * y;
}

/// get the quotient and remainder of the _ceiling_ floating-point division
template <std::floating_point T>
constexpr void
ceil_div_mod(const T x, const T y, T& quo, T& rem)
{
	quo = std::ceil(x / y);
	rem = x - quo * y;
}

/// get the quotient and remainder of the _rounded_ floating-point division
template <std::floating_point T>
constexpr void
round_div_mod(const T x, const T y, T& quo, T& rem)
{
	quo = std::round(x / y);
	rem = x - quo * y;
}

/// get the quotient and remainder of the _truncated_ division
constexpr auto
trunc_div_mod(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	trunc_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _floored_ division
constexpr auto
floor_div_mod(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	floor_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _ceiling_ division
constexpr auto
ceil_div_mod(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	ceil_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _rounded_ division
constexpr auto
round_div_mod(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	round_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient of the _truncated_ division
constexpr auto
trunc_div(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	trunc_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return quo;
}

/// get the quotient of the _floored_ division
constexpr auto
floor_div(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	floor_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return quo;
}

/// get the quotient of the _ceiling_ division
constexpr auto
ceil_div(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	ceil_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return quo;
}

/// get the quotient of the _rounded_ division
constexpr auto
round_div(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	round_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return quo;
}

/// get the remainder of the _truncated_ division
constexpr auto
trunc_mod(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	trunc_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return rem;
}

/// get the remainder of the _floored_ division
constexpr auto
floor_mod(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	floor_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return rem;
}

/// get the remainder of the _ceiling_ division
constexpr auto
ceil_mod(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	ceil_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return rem;
}

/// get the remainder of the _rounded_ division
constexpr auto
round_mod(const auto x, const auto y)
{
	using T = std::common_type_t<decltype(x), decltype(y)>;
	T quo;
	T rem;
	round_div_mod(static_cast<T>(x), static_cast<T>(y), quo, rem);
	return rem;
}

/// get the adjusted remainder of the _truncated_ division
constexpr auto
trunc_amod(const auto x, const auto y)
{
	return trunc_mod(x, y) == 0 ? y : trunc_mod(x, y);
}

/// get the adjusted remainder of the _floored_ division
constexpr auto
floor_amod(const auto x, const auto y)
{
	return floor_mod(x, y) == 0 ? y : floor_mod(x, y);
}

/// get the adjusted remainder of the _ceiling_ division
constexpr auto
ceil_amod(const auto x, const auto y)
{
	return ceil_mod(x, y) == 0 ? y : ceil_mod(x, y);
}

/// get the adjusted remainder of the _rounded_ division
constexpr auto
round_amod(const auto x, const auto y)
{
	return round_mod(x, y) == 0 ? y : round_mod(x, y);
}
