// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Checked narrowing cast for integral types
/**
* \file
* \author Steven Ward
*
* A \c narrow_cast function that safely converts between integral types,
* throwing \c std::range_error if the value is not representable in the
* target type. Unlike \c static_cast, this detects out-of-range values
* rather than silently truncating or wrapping them.
*/

#pragma once

#include <concepts>
#include <limits>
#include <stdexcept>
#include <utility>

/// Cast \a value to integral type \a To, throwing if the value is out of range.
/**
* \tparam To   The target integral type
* \tparam From The source integral type
* \param value The value to cast
* \return \a value cast to \a To
* \exception std::range_error if \a value is not representable in \a To
*
* \note \c std::in_range is not used because it does not support character
*       types or \c bool, which are included in the \c std::integral concept.
*       \c std::cmp_less and \c std::cmp_greater handle signed/unsigned
*       comparisons correctly across all integral types.
*/
template <std::integral To, std::integral From>
[[nodiscard]] static constexpr To
narrow_cast(const From value)
{
    if (std::cmp_less(value, std::numeric_limits<To>::min()) ||
        std::cmp_greater(value, std::numeric_limits<To>::max()))
    {
        throw std::range_error{"narrowing error"};
    }

    return static_cast<To>(value);
}
