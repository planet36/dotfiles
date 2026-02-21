// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// array of factorial values
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <array>
#include <cstdint>

/// array of factorial values
/**
* Python snippet to generate the array
* \code{.py}
import math
for x in range(21):
    print(f"    UINT64_C({math.factorial(x)}), // {x}!")
\endcode
*/
inline constexpr auto factorial_arr = std::array{
    UINT64_C(1), // 0!
    UINT64_C(1), // 1!
    UINT64_C(2), // 2!
    UINT64_C(6), // 3!
    UINT64_C(24), // 4!
    UINT64_C(120), // 5!
    UINT64_C(720), // 6!
    UINT64_C(5040), // 7!
    UINT64_C(40320), // 8!
    UINT64_C(362880), // 9!
    UINT64_C(3628800), // 10!
    UINT64_C(39916800), // 11!
    UINT64_C(479001600), // 12!
    UINT64_C(6227020800), // 13!
    UINT64_C(87178291200), // 14!
    UINT64_C(1307674368000), // 15!
    UINT64_C(20922789888000), // 16!
    UINT64_C(355687428096000), // 17!
    UINT64_C(6402373705728000), // 18!
    UINT64_C(121645100408832000), // 19!
    UINT64_C(2432902008176640000), // 20!
};
