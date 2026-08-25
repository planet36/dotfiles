// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Functions to round an integer to a multiple of an integer
/**
* \file
* \author Steven Ward
*/

#pragma once

#if defined(DEBUG)
#include <cassert>
#endif
#include <concepts>

/// Round \a n to the nearest multiple of \a m (toward zero)
/**
* \pre \a m > 0
*/
template <std::integral T>
[[nodiscard]] constexpr T
roundm_trunc(const T n, const T m)
{
#if defined(DEBUG)
    assert(m > 0);
#endif

    const T r = n % m;
    return n - r;
}

/// Round \a n to the nearest multiple of \a m that's at most \a n (toward negative infinity)
/**
* \pre \a m > 0
*/
template <std::integral T>
constexpr T
roundm_floor(const T n, const T m)
{
    const T t = roundm_trunc(n, m);

    if (n == t)
        return t;

    if (n < 0)
        return t - m;
    else
        return t;
}

/// Round \a n to the nearest multiple of \a m that's at least \a n (toward infinity)
/**
* \pre \a m > 0
*/
template <std::integral T>
constexpr T
roundm_ceil(const T n, const T m)
{
    const T t = roundm_trunc(n, m);

    if (n == t)
        return t;

    if (n < 0)
        return t;
    else
        return t + m;
}

/// Round \a n to the nearest multiple of \a m (halfway cases rounded away from zero)
/**
* \pre \a m > 0
*/
template <std::integral T>
constexpr T
roundm_nearest(const T n, const T m)
{
    const T t = roundm_trunc(n, m);

    if (n == t)
        return t;

    if (n < 0)
    {
        if (n % m < -(m / 2))
            return t - m;
        else
            return t;
    }
    else
    {
        if (n % m >  (m / 2))
            return t + m;
        else
            return t;
    }
}
