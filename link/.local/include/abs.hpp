// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Absolute value functions
/**
* \file
* \author Steven Ward
*
* \sa https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/p3643r2.html
* \sa https://eisenwave.github.io/cpp-proposals/to-signed-unsigned.html
*/

#pragma once

#include "to_unsigned.hpp"

#include <concepts>
#include <type_traits>

/// Cast the int to signed int
constexpr auto
to_signed(const std::integral auto x)
{
    return static_cast<std::make_signed_t<decltype(x)>>(x);
}

/**
\return the absolute value of \a x as an unsigned type

\note C2Y adds \c uabs to the C standard library, and glibc 2.42 declares it in \c stdlib.h.
When that declaration is visible, a call with an \c int argument resolves to that
non-template function, which is not \c constexpr.
*/
constexpr auto
uabs(const std::signed_integral auto x)
{
    using U = std::make_unsigned_t<decltype(x)>;
    const U u = to_unsigned(x);
    return x < 0 ? static_cast<U>(0U - u) : u;
}

/**
\return the absolute value of \a x as an unsigned type
*/
constexpr auto
uabs(const std::unsigned_integral auto x)
{
    return x;
}
