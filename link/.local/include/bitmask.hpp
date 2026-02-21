// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// a bitmask and bit manipulation library
/**
* \file
* \author Steven Ward
*
* For the "one" bitmasks, one bit is set (1) and the rest are not set (0).
* For the "zero" bitmasks, one bit is not set (0) and the rest are set (1).
* For the "lowpass" bitmasks, the low-order bits are set (1) and the high-order bits are not set (0).
* For the "highpass" bitmasks, the high-order bits are set (1) and the low-order bits are not set (0).
*
* Example:
* \verbatim
bitmask of 8 bits

 i  one       zero      lowpass   highpass
 0  00000001  11111110  00000000  11111111
 1  00000010  11111101  00000001  11111110
 2  00000100  11111011  00000011  11111100
 3  00001000  11110111  00000111  11111000
 4  00010000  11101111  00001111  11110000
 5  00100000  11011111  00011111  11100000
 6  01000000  10111111  00111111  11000000
 7  10000000  01111111  01111111  10000000
\endverbatim
*/

#pragma once

#include <concepts>
#include <type_traits>

/// get a bitmask where bit \a i is set (1) and the rest are not set (0)
template <std::unsigned_integral T>
requires (!std::is_same_v<T, bool>)
constexpr T
bitmask_one(const unsigned int i)
{
    return T{1} << i;
}

/// get a bitmask where bit \a i is not set (0) and the rest are set (1)
template <std::unsigned_integral T>
requires (!std::is_same_v<T, bool>)
constexpr T
bitmask_zero(const unsigned int i)
{
    return ~bitmask_one<T>(i);
}

/// get a bitmask where low-order bits (less significant than bit \a i) are set (1) and the rest are not set (0)
template <std::unsigned_integral T>
requires (!std::is_same_v<T, bool>)
constexpr T
bitmask_lowpass(const unsigned int i)
{
    return bitmask_one<T>(i) - 1U;
}

/// get a bitmask where high-order bits (not less significant than bit \a i) are set (1) and the rest are not set (0)
template <std::unsigned_integral T>
requires (!std::is_same_v<T, bool>)
constexpr T
bitmask_highpass(const unsigned int i)
{
    return bitmask_zero<T>(i) + 1U;
}

/// get bit \a i in \a x
template <std::unsigned_integral T>
requires (!std::is_same_v<T, bool>)
constexpr bool
get_bit(const T& x, const unsigned int i)
{
    return x & bitmask_one<T>(i);
}

/// set bit \a i in \a x
template <std::unsigned_integral T>
requires (!std::is_same_v<T, bool>)
constexpr void
set_bit(T& x, const unsigned int i)
{
    x |= bitmask_one<T>(i);
}

/// reset bit \a i in \a x
template <std::unsigned_integral T>
requires (!std::is_same_v<T, bool>)
constexpr void
reset_bit(T& x, const unsigned int i)
{
    x &= bitmask_zero<T>(i);
}

/// toggle bit \a i in \a x
template <std::unsigned_integral T>
requires (!std::is_same_v<T, bool>)
constexpr void
toggle_bit(T& x, const unsigned int i)
{
    x ^= bitmask_one<T>(i);
}
