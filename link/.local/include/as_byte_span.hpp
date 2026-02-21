// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Get a view to the object as a span of bytes
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <memory>
#include <ranges>
#include <span>

template <typename T>
requires (!std::ranges::contiguous_range<T>)
constexpr auto
as_byte_span(const T& x)
{
    return std::as_bytes(std::span(std::addressof(x), 1));
}

constexpr auto
as_byte_span(const std::ranges::contiguous_range auto& container)
{
    return std::as_bytes(std::span{container});
}
