// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Xorshift 16-bit
/**
\file
\author Steven Ward
\sa http://www.retroprogramming.com/2017/07/xorshift-pseudorandom-numbers-in-z80.html
\sa https://codebase64.org/doku.php?id=base:16bit_xorshift_random_generator
\sa https://www.jstatsoft.org/article/view/v008i14
*/

#pragma once

#include <cstdint>

constexpr uint16_t
xorshift16(uint16_t x, const int a, const int b, const int c)
{
    x ^= x << a;
    x ^= x >> b;
    x ^= x << c;
    return x;
}

constexpr uint16_t
xorshift16(uint16_t x)
{
    return xorshift16(x, 7, 9, 8);
}
