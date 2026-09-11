// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Get the byte width of an unsigned integer
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "to_unsigned.hpp"

#include <bit>
#if defined(DEBUG)
#include <cassert>
#endif
#include <concepts>

/// Get the byte width of an unsigned integer
[[nodiscard]] static constexpr int
byte_width(const std::unsigned_integral auto x) noexcept
{
    // std::bit_width(0) returns 0, but we want it to be 1
    if (x == 0)
        return 1;
    const auto w = std::bit_width(x);
    return (w / 8) + (w % 8 != 0);
}

/// Get the byte width of a non-negative signed integer
/**
* \pre \a x ≥ 0
*/
[[nodiscard]] static constexpr int
byte_width(const std::signed_integral auto x) noexcept
{
#if defined(DEBUG)
    assert(x >= 0);
#endif

    return byte_width(to_unsigned(x));
}
