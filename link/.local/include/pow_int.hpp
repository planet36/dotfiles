// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// constexpr integer exponentiation
/**
* \file
* \author Steven Ward
* Inspired by https://web.archive.org/web/20200629174939/http://timmurphy.org/2013/06/27/template-metaprogramming-in-c/
*/

#pragma once

#include <cstdint>
#include <limits>

/// Raise base \a B to the power of exponent \a E
template <typename T, T B, int8_t E>
consteval T
pow_int_func()
{
    if constexpr (E < 0)
    {
        // https://mathworld.wolfram.com/DivisionbyZero.html
        static_assert(B != 0, "division by zero is undefined");

        static_assert(E != std::numeric_limits<decltype(E)>::min(), "signed integer underflow");

        // https://en.wikipedia.org/wiki/Exponentiation#Negative_exponents
        return 1 / pow_int_func<T, B, -E>();
    }
    else if constexpr (E == 0)
    {
        // define 0**0 == 1
        /*
        // https://mathworld.wolfram.com/Indeterminate.html
        // https://en.wikipedia.org/wiki/Zero_to_the_power_of_zero
        static_assert(B != 0, "undefined");
        */

        // https://en.wikipedia.org/wiki/Exponentiation#Zero_exponent
        return 1;
    }
    else if constexpr (E == 1)
    {
        return B;
    }
    else
    {
        // https://en.wikipedia.org/wiki/Exponentiation#Positive_exponents
        return B * pow_int_func<T, B, E - 1>();
    }
}

/// Helper macro
#define POW_INT(BASE, EXPONENT) pow_int_func<std::decay_t<decltype(BASE)>, BASE, EXPONENT>()

/// Raise base \a B to the power of exponent \a E
template <typename T, T B, uint8_t E>
consteval T
pow_uint_func()
{
    if constexpr (E == 0)
    {
        // define 0**0 == 1
        /*
        // https://mathworld.wolfram.com/Indeterminate.html
        // https://en.wikipedia.org/wiki/Zero_to_the_power_of_zero
        static_assert(B != 0, "undefined");
        */

        // https://en.wikipedia.org/wiki/Exponentiation#Zero_exponent
        return 1;
    }
    else if constexpr (E == 1)
    {
        return B;
    }
    else
    {
        // https://en.wikipedia.org/wiki/Exponentiation#Positive_exponents
        return B * pow_uint_func<T, B, E - 1>();
    }
}

/// Helper macro
#define POW_UINT(BASE, EXPONENT) pow_uint_func<std::decay_t<decltype(BASE)>, BASE, EXPONENT>()
