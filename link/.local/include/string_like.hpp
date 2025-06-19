// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concept for a "string-like" type
/**
\file
\author Steven Ward
*/

#pragma once

#include <concepts>
#include <string>
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
concept string_like = convertible_to_any_string_view<std::remove_reference_t<std::decay_t<T>>>;

// {{{ unit tests

// {{{ affirmative tests
static_assert(string_like<char*>);
static_assert(string_like<const char*>);
static_assert(string_like<char8_t*>);
static_assert(string_like<const char8_t*>);
static_assert(string_like<wchar_t*>);
static_assert(string_like<const wchar_t*>);
static_assert(string_like<char16_t*>);
static_assert(string_like<const char16_t*>);
static_assert(string_like<char32_t*>);
static_assert(string_like<const char32_t*>);
static_assert(string_like<char[2]>);
static_assert(string_like<const char[2]>);
static_assert(string_like<char8_t[2]>);
static_assert(string_like<const char8_t[2]>);
static_assert(string_like<wchar_t[2]>);
static_assert(string_like<const wchar_t[2]>);
static_assert(string_like<char16_t[2]>);
static_assert(string_like<const char16_t[2]>);
static_assert(string_like<char32_t[2]>);
static_assert(string_like<const char32_t[2]>);

static_assert(string_like<std::string_view>);
static_assert(string_like<std::wstring_view>);
static_assert(string_like<std::u8string_view>);
static_assert(string_like<std::u16string_view>);
static_assert(string_like<std::u32string_view>);

static_assert(string_like<const std::string_view>);
static_assert(string_like<const std::wstring_view>);
static_assert(string_like<const std::u8string_view>);
static_assert(string_like<const std::u16string_view>);
static_assert(string_like<const std::u32string_view>);

static_assert(string_like<std::string_view&>);
static_assert(string_like<std::wstring_view&>);
static_assert(string_like<std::u8string_view&>);
static_assert(string_like<std::u16string_view&>);
static_assert(string_like<std::u32string_view&>);

static_assert(string_like<const std::string_view&>);
static_assert(string_like<const std::wstring_view&>);
static_assert(string_like<const std::u8string_view&>);
static_assert(string_like<const std::u16string_view&>);
static_assert(string_like<const std::u32string_view&>);

static_assert(string_like<std::string>);
static_assert(string_like<std::wstring>);
static_assert(string_like<std::u8string>);
static_assert(string_like<std::u16string>);
static_assert(string_like<std::u32string>);

static_assert(string_like<const std::string>);
static_assert(string_like<const std::wstring>);
static_assert(string_like<const std::u8string>);
static_assert(string_like<const std::u16string>);
static_assert(string_like<const std::u32string>);

static_assert(string_like<std::string&>);
static_assert(string_like<std::wstring&>);
static_assert(string_like<std::u8string&>);
static_assert(string_like<std::u16string&>);
static_assert(string_like<std::u32string&>);

static_assert(string_like<const std::string&>);
static_assert(string_like<const std::wstring&>);
static_assert(string_like<const std::u8string&>);
static_assert(string_like<const std::u16string&>);
static_assert(string_like<const std::u32string&>);
// }}}

// {{{ negative tests
static_assert(!string_like<signed char*>);
static_assert(!string_like<const signed char*>);
static_assert(!string_like<unsigned char*>);
static_assert(!string_like<const unsigned char*>);

static_assert(!string_like<signed char[2]>);
static_assert(!string_like<const signed char[2]>);
static_assert(!string_like<unsigned char[2]>);
static_assert(!string_like<const unsigned char[2]>);

static_assert(!string_like<volatile char*>);
static_assert(!string_like<const volatile char*>);
static_assert(!string_like<volatile signed char*>);
static_assert(!string_like<const volatile signed char*>);
static_assert(!string_like<volatile unsigned char*>);
static_assert(!string_like<const volatile unsigned char*>);
static_assert(!string_like<volatile char8_t*>);
static_assert(!string_like<const volatile char8_t*>);
static_assert(!string_like<volatile wchar_t*>);
static_assert(!string_like<const volatile wchar_t*>);
static_assert(!string_like<volatile char16_t*>);
static_assert(!string_like<const volatile char16_t*>);
static_assert(!string_like<volatile char32_t*>);
static_assert(!string_like<const volatile char32_t*>);
static_assert(!string_like<volatile char[2]>);
static_assert(!string_like<const volatile char[2]>);
static_assert(!string_like<volatile signed char[2]>);
static_assert(!string_like<const volatile signed char[2]>);
static_assert(!string_like<volatile unsigned char[2]>);
static_assert(!string_like<const volatile unsigned char[2]>);
static_assert(!string_like<volatile char8_t[2]>);
static_assert(!string_like<const volatile char8_t[2]>);
static_assert(!string_like<volatile wchar_t[2]>);
static_assert(!string_like<const volatile wchar_t[2]>);
static_assert(!string_like<volatile char16_t[2]>);
static_assert(!string_like<const volatile char16_t[2]>);
static_assert(!string_like<volatile char32_t[2]>);
static_assert(!string_like<const volatile char32_t[2]>);
// }}}

// {{{ test other types
static_assert(!string_like<int>);
static_assert(!string_like<int*>);
static_assert(!string_like<double>);
static_assert(!string_like<int[2]>);
static_assert( string_like<char*>);
static_assert(!string_like<char&>);
static_assert(!string_like<void*>);
static_assert( string_like<char[2]>);
static_assert(!string_like<char[2][2]>);
static_assert(!string_like<std::string*>);
//}}}

// }}}
