// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get the byte width of an unsigned integer
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <bit>
#include <concepts>

/// Get the byte width of an unsigned integer
constexpr unsigned int
byte_width(const std::unsigned_integral auto x)
{
    // std::bit_width(0) returns 0, but we want it to be 1
    if (x == 0)
        return 1;
    const unsigned int w = static_cast<unsigned int>(std::bit_width(x));
    return (w / 8) + (w % 8 != 0);
}
