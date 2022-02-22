// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// mod function
/**
\file
\author Steven Ward
*/

#pragma once

#include <concepts>

/// get the remainder of the _floored_ integer division
/**
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
constexpr auto mod(const std::signed_integral auto x,
                   const std::signed_integral auto y)
{
#if 0
	return x - y * int_div_floor(x, y);
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
constexpr auto amod(const std::signed_integral auto x,
                    const std::signed_integral auto y)
{
	return mod(x, y) != 0 ? mod(x, y) : y;
}
