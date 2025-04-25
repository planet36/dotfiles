// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Exact integer operations
/**
\file
\author Steven Ward

These integer arithmetic functions throw \c std::overflow_error if the result
is not representable in the given type.  They are inspired by Java functions of
similar names.

\sa https://docs.oracle.com/en/java/javase/20/docs/api/java.base/java/lang/Math.html
\sa https://docs.oracle.com/en/java/javase/20/docs/api/java.base/java/lang/StrictMath.html
\sa https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
*/

#pragma once

#include "div_mod.hpp"

#include <concepts>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>

/** Given \c x and \c y of type \c T, throw \c std::overflow_error if \c y is
* zero or the quotient of \c x/y overflows a \c T. */
#define DIVIDE_CHECK                                          \
    if (y == T{})                                             \
        throw std::overflow_error(__func__);                  \
    if constexpr (std::is_signed_v<T>)                        \
    {                                                         \
        if (x == std::numeric_limits<T>::min() && y == T{-1}) \
            throw std::overflow_error(__func__);              \
    }

template <std::integral T>
T
absExact(const T x)
{
    if constexpr (std::is_unsigned_v<T>)
    {
        return x;
    }

    if constexpr (std::is_signed_v<T>)
    {
        if (x == std::numeric_limits<T>::min())
            throw std::overflow_error(__func__);
        return std::abs(x);
    }

    std::unreachable();
}

template <std::integral T>
T
addExact(const T x, const T y)
{
    T result{};
    if (__builtin_add_overflow(x, y, &result))
        throw std::overflow_error(__func__);
    return result;
}

/// This is similar to \c toIntExact in the Java \c Math class.
template <std::integral R, std::integral T>
R
castExact(const T x)
{
    if (!std::in_range<R>(x))
        throw std::overflow_error(__func__);
    return static_cast<R>(x);
}

template <std::integral T>
T
ceilDivExact(const T x, const T y)
{
    DIVIDE_CHECK

    return div_ceil(x, y);
}

template <std::integral T>
T
decrementExact(const T x)
{
    if (x == std::numeric_limits<T>::min())
        throw std::overflow_error(__func__);
    return x - 1;
}

template <std::integral T>
T
divideExact(const T x, const T y)
{
    DIVIDE_CHECK

    return x / y;
}

template <std::integral T>
T
floorDivExact(const T x, const T y)
{
    DIVIDE_CHECK

    return div_floor(x, y);
}

template <std::integral T>
T
incrementExact(const T x)
{
    if (x == std::numeric_limits<T>::max())
        throw std::overflow_error(__func__);
    return x + 1;
}

template <std::integral T>
T
multiplyExact(const T x, const T y)
{
    T result{};
    if (__builtin_mul_overflow(x, y, &result))
        throw std::overflow_error(__func__);
    return result;
}

template <std::integral T>
T
negateExact(const T x)
{
    if constexpr (std::is_unsigned_v<T>)
    {
        // 0 is the only unsigned value for which its negative is also unsigned.
        if (x != T{})
            throw std::overflow_error(__func__);
        return x;
    }

    if constexpr (std::is_signed_v<T>)
    {
        if (x == std::numeric_limits<T>::min())
            throw std::overflow_error(__func__);
        return -x;
    }

    std::unreachable();
}

template <std::integral T>
T
roundDivExact(const T x, const T y)
{
    DIVIDE_CHECK

    return div_round(x, y);
}

template <std::integral T>
T
subtractExact(const T x, const T y)
{
    T result{};
    if (__builtin_sub_overflow(x, y, &result))
        throw std::overflow_error(__func__);
    return result;
}

#undef DIVIDE_CHECK
