// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Concepts of a byte and of a contiguous byte range
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <concepts>
#include <cstddef>
#include <ranges>
#include <type_traits>

/// \c std::byte or a narrow character type, possibly cv-qualified
template <typename T>
concept byte_like =
    std::same_as<std::remove_cv_t<T>, std::byte>     ||
    std::same_as<std::remove_cv_t<T>, char>          ||
    std::same_as<std::remove_cv_t<T>, unsigned char> ||
    std::same_as<std::remove_cv_t<T>, signed char>   ||
    std::same_as<std::remove_cv_t<T>, char8_t>;

/// A contiguous sized range of bytes
/**
* Contiguity does not imply size, as a \c std::views::take_while view shows.
*
* The const requirements reject a view that a const reference cannot iterate,
* such as one from \c std::views::drop_while.  They strip the reference from
* \a T first, since \c const leaves a reference type unchanged.  The
* requirements on \a T itself keep this concept subsuming
* \c std::ranges::contiguous_range and \c std::ranges::sized_range.
*/
template <typename T>
concept contiguous_byte_range =
    std::ranges::contiguous_range<T> &&
    std::ranges::sized_range<T> &&
    std::ranges::contiguous_range<const std::remove_reference_t<T>> &&
    std::ranges::sized_range<const std::remove_reference_t<T>> &&
    byte_like<std::ranges::range_value_t<T>>;
