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

// {{{ unit tests

// {{{ affirmative tests
static_assert(narrow_character_ptr<char*>);
static_assert(narrow_character_ptr<const char*>);
static_assert(narrow_character_ptr<volatile char*>);
static_assert(narrow_character_ptr<const volatile char*>);
static_assert(narrow_character_ptr<signed char*>);
static_assert(narrow_character_ptr<const signed char*>);
static_assert(narrow_character_ptr<volatile signed char*>);
static_assert(narrow_character_ptr<const volatile signed char*>);
static_assert(narrow_character_ptr<unsigned char*>);
static_assert(narrow_character_ptr<const unsigned char*>);
static_assert(narrow_character_ptr<volatile unsigned char*>);
static_assert(narrow_character_ptr<const volatile unsigned char*>);
static_assert(narrow_character_ptr<char8_t*>);
static_assert(narrow_character_ptr<const char8_t*>);
static_assert(narrow_character_ptr<volatile char8_t*>);
static_assert(narrow_character_ptr<const volatile char8_t*>);
static_assert(wide_character_ptr<wchar_t*>);
static_assert(wide_character_ptr<const wchar_t*>);
static_assert(wide_character_ptr<volatile wchar_t*>);
static_assert(wide_character_ptr<const volatile wchar_t*>);
static_assert(wide_character_ptr<char16_t*>);
static_assert(wide_character_ptr<const char16_t*>);
static_assert(wide_character_ptr<volatile char16_t*>);
static_assert(wide_character_ptr<const volatile char16_t*>);
static_assert(wide_character_ptr<char32_t*>);
static_assert(wide_character_ptr<const char32_t*>);
static_assert(wide_character_ptr<volatile char32_t*>);
static_assert(wide_character_ptr<const volatile char32_t*>);
static_assert(narrow_character_ptr<char[2]>);
static_assert(narrow_character_ptr<const char[2]>);
static_assert(narrow_character_ptr<volatile char[2]>);
static_assert(narrow_character_ptr<const volatile char[2]>);
static_assert(narrow_character_ptr<signed char[2]>);
static_assert(narrow_character_ptr<const signed char[2]>);
static_assert(narrow_character_ptr<volatile signed char[2]>);
static_assert(narrow_character_ptr<const volatile signed char[2]>);
static_assert(narrow_character_ptr<unsigned char[2]>);
static_assert(narrow_character_ptr<const unsigned char[2]>);
static_assert(narrow_character_ptr<volatile unsigned char[2]>);
static_assert(narrow_character_ptr<const volatile unsigned char[2]>);
static_assert(narrow_character_ptr<char8_t[2]>);
static_assert(narrow_character_ptr<const char8_t[2]>);
static_assert(narrow_character_ptr<volatile char8_t[2]>);
static_assert(narrow_character_ptr<const volatile char8_t[2]>);
static_assert(wide_character_ptr<wchar_t[2]>);
static_assert(wide_character_ptr<const wchar_t[2]>);
static_assert(wide_character_ptr<volatile wchar_t[2]>);
static_assert(wide_character_ptr<const volatile wchar_t[2]>);
static_assert(wide_character_ptr<char16_t[2]>);
static_assert(wide_character_ptr<const char16_t[2]>);
static_assert(wide_character_ptr<volatile char16_t[2]>);
static_assert(wide_character_ptr<const volatile char16_t[2]>);
static_assert(wide_character_ptr<char32_t[2]>);
static_assert(wide_character_ptr<const char32_t[2]>);
static_assert(wide_character_ptr<volatile char32_t[2]>);
static_assert(wide_character_ptr<const volatile char32_t[2]>);
// }}}

// {{{ negative tests
static_assert(!wide_character_ptr<char*>);
static_assert(!wide_character_ptr<const char*>);
static_assert(!wide_character_ptr<volatile char*>);
static_assert(!wide_character_ptr<const volatile char*>);
static_assert(!wide_character_ptr<signed char*>);
static_assert(!wide_character_ptr<const signed char*>);
static_assert(!wide_character_ptr<volatile signed char*>);
static_assert(!wide_character_ptr<const volatile signed char*>);
static_assert(!wide_character_ptr<unsigned char*>);
static_assert(!wide_character_ptr<const unsigned char*>);
static_assert(!wide_character_ptr<volatile unsigned char*>);
static_assert(!wide_character_ptr<const volatile unsigned char*>);
static_assert(!wide_character_ptr<char8_t*>);
static_assert(!wide_character_ptr<const char8_t*>);
static_assert(!wide_character_ptr<volatile char8_t*>);
static_assert(!wide_character_ptr<const volatile char8_t*>);
static_assert(!narrow_character_ptr<wchar_t*>);
static_assert(!narrow_character_ptr<const wchar_t*>);
static_assert(!narrow_character_ptr<volatile wchar_t*>);
static_assert(!narrow_character_ptr<const volatile wchar_t*>);
static_assert(!narrow_character_ptr<char16_t*>);
static_assert(!narrow_character_ptr<const char16_t*>);
static_assert(!narrow_character_ptr<volatile char16_t*>);
static_assert(!narrow_character_ptr<const volatile char16_t*>);
static_assert(!narrow_character_ptr<char32_t*>);
static_assert(!narrow_character_ptr<const char32_t*>);
static_assert(!narrow_character_ptr<volatile char32_t*>);
static_assert(!narrow_character_ptr<const volatile char32_t*>);
static_assert(!wide_character_ptr<char[2]>);
static_assert(!wide_character_ptr<const char[2]>);
static_assert(!wide_character_ptr<volatile char[2]>);
static_assert(!wide_character_ptr<const volatile char[2]>);
static_assert(!wide_character_ptr<signed char[2]>);
static_assert(!wide_character_ptr<const signed char[2]>);
static_assert(!wide_character_ptr<volatile signed char[2]>);
static_assert(!wide_character_ptr<const volatile signed char[2]>);
static_assert(!wide_character_ptr<unsigned char[2]>);
static_assert(!wide_character_ptr<const unsigned char[2]>);
static_assert(!wide_character_ptr<volatile unsigned char[2]>);
static_assert(!wide_character_ptr<const volatile unsigned char[2]>);
static_assert(!wide_character_ptr<char8_t[2]>);
static_assert(!wide_character_ptr<const char8_t[2]>);
static_assert(!wide_character_ptr<volatile char8_t[2]>);
static_assert(!wide_character_ptr<const volatile char8_t[2]>);
static_assert(!narrow_character_ptr<wchar_t[2]>);
static_assert(!narrow_character_ptr<const wchar_t[2]>);
static_assert(!narrow_character_ptr<volatile wchar_t[2]>);
static_assert(!narrow_character_ptr<const volatile wchar_t[2]>);
static_assert(!narrow_character_ptr<char16_t[2]>);
static_assert(!narrow_character_ptr<const char16_t[2]>);
static_assert(!narrow_character_ptr<volatile char16_t[2]>);
static_assert(!narrow_character_ptr<const volatile char16_t[2]>);
static_assert(!narrow_character_ptr<char32_t[2]>);
static_assert(!narrow_character_ptr<const char32_t[2]>);
static_assert(!narrow_character_ptr<volatile char32_t[2]>);
static_assert(!narrow_character_ptr<const volatile char32_t[2]>);
// }}}

// {{{ test other types
static_assert(!character_ptr<int>);
static_assert(!character_ptr<int*>);
static_assert(!character_ptr<int[2]>);
static_assert( character_ptr<char*>);
static_assert(!character_ptr<char&>);
static_assert( character_ptr<char[2]>);
static_assert(!character_ptr<char[2][2]>);
//}}}

// }}}
