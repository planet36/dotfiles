// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// array of factorial values
/**
* \file
* \author Steven Ward
* \sa https://oeis.org/A000142
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
    UINT64_C(1),                         // 0!
    UINT64_C(1),                         // 1!
    UINT64_C(2),                         // 2!
    UINT64_C(6),                         // 3!
    UINT64_C(24),                        // 4!
    UINT64_C(120),                       // 5!
    UINT64_C(720),                       // 6!
    UINT64_C(5040),                      // 7!
    UINT64_C(40'320),                    // 8!
    UINT64_C(362'880),                   // 9!
    UINT64_C(3'628'800),                 // 10!
    UINT64_C(39'916'800),                // 11!
    UINT64_C(479'001'600),               // 12!
    UINT64_C(6'227'020'800),             // 13!
    UINT64_C(87'178'291'200),            // 14!
    UINT64_C(1'307'674'368'000),         // 15!
    UINT64_C(20'922'789'888'000),        // 16!
    UINT64_C(355'687'428'096'000),       // 17!
    UINT64_C(6'402'373'705'728'000),     // 18!
    UINT64_C(121'645'100'408'832'000),   // 19!
    UINT64_C(2'432'902'008'176'640'000), // 20!
};
