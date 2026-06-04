// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Implementation of \c std::in_range that allows const-qualified template types
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/cpp/utility/in_range
* \sa https://eel.is/c++draft/utility.intcmp#lib:in_range
*
* \c std::in_range does not allow const-qualified template types.
* \sa https://gcc.gnu.org/bugzilla/show_bug.cgi?id=125439
*/

#pragma once

#include <concepts>
#include <limits>
#include <utility>

/// Returns \c true if \a t is representable as type \c R
/**
* \tparam R the integer type whose representable range is checked; may be const-qualified
* \tparam T the integer type of the value under test
* \param t the value to test
* \return \c true if \a t is within the interval <code>[std::numeric_limits<R>::min(), std::numeric_limits<R>::max()]</code>
* \note This is not as restrictive as \c std::in_range.
*/
template <std::integral R, std::integral T>
[[nodiscard]] static constexpr bool
in_range(T t) noexcept
{
    return std::cmp_greater_equal(t, std::numeric_limits<R>::min()) &&
        std::cmp_less_equal(t, std::numeric_limits<R>::max());
}
