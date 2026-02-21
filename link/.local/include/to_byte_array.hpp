// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Convert an object to a \c std::array of \c std::byte
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <array>
#include <bit>
#include <cstddef>

constexpr auto
to_byte_array(const auto& x)
{
    return std::bit_cast<std::array<std::byte, sizeof(x)>>(x);
}
