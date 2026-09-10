// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// User-defined integer literal to create a \c std::byte
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <cstddef>
#include <limits>
#include <stdexcept>

/**
* \pre \a x must be at most 255.  A larger literal does not compile.
*/
consteval std::byte
operator""_b(unsigned long long x)
{
    if (x > std::numeric_limits<unsigned char>::max())
        throw std::out_of_range("byte literal");

    return std::byte{static_cast<unsigned char>(x)};
}
