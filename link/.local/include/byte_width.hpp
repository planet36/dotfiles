// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get the byte width of an unsigned integer
/**
\file
\author Steven Ward
*/

#pragma once

#include <algorithm>
#include <bit>

constexpr unsigned int
byte_width(const size_t x)
{
    // std::bit_width(0) returns 0, but we want it to be 1
    const unsigned int w = std::max(static_cast<unsigned int>(std::bit_width(x)), 1U);
    return (w / 8) + (w % 8 != 0);
}
