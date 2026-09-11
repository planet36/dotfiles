// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// sin_cos functions that use references instead of pointers
/**
* \file
* \author Steven Ward
* \sa https://www.gnu.org/software/libc/manual/html_node/Trig-Functions.html#index-sincos
*/

#pragma once

#include <cmath>
#include <concepts>

template <std::floating_point T>
constexpr void
sin_cos(const T x_rad, T& s, T& c)
{
    s = std::sin(x_rad);
    c = std::cos(x_rad);
}
