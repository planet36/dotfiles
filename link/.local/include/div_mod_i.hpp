// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Division and remainder (mod) functions using various rounding methods
/**
\file
\author Steven Ward
\note Division by zero is not checked.
\note Overflow is not checked.

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

#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

/// get the quotient and remainder of the _truncated_ integer division
template <std::integral T>
constexpr void
trunc_div_mod(const T x,
              const T y,
              T& quo,
              T& rem)
{
	quo = x / y;
	rem = x % y;
}

/// get the quotient and remainder of the _floored_ integer division
template <std::integral T>
constexpr void
floor_div_mod(const T x,
              const T y,
              T& quo,
              T& rem)
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
ceil_div_mod(const T x,
             const T y,
             T& quo,
             T& rem)
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
round_div_mod(const T x,
              const T y,
              T& quo,
              T& rem)
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

/// get the quotient and remainder of the _truncated_ integer division
template <std::integral T>
constexpr auto
trunc_div_mod(const T x,
              const T y)
{
	T quo;
	T rem;
	trunc_div_mod(x, y, quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _floored_ integer division
template <std::integral T>
constexpr auto
floor_div_mod(const T x,
              const T y)
{
	T quo;
	T rem;
	floor_div_mod(x, y, quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _ceiling_ integer division
template <std::integral T>
constexpr auto
ceil_div_mod(const T x,
             const T y)
{
	T quo;
	T rem;
	ceil_div_mod(x, y, quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient and remainder of the _rounded_ integer division
template <std::integral T>
constexpr auto
round_div_mod(const T x,
              const T y)
{
	T quo;
	T rem;
	round_div_mod(x, y, quo, rem);
	return std::make_pair(quo, rem);
}

/// get the quotient of the _truncated_ integer division
template <std::integral T>
constexpr auto
trunc_div(const T x,
          const T y)
{
	T quo;
	T rem;
	trunc_div_mod(x, y, quo, rem);
	return quo;
}

/// get the quotient of the _floored_ integer division
template <std::integral T>
constexpr auto
floor_div(const T x,
          const T y)
{
	T quo;
	T rem;
	floor_div_mod(x, y, quo, rem);
	return quo;
}

/// get the quotient of the _ceiling_ integer division
template <std::integral T>
constexpr auto
ceil_div(const T x,
         const T y)
{
	T quo;
	T rem;
	ceil_div_mod(x, y, quo, rem);
	return quo;
}

/// get the quotient of the _rounded_ integer division
template <std::integral T>
constexpr auto
round_div(const T x,
          const T y)
{
	T quo;
	T rem;
	round_div_mod(x, y, quo, rem);
	return quo;
}

/// get the remainder of the _truncated_ integer division
template <std::integral T>
constexpr auto
trunc_mod(const T x,
          const T y)
{
	T quo;
	T rem;
	trunc_div_mod(x, y, quo, rem);
	return rem;
}

/// get the remainder of the _floored_ integer division
template <std::integral T>
constexpr auto
floor_mod(const T x,
          const T y)
{
	T quo;
	T rem;
	floor_div_mod(x, y, quo, rem);
	return rem;
}

/// get the remainder of the _ceiling_ integer division
template <std::integral T>
constexpr auto
ceil_mod(const T x,
         const T y)
{
	T quo;
	T rem;
	ceil_div_mod(x, y, quo, rem);
	return rem;
}

/// get the remainder of the _rounded_ integer division
template <std::integral T>
constexpr auto
round_mod(const T x,
          const T y)
{
	T quo;
	T rem;
	round_div_mod(x, y, quo, rem);
	return rem;
}

/// get the adjusted remainder of the _truncated_ integer division
template <std::integral T>
constexpr auto
trunc_amod(const T x,
           const T y)
{
	return trunc_mod(x, y) == 0 ? y : trunc_mod(x, y);
}

/// get the adjusted remainder of the _floored_ integer division
template <std::integral T>
constexpr auto
floor_amod(const T x,
           const T y)
{
	return floor_mod(x, y) == 0 ? y : floor_mod(x, y);
}

/// get the adjusted remainder of the _ceiling_ integer division
template <std::integral T>
constexpr auto
ceil_amod(const T x,
          const T y)
{
	return ceil_mod(x, y) == 0 ? y : ceil_mod(x, y);
}

/// get the adjusted remainder of the _rounded_ integer division
template <std::integral T>
constexpr auto
round_amod(const T x,
           const T y)
{
	return round_mod(x, y) == 0 ? y : round_mod(x, y);
}
