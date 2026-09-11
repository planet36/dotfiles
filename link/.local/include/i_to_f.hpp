// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Cast integer to floating-point of sufficient precision
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "float_bytes.hpp"

#include <concepts>
#include <limits>

// XXX: Every uint64_t (digits=64) cannot be cast exactly to long double (digits=64)

template <std::integral T>
requires (std::numeric_limits<T>::digits <= std::numeric_limits<long double>::digits)
constexpr auto
i_to_f(const T x)
{
    using result_type = float_bits<std::numeric_limits<T>::digits>;
    return static_cast<result_type>(x);
}
