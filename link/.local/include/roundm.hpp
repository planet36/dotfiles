// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// round to a multiple of an integer
/**
\file
\author Steven Ward
*/

#pragma once

#include <concepts>

/**
\pre \a m > 0
*/
template <std::integral T>
constexpr T
roundm_trunc(const T x, const T m)
{
    return x - x % m;
    //return (x / m) * m;
}

/**
\pre \a m > 0
*/
template <std::integral T>
constexpr T
roundm_floor(const T x, const T m)
{
    const auto t = roundm_trunc(x, m);

    // necessary for x < 0
    //if (x % m == 0)
    if (x == t)
        return x;

    if (x < 0)
        return t - m;
    else
        return t;
}

/**
\pre \a m > 0
*/
template <std::integral T>
constexpr T
roundm_ceil(const T x, const T m)
{
    const auto t = roundm_trunc(x, m);

    // necessary for x > 0
    //if (x % m == 0)
    if (x == t)
        return x;

    if (x < 0)
        return t;
    else
        return t + m;
}

// away from zero
/**
\pre \a m > 0
*/
template <std::integral T>
constexpr T
roundm_up(const T x, const T m)
{
    const auto t = roundm_trunc(x, m);

    //if (x % m == 0)
    if (x == t)
        return x;

    if (x < 0)
        return t - m;
    else
        return t + m;
}

/**
\pre \a m > 0
*/
template <std::integral T>
constexpr T
roundm_nearest(const T x, const T m)
{
    const auto t = roundm_trunc(x, m);

    if (x < 0)
        return (x % m < -(m / 2)) ? t - m : t;
    else
        return (x % m >  (m / 2)) ? t + m : t;
}
