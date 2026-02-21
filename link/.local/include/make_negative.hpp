// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Make a signed arithmetic value negative
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <cmath>
#include <concepts>

constexpr auto
make_negative(const std::signed_integral auto x)
{
    if (x < 0)
        return x;
    else
        return -x;
}

constexpr auto
make_negative(const std::floating_point auto x)
{
    if (std::signbit(x))
        return x;
    else
        return std::copysign(x, decltype(x){-1});
}
