// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Get a view to the object as a span of bytes
/**
* \file
* \author Steven Ward
*
* Each overload returns a view that's valid only while the referenced storage
* remains valid.
*
* Beware of a dangling span.  The storage may be destroyed, reallocated, or
* modified.  A temporary argument does not outlive the statement that creates
* it.
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
* The extent is static.  Spelling the \c std::span arguments out is what keeps
* it so, since the deduction guide for a pointer and a count yields
* \c std::dynamic_extent.
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
    return std::as_bytes(std::span<const T, 1>(std::addressof(x), 1));
}

/// Get a view to the elements of a contiguous range as a span of bytes
/**
* The span has a static extent when \a container has one.
*
* \c std::ranges::sized_range is what the \c std::span range constructor
* needs, and it does not follow from \c std::ranges::contiguous_range.  A
* contiguous range whose sentinel is not sized reaches no overload at all,
* which is the diagnostic to want.
*
* Do not add an overload beside this one constrained on a concept that names
* the byte types.  Such a concept does not subsume
* \c std::is_trivially_copyable_v, so neither overload would be the more
* constrained one, and every call passing a range of bytes would be
* ambiguous.
*
* \param container the range to view
* \return a \c std::span of <code>const std::byte</code> over the elements of
*         \a container
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
