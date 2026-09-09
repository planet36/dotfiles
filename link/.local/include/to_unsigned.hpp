// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Cast an integer to its unsigned equivalent
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <concepts>
#include <type_traits>

/// Cast the integer to its unsigned equivalent
/**
* \param x the integer to cast
* \return \a x converted to the unsigned type of the same width, modulo 2^N
*/
[[nodiscard]] constexpr auto
to_unsigned(const std::integral auto x) noexcept
{
    return static_cast<std::make_unsigned_t<decltype(x)>>(x);
}
