// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// trim leading and trailing characters from a string
/**
\file
\author Steven Ward
*/

#pragma once

#include <algorithm>
#include <cctype>
#include <cwctype>
#include <locale>
#include <string>

// https://stackoverflow.com/a/217605

// {{{ trim spaces from a std::string using std::isspace

void
ltrim(std::string& s)
{
	(void)s.erase(s.begin(), std::find_if_not(s.begin(), s.end(),
	              // Characters must be converted to unsigned char.
	              // https://en.cppreference.com/w/cpp/string/byte/isspace
	              [](const unsigned char c_i) { return std::isspace(c_i); }));
}

void
rtrim(std::string& s)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
	              // Characters must be converted to unsigned char.
	              // https://en.cppreference.com/w/cpp/string/byte/isspace
	              [](const unsigned char c_i) { return std::isspace(c_i); }).base(),
	              s.end());
}

void
trim(std::string& s)
{
	rtrim(s);
	ltrim(s);
}

auto
ltrim_copy(std::string s)
{
	ltrim(s);
	return s;
}

auto
rtrim_copy(std::string s)
{
	rtrim(s);
	return s;
}

auto
trim_copy(std::string s)
{
	trim(s);
	return s;
}

// }}}

// {{{ trim spaces from a std::wstring using std::iswspace

void
ltrim(std::wstring& s)
{
	(void)s.erase(s.begin(), std::find_if_not(s.begin(), s.end(),
	              // https://en.cppreference.com/w/cpp/string/wide/iswspace
	              [](const auto c_i) { return std::iswspace(static_cast<wint_t>(c_i)); }));
}

void
rtrim(std::wstring& s)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
	              // https://en.cppreference.com/w/cpp/string/wide/iswspace
	              [](const auto c_i) { return std::iswspace(static_cast<wint_t>(c_i)); }).base(),
	              s.end());
}

void
trim(std::wstring& s)
{
	rtrim(s);
	ltrim(s);
}

auto
ltrim_copy(std::wstring s)
{
	ltrim(s);
	return s;
}

auto
rtrim_copy(std::wstring s)
{
	rtrim(s);
	return s;
}

auto
trim_copy(std::wstring s)
{
	trim(s);
	return s;
}

// }}}

// {{{ trim spaces from a std::basic_string with std::locale using std::isspace(std::locale)

template <class CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
void
ltrim(std::basic_string<CharT, Traits, Allocator>& s, const std::locale& loc)
{
	(void)s.erase(s.begin(), std::find_if_not(s.begin(), s.end(),
	              // https://en.cppreference.com/w/cpp/locale/isspace
	              [loc](const auto c_i) { return std::isspace(c_i, loc); }));
}

template <class CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
void
rtrim(std::basic_string<CharT, Traits, Allocator>& s, const std::locale& loc)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
	              // https://en.cppreference.com/w/cpp/locale/isspace
	              [loc](const auto c_i) { return std::isspace(c_i, loc); }).base(),
	              s.end());
}

template <class CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
void
trim(std::basic_string<CharT, Traits, Allocator>& s, const std::locale& loc)
{
	rtrim(s, loc);
	ltrim(s, loc);
}

template <class CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
auto
ltrim_copy(std::basic_string<CharT, Traits, Allocator> s,
           const std::locale& loc)
{
	ltrim(s, loc);
	return s;
}

template <class CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
auto
rtrim_copy(std::basic_string<CharT, Traits, Allocator> s,
           const std::locale& loc)
{
	rtrim(s, loc);
	return s;
}

template <class CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
auto
trim_copy(std::basic_string<CharT, Traits, Allocator> s, const std::locale& loc)
{
	trim(s);
	return s;
}

// }}}

// {{{ trim the character from a StringT

template <typename StringT>
void
ltrim(StringT& s, const typename StringT::value_type delim_char)
{
	(void)s.erase(s.begin(), std::find_if_not(s.begin(), s.end(),
	              [delim_char](const auto c_i) { return c_i == delim_char; }));
}

template <typename StringT>
void
rtrim(StringT& s, const typename StringT::value_type delim_char)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
	              [delim_char](const auto c_i) { return c_i == delim_char; }).base(),
	              s.end());
}

template <typename StringT>
void
trim(StringT& s, const typename StringT::value_type delim_char)
{
	rtrim(s, delim_char);
	ltrim(s, delim_char);
}

template <typename StringT>
auto
ltrim_copy(StringT s, const typename StringT::value_type delim_char)
{
	ltrim(s, delim_char);
	return s;
}

template <typename StringT>
auto
rtrim_copy(StringT s, const typename StringT::value_type delim_char)
{
	rtrim(s, delim_char);
	return s;
}

template <typename StringT>
auto
trim_copy(StringT s, const typename StringT::value_type delim_char)
{
	trim(s, delim_char);
	return s;
}

// }}}

// {{{ trim the complement of the character from a StringT

template <typename StringT>
void
ltrim_not(StringT& s, const typename StringT::value_type delim_char)
{
	(void)s.erase(s.begin(), std::find_if_not(s.begin(), s.end(),
	              [delim_char](const auto c_i) { return c_i != delim_char; }));
}

template <typename StringT>
void
rtrim_not(StringT& s, const typename StringT::value_type delim_char)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
	              [delim_char](const auto c_i) { return c_i != delim_char; }).base(),
	              s.end());
}

template <typename StringT>
void
trim_not(StringT& s, const typename StringT::value_type delim_char)
{
	rtrim_not(s, delim_char);
	ltrim_not(s, delim_char);
}

template <typename StringT>
auto
ltrim_not_copy(StringT s, const typename StringT::value_type delim_char)
{
	ltrim_not(s, delim_char);
	return s;
}

template <typename StringT>
auto
rtrim_not_copy(StringT s, const typename StringT::value_type delim_char)
{
	rtrim_not(s, delim_char);
	return s;
}

template <typename StringT>
auto
trim_not_copy(StringT s, const typename StringT::value_type delim_char)
{
	trim_not(s, delim_char);
	return s;
}

// }}}

// {{{ trim the set of characters from a StringT

template <typename StringT>
void
ltrim(StringT& s, const StringT& delim_set)
{
	(void)s.erase(s.begin(), std::find_if_not(s.begin(), s.end(),
	              [delim_set](const auto c_i) { return delim_set.contains(c_i); }));
}

template <typename StringT>
void
rtrim(StringT& s, const StringT& delim_set)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
	              [delim_set](const auto c_i) { return delim_set.contains(c_i); }).base(),
	              s.end());
}

template <typename StringT>
void
trim(StringT& s, const StringT& delim_set)
{
	rtrim(s, delim_set);
	ltrim(s, delim_set);
}

template <typename StringT>
auto
ltrim_copy(StringT s, const StringT& delim_set)
{
	ltrim(s, delim_set);
	return s;
}

template <typename StringT>
auto
rtrim_copy(StringT s, const StringT& delim_set)
{
	rtrim(s, delim_set);
	return s;
}

template <typename StringT>
auto
trim_copy(StringT s, const StringT& delim_set)
{
	trim(s, delim_set);
	return s;
}

// }}}

// {{{ trim the complement of the set of characters from a StringT

template <typename StringT>
void
ltrim_not(StringT& s, const StringT& delim_set)
{
	(void)s.erase(s.begin(), std::find_if_not(s.begin(), s.end(),
	              [delim_set](const auto c_i) { return !delim_set.contains(c_i); }));
}

template <typename StringT>
void
rtrim_not(StringT& s, const StringT& delim_set)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
	              [delim_set](const auto c_i) { return !delim_set.contains(c_i); }).base(),
	              s.end());
}

template <typename StringT>
void
trim_not(StringT& s, const StringT& delim_set)
{
	rtrim_not(s, delim_set);
	ltrim_not(s, delim_set);
}

template <typename StringT>
auto
ltrim_not_copy(StringT s, const StringT& delim_set)
{
	ltrim_not(s, delim_set);
	return s;
}

template <typename StringT>
auto
rtrim_not_copy(StringT s, const StringT& delim_set)
{
	rtrim_not(s, delim_set);
	return s;
}

template <typename StringT>
auto
trim_not_copy(StringT s, const StringT& delim_set)
{
	trim_not(s, delim_set);
	return s;
}

// }}}
