// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Get a view to the object as a span of bytes
/**
* \file
* \author Steven Ward
*
* Each overload returns a view that dangles once the referenced storage is
* destroyed or reallocated.  A temporary argument is destroyed at the end of the
* statement that creates it.
*/

#pragma once

#include <memory>
#include <ranges>
#include <span>
#include <type_traits>

/// Get a view to a single object as a span of bytes
/**
* Padding bytes within \a T are included, and their values are unspecified.
*
* \param x the object to view
* \return a <code>std::span<const std::byte, sizeof(T)></code> over the object
*         representation of \a x
*/
template <typename T>
requires (!std::ranges::contiguous_range<T>) && std::is_trivially_copyable_v<T>
[[nodiscard]] constexpr auto
as_byte_span(const T& x) noexcept
{
    return std::as_bytes(std::span<const T, 1>(std::addressof(x), 1));
}

/// Get a view to the elements of a contiguous range as a span of bytes
/**
* \param container the range to view
* \return a \c std::span of <code>const std::byte</code> over the elements of
*         \a container, with a static extent when \a container has one
*/
template <typename R>
requires std::ranges::contiguous_range<const R> &&
         std::ranges::sized_range<const R> &&
         std::is_trivially_copyable_v<std::ranges::range_value_t<const R>>
[[nodiscard]] constexpr auto
as_byte_span(const R& container) noexcept
{
    return std::as_bytes(std::span{container});
}
