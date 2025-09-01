// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Convert between binary and gray code
/**
* \file
* \author Steven Ward
* \sa https://en.wikipedia.org/wiki/Gray_code
*/

#pragma once

#include <concepts>
#include <limits>

constexpr auto
binary_to_gray(std::unsigned_integral auto x) -> decltype(x)
{
    return x ^ (x >> 1);
}

constexpr auto
gray_to_binary(std::unsigned_integral auto x) -> decltype(x)
{
    unsigned short shift = std::numeric_limits<decltype(x)>::digits;

    while (shift /= 2)
    {
        x ^= (x >> shift);
    }

    return x;
}
