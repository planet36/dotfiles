// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Get the integer part and fractional part of a floating-point number
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <cmath>
#include <concepts>

/// get the integer and fractional parts of a floating-point number
template <std::floating_point T>
constexpr void
int_frac_parts(const T x, T& i, T& f)
{
    f = std::modf(x, &i);
}

/// get the integer part of a floating-point number
template <std::floating_point T>
constexpr T
int_part(const T x)
{
    T i{};
    T f{};
    int_frac_parts(x, i, f);
    return i;
}

/// get the fractional part of a floating-pointing point number
template <std::floating_point T>
constexpr T
frac_part(const T x)
{
    T i{};
    T f{};
    int_frac_parts(x, i, f);
    return f;
}
