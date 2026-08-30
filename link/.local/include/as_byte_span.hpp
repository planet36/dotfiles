// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Get a view to the object as a span of bytes
/**
* Each overload returns a view that's valid only while the referenced storage
* remains valid.
*
* Beware of a dangling span.  The storage may be destroyed, reallocated, or
* modified.  A temporary argument does not outlive the statement that creates
* it.
*
* \file
* \author Steven Ward
*/

#pragma once

#include <memory>
#include <ranges>
#include <span>
#include <type_traits>

/// Get a view to a single object as a span of bytes
/**
* The view spans the object representation, so padding bytes within \a T are
* included, and their values are unspecified.
*
* \param x the object to view
* \return a \c std::span of <code>const std::byte</code> over the object
*         representation of \a x
*/
template <typename T>
requires (!std::ranges::contiguous_range<T>) && std::is_trivially_copyable_v<T>
[[nodiscard]] constexpr auto
as_byte_span(const T& x) noexcept
{
    return std::as_bytes(std::span(std::addressof(x), 1));
}

/// Get a view to the elements of a contiguous range as a span of bytes
/**
* \param container the range to view
* \return a \c std::span of <code>const std::byte</code> over the elements of
*         \a container
*/
[[nodiscard]] constexpr auto
as_byte_span(const std::ranges::contiguous_range auto& container) noexcept
{
    return std::as_bytes(std::span{container});
}
