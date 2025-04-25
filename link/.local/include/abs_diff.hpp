// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Absolute difference between 2 integers as an unsigned integer
/**
\file
\author Steven Ward
\sa https://doc.rust-lang.org/stable/std/index.html?search=abs_diff&filter-crate=std
*/

#pragma once

#include <concepts>
#include <type_traits>

template <std::unsigned_integral T, std::unsigned_integral U>
constexpr std::common_type_t<T, U>
abs_diff(const T a, const U b)
{
    return (a < b) ? b - a : a - b;
}

template <std::signed_integral T, std::signed_integral U>
constexpr std::make_unsigned_t<std::common_type_t<T, U>>
abs_diff(const T a, const U b)
{
    return (a < b) ? b - a : a - b;
}
