// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concept for a "string-like" type
/**
\file
\author Steven Ward
*/

#pragma once

#include <concepts>
#include <string_view>
#include <type_traits>

template<typename T>
concept convertible_to_any_string_view =
    std::convertible_to<T, std::string_view> ||
    std::convertible_to<T, std::wstring_view> ||
    std::convertible_to<T, std::u8string_view> ||
    std::convertible_to<T, std::u16string_view> ||
    std::convertible_to<T, std::u32string_view>;

template<typename T>
concept string_like = convertible_to_any_string_view<std::remove_cvref_t<T>>;
