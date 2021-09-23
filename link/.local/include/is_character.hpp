// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Checks if a type is a character type
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/language/type
*/

#pragma once

#include <type_traits>

template <typename T>
struct is_narrow_character :
std::bool_constant<
   std::is_same_v<char         , std::remove_cv_t<T>>
|| std::is_same_v<signed char  , std::remove_cv_t<T>>
|| std::is_same_v<unsigned char, std::remove_cv_t<T>>
|| std::is_same_v<char8_t      , std::remove_cv_t<T>>
>{};

template <typename T>
inline constexpr bool is_narrow_character_v = is_narrow_character<T>::value;

template <typename T>
struct is_wide_character :
std::bool_constant<
   std::is_same_v<char16_t, std::remove_cv_t<T>>
|| std::is_same_v<char32_t, std::remove_cv_t<T>>
|| std::is_same_v<wchar_t , std::remove_cv_t<T>>
>{};

template <typename T>
inline constexpr bool is_wide_character_v = is_wide_character<T>::value;

template <typename T>
struct is_character :
std::bool_constant<is_narrow_character_v<T> || is_wide_character_v<T>>{};

template <typename T>
inline constexpr bool is_character_v = is_character<T>::value;
