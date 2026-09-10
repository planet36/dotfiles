// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// similar to \c std::copysign but for signed integers
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/numeric/math/copysign
*/

#pragma once

#include "make_negative.hpp"

#if defined(DEBUG)
#include <cassert>
#endif
#include <concepts>
#include <limits>

/**
* \pre \a mag must not be the minimum of its type, unless \a sgn is negative.
*/
constexpr auto
icopysign(const std::signed_integral auto mag,
          const std::signed_integral auto sgn) -> decltype(mag)
{
    if (sgn < 0)
        return make_negative(mag);

#if defined(DEBUG)
    assert(mag != std::numeric_limits<decltype(mag)>::min());
#endif

    return (mag < 0) ? static_cast<decltype(mag)>(-mag) : mag;
}
