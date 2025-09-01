// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// round-half-up function
/**
* \file
* \author Steven Ward
* \sa https://www.clivemaxfield.com/diycalculator/popup-m-round.shtml
* \sa https://www.eetimes.com/an-introduction-to-different-rounding-algorithms/
*/

#pragma once

#include "next.hpp"

#include <cmath>
#include <concepts>

/// Round to the nearest integer, with halfway cases rounding away from zero.
/**
* This is faster than \c std::round.
* \sa https://en.cppreference.com/w/cpp/numeric/math/round
*/
template <std::floating_point T>
constexpr T
round_half_up(const T x)
{
    // NOTE: next-less-than 0.5 is necessary when x == +/-0.49999999999999994
    static constexpr T almost_half = next_less(T{0.5});

    return std::trunc(x + std::copysign(almost_half, x));
}
