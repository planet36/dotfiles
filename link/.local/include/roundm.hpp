// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Functions to round an integer to a multiple of an integer
/**
* \file
* \author Steven Ward
*/

#pragma once

#if defined(DEBUG)
#include <bit>
#include <cassert>
#include <type_traits>
#endif
#include <concepts>
#include <expected>
#include <limits>
#include <system_error>

namespace roundm
{

/// Round \a n to the nearest multiple of \a m (toward zero)
/**
* \pre \a m > 0
*/
template <std::integral T>
[[nodiscard]] constexpr T
trunc(const T n, const T m)
{
#if defined(DEBUG)
    assert(m > 0);
#endif

    const T r = n % m;
    return n - r;
}

namespace detail
{

/// Get the next multiple of \a m less than \a t
/**
* \pre \a t is a multiple of \a m
* \pre \a m > 0
* \return \c std::unexpected(std::errc::result_out_of_range) if the result is less than
*         <code>std::numeric_limits<T>::min()</code>
*/
template <std::integral T>
constexpr std::expected<T, std::errc>
below(const T t, const T m)
{
    if (t < std::numeric_limits<T>::min() + m)
        return std::unexpected(std::errc::result_out_of_range);

    return t - m;
}

/// Get the next multiple of \a m greater than \a t
/**
* \pre \a t is a multiple of \a m
* \pre \a m > 0
* \return \c std::unexpected(std::errc::result_out_of_range) if the result is greater than
*         <code>std::numeric_limits<T>::max()</code>
*/
template <std::integral T>
constexpr std::expected<T, std::errc>
above(const T t, const T m)
{
    if (t > std::numeric_limits<T>::max() - m)
        return std::unexpected(std::errc::result_out_of_range);

    return t + m;
}

} // namespace detail

/// Round \a n to the nearest multiple of \a m that's at most \a n (toward negative infinity)
/**
* \pre \a m > 0
* \return \c std::unexpected(std::errc::result_out_of_range) if the result is less than
*         <code>std::numeric_limits<T>::min()</code>
*/
template <std::integral T>
constexpr std::expected<T, std::errc>
floor(const T n, const T m)
{
    const T t = trunc(n, m);

    if (n == t)
        return t;

    if (n < 0)
        return detail::below(t, m);
    else
        return t;
}

/// Round \a n to the nearest multiple of \a m that's at least \a n (toward infinity)
/**
* \pre \a m > 0
* \return \c std::unexpected(std::errc::result_out_of_range) if the result is greater than
*         <code>std::numeric_limits<T>::max()</code>
*/
template <std::integral T>
constexpr std::expected<T, std::errc>
ceil(const T n, const T m)
{
    const T t = trunc(n, m);

    if (n == t)
        return t;

    if (n < 0)
        return t;
    else
        return detail::above(t, m);
}

/// Round \a n to the nearest multiple of \a m that's at least \a n (toward infinity)
/**
* This is \c roundm::ceil for the case where \a n is non-negative and \a m is a power of 2.
* \pre \a n >= 0
* \pre \a m is a positive power of 2
* \return \c std::unexpected(std::errc::result_out_of_range) if the result is greater than
*         <code>std::numeric_limits<T>::max()</code>
*/
template <std::integral T>
constexpr std::expected<T, std::errc>
ceil_pow2(const T n, const T m)
{
#if defined(DEBUG)
    if constexpr (std::numeric_limits<T>::is_signed)
        assert(n >= 0);
    assert(m > 0);
    assert(std::has_single_bit(static_cast<std::make_unsigned_t<T>>(m)));
#endif

    const T r = n & (m - 1); // equivalent to n % m

    if (r == 0)
        return n;

    const T t = n - r;

    return detail::above(t, m);
}

/// Round \a n to the nearest multiple of \a m (halfway cases rounded away from zero)
/**
* \pre \a m > 0
* \return \c std::unexpected(std::errc::result_out_of_range) if the result is less than
*         <code>std::numeric_limits<T>::min()</code> or greater than
*         <code>std::numeric_limits<T>::max()</code>
*/
template <std::integral T>
constexpr std::expected<T, std::errc>
nearest(const T n, const T m)
{
    const T t = trunc(n, m);

    if (n == t)
        return t;

    // n lies between t and the adjacent multiple away from zero.
    const T d = (n < t) ? (t - n) : (n - t); // distance from n to t, in [1, m - 1]

    // d == m - d is a halfway case

    if (d < m - d) // not 2 * d < m, which can overflow
    {
        // round toward zero
        return t;
    }
    else
    {
        // round away from zero
        if (n < 0)
            return detail::below(t, m);
        else
            return detail::above(t, m);
    }
}

} // namespace roundm
