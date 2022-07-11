// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// trim whitespace from string
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

// {{{ trim spaces from std::string using std::isspace

void
ltrim(std::string& s)
{
	(void)s.erase(s.begin(),
		std::find_if_not(s.begin(), s.end(),
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

// {{{ trim spaces from std::wstring using std::iswspace

void
ltrim(std::wstring& s)
{
	(void)s.erase(s.begin(),
		std::find_if_not(s.begin(), s.end(),
			// https://en.cppreference.com/w/cpp/string/wide/iswspace
			[](const auto c_i) { return std::iswspace(c_i); }));
}

void
rtrim(std::wstring& s)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
			// https://en.cppreference.com/w/cpp/string/wide/iswspace
			[](const auto c_i) { return std::iswspace(c_i); }).base(),
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

// {{{ trim spaces from std::basic_string with std::locale using std::isspace

template <class CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
void
ltrim(std::basic_string<CharT, Traits, Allocator>& s, const std::locale& loc)
{
	(void)s.erase(s.begin(),
		std::find_if_not(s.begin(), s.end(),
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

// {{{ trim character from StringT

template <typename StringT>
void
ltrim(StringT& s, const typename StringT::value_type c)
{
	(void)s.erase(s.begin(),
		std::find_if_not(s.begin(), s.end(),
			[c](const auto c_i) { return c_i == c; }));
}

template <typename StringT>
void
rtrim(StringT& s, const typename StringT::value_type c)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
			[c](const auto c_i) { return c_i == c; }).base(),
		s.end());
}

template <typename StringT>
void
trim(StringT& s, const typename StringT::value_type c)
{
	rtrim(s, c);
	ltrim(s, c);
}

template <typename StringT>
auto
ltrim_copy(StringT s, const typename StringT::value_type c)
{
	ltrim(s, c);
	return s;
}

template <typename StringT>
auto
rtrim_copy(StringT s, const typename StringT::value_type c)
{
	rtrim(s, c);
	return s;
}

template <typename StringT>
auto
trim_copy(StringT s, const typename StringT::value_type c)
{
	trim(s, c);
	return s;
}

// }}}

// {{{ trim set of characters from StringT

template <typename StringT>
void
ltrim_set(StringT& s, const StringT& set)
{
	(void)s.erase(s.begin(),
		std::find_if_not(s.begin(), s.end(),
			[set](const auto c_i) { return set.contains(c_i); }));
}

template <typename StringT>
void
rtrim_set(StringT& s, const StringT& set)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
			[set](const auto c_i) { return set.contains(c_i); }).base(),
		s.end());
}

template <typename StringT>
void
trim_set(StringT& s, const StringT& set)
{
	rtrim_set(s, set);
	ltrim_set(s, set);
}

template <typename StringT>
auto
ltrim_set_copy(StringT s, const StringT& set)
{
	ltrim_set(s, set);
	return s;
}

template <typename StringT>
auto
rtrim_set_copy(StringT s, const StringT& set)
{
	rtrim_set(s, set);
	return s;
}

template <typename StringT>
auto
trim_set_copy(StringT s, const StringT& set)
{
	trim_set(s, set);
	return s;
}

// }}}

// {{{ trim complementary set of characters from StringT

template <typename StringT>
void
ltrim_cset(StringT& s, const StringT& set)
{
	(void)s.erase(s.begin(),
		std::find_if_not(s.begin(), s.end(),
			[set](const auto c_i) { return !set.contains(c_i); }));
}

template <typename StringT>
void
rtrim_cset(StringT& s, const StringT& set)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(),
			[set](const auto c_i) { return !set.contains(c_i); }).base(),
		s.end());
}

template <typename StringT>
void
trim_cset(StringT& s, const StringT& set)
{
	rtrim_cset(s, set);
	ltrim_cset(s, set);
}

template <typename StringT>
auto
ltrim_cset_copy(StringT s, const StringT& set)
{
	ltrim_cset(s, set);
	return s;
}

template <typename StringT>
auto
rtrim_cset_copy(StringT s, const StringT& set)
{
	rtrim_cset(s, set);
	return s;
}

template <typename StringT>
auto
trim_cset_copy(StringT s, const StringT& set)
{
	trim_cset(s, set);
	return s;
}

// }}}
