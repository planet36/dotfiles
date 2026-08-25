// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// round to a multiple of an integer
/**
* \file
* \author Steven Ward
*/

#pragma once

#if defined(DEBUG)
#include <cassert>
#endif
#include <concepts>

/**
* \pre \a m > 0
*/
template <std::integral T>
constexpr T
roundm_trunc(const T n, const T m)
{
#if defined(DEBUG)
    assert(m > 0);
#endif

    const T r = n % m;
    return n - r;
}

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
    {
        return t - m;
    }
    else
    {
        return t;
    }
}

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
    {
        return t;
    }
    else
    {
        return t + m;
    }
}

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
        {
            return t - m;
        }
        else
        {
            return t;
        }
    }
    else
    {
        if (n % m >  (m / 2))
        {
            return t + m;
        }
        else
        {
            return t;
        }
    }
}
