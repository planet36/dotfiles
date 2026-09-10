// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Salsa20 quarter-round function
/**
* \file
* \author Steven Ward
* \sa https://cr.yp.to/chacha/chacha-20080128.pdf
*/

#pragma once

#include <bit>
#include <cstdint>

constexpr void
salsa20_qr(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d)
{
    b ^= std::rotl(a + d, 7);
    c ^= std::rotl(a + b, 9);
    d ^= std::rotl(b + c, 13);
    a ^= std::rotl(c + d, 18);
}
