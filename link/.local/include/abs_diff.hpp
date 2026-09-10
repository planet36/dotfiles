// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Absolute difference between 2 integers as an unsigned integer
/**
* \file
* \author Steven Ward
* \sa https://doc.rust-lang.org/stable/std/index.html?search=abs_diff&filter-crate=std
*/

#pragma once

#include <concepts>
#include <type_traits>

template <std::unsigned_integral T, std::unsigned_integral T2>
constexpr std::common_type_t<T, T2>
abs_diff(const T a, const T2 b)
{
    return (a < b) ? b - a : a - b;
}

template <std::signed_integral T, std::signed_integral T2>
constexpr auto
abs_diff(const T a, const T2 b)
{
    using U = std::make_unsigned_t<std::common_type_t<T, T2>>;

    const auto ua = static_cast<U>(a);
    const auto ub = static_cast<U>(b);

    return (a < b) ? static_cast<U>(ub - ua) : static_cast<U>(ua - ub);
}
