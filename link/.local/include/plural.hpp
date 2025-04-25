// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Determine if an integer should have a plural suffix
/**
\file
\author Steven Ward
*/

#pragma once

#include <array>
#include <concepts>
#include <string>

constexpr bool
is_plural(const std::signed_integral auto n)
{
    return (n != 1) && (n != -1);
}

constexpr bool
is_plural(const std::unsigned_integral auto n)
{
    return n != 1;
}

inline constexpr std::array<std::string, 2> plural_suffix{"", "s"};
