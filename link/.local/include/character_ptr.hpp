// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concepts for character pointer types
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/language/type
*/

#pragma once

#include "character.hpp"

template <typename T>
struct is_narrow_character_ptr : std::bool_constant<std::is_pointer_v<std::decay_t<T>> &&
                                 is_narrow_character_v<std::remove_pointer_t<std::decay_t<T>>>>
{};

template <typename T>
inline constexpr bool is_narrow_character_ptr_v = is_narrow_character_ptr<T>::value;

template <typename T>
struct is_wide_character_ptr : std::bool_constant<std::is_pointer_v<std::decay_t<T>> &&
                                 is_wide_character_v<std::remove_pointer_t<std::decay_t<T>>>>
{};

template <typename T>
inline constexpr bool is_wide_character_ptr_v = is_wide_character_ptr<T>::value;

template <typename T>
struct is_character_ptr : std::bool_constant<is_narrow_character_ptr_v<T> ||
                          is_wide_character_ptr_v<T>>
{};

template <typename T>
inline constexpr bool is_character_ptr_v = is_character_ptr<T>::value;

template <typename T>
concept narrow_character_ptr = is_narrow_character_ptr_v<T>;

template <typename T>
concept wide_character_ptr = is_wide_character_ptr_v<T>;

template <typename T>
concept character_ptr = narrow_character_ptr<T> || wide_character_ptr<T>;
