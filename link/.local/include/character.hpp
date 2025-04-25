// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concepts for character types
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/language/type
*/

#pragma once

#include "type_any_of.hpp"

#include <type_traits>

template <typename T>
struct is_narrow_character : is_type_any_of<std::remove_cv_t<T>,
    char, signed char, unsigned char, char8_t>
{};

template <typename T>
inline constexpr bool is_narrow_character_v = is_narrow_character<T>::value;

template <typename T>
struct is_wide_character : is_type_any_of<std::remove_cv_t<T>,
    char16_t, char32_t, wchar_t>
{};

template <typename T>
inline constexpr bool is_wide_character_v = is_wide_character<T>::value;

template <typename T>
struct is_character : std::bool_constant<
    is_narrow_character_v<T> || is_wide_character_v<T>>
{};

template <typename T>
inline constexpr bool is_character_v = is_character<T>::value;

template <typename T>
concept narrow_character = is_narrow_character_v<T>;

template <typename T>
concept wide_character = is_wide_character_v<T>;

template <typename T>
concept character = narrow_character<T> || wide_character<T>;
