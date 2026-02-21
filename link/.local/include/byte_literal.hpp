// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// User-defined integer literal to create a \c std::byte
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <cstddef>

constexpr std::byte
operator""_b(unsigned long long x)
{
    return std::byte{static_cast<unsigned char>(x)};
}
