// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Cast floating-point to integer of sufficient size
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "int_bytes.hpp"

#include <concepts>
#include <limits>
#include <stdexcept>

/// Cast \a x to a signed integer with at least as many bits as its significand
/**
* \exception std::range_error if \a x is NaN or its truncated value does not fit
*/
template <std::floating_point T>
constexpr auto
f_to_i(const T x)
{
    using result_type = int_bits<std::numeric_limits<T>::digits>;

    constexpr auto lo = static_cast<T>(std::numeric_limits<result_type>::min());

    if (!(x >= lo && x < -lo))
        throw std::range_error{__func__};

    return static_cast<result_type>(x);
}

/// Cast \a x to an unsigned integer with at least as many bits as its significand
/**
* \exception std::range_error if \a x is NaN or its truncated value does not fit
*/
template <std::floating_point T>
constexpr auto
f_to_u(const T x)
{
    using result_type = uint_bits<std::numeric_limits<T>::digits>;

    constexpr auto hi = static_cast<T>(std::numeric_limits<result_type>::max() / 2 + 1) * 2;

    if (!(x > -1 && x < hi))
        throw std::range_error{__func__};

    return static_cast<result_type>(x);
}
