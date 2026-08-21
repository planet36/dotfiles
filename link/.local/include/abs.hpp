// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Absolute value functions
/**
* \file
* \author Steven Ward
*
* \sa https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/p3643r2.html
* \sa https://eisenwave.github.io/cpp-proposals/to-signed-unsigned.html
*/

#pragma once

#include <concepts>
#include <cstdlib>
#include <type_traits>

/// Cast the int to unsigned int
constexpr auto
to_unsigned(const std::integral auto x)
{
    return static_cast<std::make_unsigned_t<decltype(x)>>(x);
}

/// Cast the int to signed int
constexpr auto
to_signed(const std::integral auto x)
{
    return static_cast<std::make_signed_t<decltype(x)>>(x);
}

/**
\return the absolute value of \a x as an unsigned type
*/
constexpr auto
uabs(const std::signed_integral auto x)
{
    return to_unsigned(std::abs(x));
}

/**
\return the absolute value of \a x as an unsigned type
*/
constexpr auto
uabs(const std::unsigned_integral auto x)
{
    return x;
}
