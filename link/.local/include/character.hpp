// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concepts for character types
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/language/type
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
struct is_wide_character : is_type_any_of<std::remove_cv_t<T>, char16_t, char32_t, wchar_t>
{};

template <typename T>
inline constexpr bool is_wide_character_v = is_wide_character<T>::value;

template <typename T>
struct is_character : std::bool_constant<is_narrow_character_v<T> || is_wide_character_v<T>>
{};

template <typename T>
inline constexpr bool is_character_v = is_character<T>::value;

template <typename T>
concept narrow_character = is_narrow_character_v<T>;

template <typename T>
concept wide_character = is_wide_character_v<T>;

template <typename T>
concept character = narrow_character<T> || wide_character<T>;

// {{{ unit tests

// {{{ affirmative tests
static_assert(narrow_character<char>);
static_assert(narrow_character<const char>);
static_assert(narrow_character<volatile char>);
static_assert(narrow_character<const volatile char>);
static_assert(narrow_character<signed char>);
static_assert(narrow_character<const signed char>);
static_assert(narrow_character<volatile signed char>);
static_assert(narrow_character<const volatile signed char>);
static_assert(narrow_character<unsigned char>);
static_assert(narrow_character<const unsigned char>);
static_assert(narrow_character<volatile unsigned char>);
static_assert(narrow_character<const volatile unsigned char>);
static_assert(narrow_character<char8_t>);
static_assert(narrow_character<const char8_t>);
static_assert(narrow_character<volatile char8_t>);
static_assert(narrow_character<const volatile char8_t>);
static_assert(wide_character<wchar_t>);
static_assert(wide_character<const wchar_t>);
static_assert(wide_character<volatile wchar_t>);
static_assert(wide_character<const volatile wchar_t>);
static_assert(wide_character<char16_t>);
static_assert(wide_character<const char16_t>);
static_assert(wide_character<volatile char16_t>);
static_assert(wide_character<const volatile char16_t>);
static_assert(wide_character<char32_t>);
static_assert(wide_character<const char32_t>);
static_assert(wide_character<volatile char32_t>);
static_assert(wide_character<const volatile char32_t>);
// }}}

// {{{ negative tests
static_assert(!wide_character<char>);
static_assert(!wide_character<const char>);
static_assert(!wide_character<volatile char>);
static_assert(!wide_character<const volatile char>);
static_assert(!wide_character<signed char>);
static_assert(!wide_character<const signed char>);
static_assert(!wide_character<volatile signed char>);
static_assert(!wide_character<const volatile signed char>);
static_assert(!wide_character<unsigned char>);
static_assert(!wide_character<const unsigned char>);
static_assert(!wide_character<volatile unsigned char>);
static_assert(!wide_character<const volatile unsigned char>);
static_assert(!wide_character<char8_t>);
static_assert(!wide_character<const char8_t>);
static_assert(!wide_character<volatile char8_t>);
static_assert(!wide_character<const volatile char8_t>);
static_assert(!narrow_character<wchar_t>);
static_assert(!narrow_character<const wchar_t>);
static_assert(!narrow_character<volatile wchar_t>);
static_assert(!narrow_character<const volatile wchar_t>);
static_assert(!narrow_character<char16_t>);
static_assert(!narrow_character<const char16_t>);
static_assert(!narrow_character<volatile char16_t>);
static_assert(!narrow_character<const volatile char16_t>);
static_assert(!narrow_character<char32_t>);
static_assert(!narrow_character<const char32_t>);
static_assert(!narrow_character<volatile char32_t>);
static_assert(!narrow_character<const volatile char32_t>);
// }}}

// {{{ test other types
static_assert(!character<int>);
static_assert(!character<int*>);
static_assert(!character<double>);
static_assert(!character<int[2]>);
static_assert(!character<char*>);
static_assert(!character<char&>);
static_assert(!character<void*>);
static_assert(!character<char[2]>);
static_assert(!character<char[2][2]>);
//}}}

// }}}
