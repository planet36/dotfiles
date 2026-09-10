// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// case-insensitive character and string comparison
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "character.hpp"
#include "type_any_of.hpp"

#include <algorithm>
#include <locale>
#include <string>

/// case-insensitive equal characters, folding only the ASCII letters
template <character CharT>
constexpr bool
ci_equal(const CharT& c1, const CharT& c2)
{
    const auto fold = [](const CharT c)
    {
        return (c >= CharT{'A'} && c <= CharT{'Z'}) ?
                   static_cast<CharT>(c - CharT{'A'} + CharT{'a'}) : c;
    };
    return fold(c1) == fold(c2);
}

/// case-insensitive equal characters (with locale)
template <typename CharT>
requires type_any_of<CharT, char, wchar_t>
bool
ci_equal(const CharT& c1, const CharT& c2, const std::locale& loc)
{
    return (c1 == c2) || (std::toupper(c1, loc) == std::toupper(c2, loc));
}

/// case-insensitive equal strings
template <character CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
bool
ci_equal(const std::basic_string<CharT, Traits, Allocator>& s1,
         const std::basic_string<CharT, Traits, Allocator>& s2)
{
    return std::equal(s1.begin(), s1.end(), s2.begin(), s2.end(),
                      [](const CharT& c1, const CharT& c2) { return ci_equal(c1, c2); });
}

/// case-insensitive equal strings (with locale)
template <typename CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
requires type_any_of<CharT, char, wchar_t>
bool
ci_equal(const std::basic_string<CharT, Traits, Allocator>& s1,
         const std::basic_string<CharT, Traits, Allocator>& s2,
         const std::locale& loc)
{
    return std::equal(s1.begin(), s1.end(), s2.begin(), s2.end(),
                      [loc](const CharT& c1, const CharT& c2)
                      { return ci_equal(c1, c2, loc); });
}

/// case-insensitive equal strings
template <character CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
bool
ci_equal(const std::basic_string<CharT, Traits, Allocator>& s1, const CharT* s2)
{
    return ci_equal(s1, std::basic_string<CharT>{s2});
}

/// case-insensitive equal strings (with locale)
template <typename CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
requires type_any_of<CharT, char, wchar_t>
bool
ci_equal(const std::basic_string<CharT, Traits, Allocator>& s1,
         const CharT* s2,
         const std::locale& loc)
{
    return ci_equal(s1, std::basic_string<CharT>{s2}, loc);
}

/// case-insensitive equal strings
template <character CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
bool
ci_equal(const CharT* s1, const std::basic_string<CharT, Traits, Allocator>& s2)
{
    return ci_equal(std::basic_string<CharT>{s1}, s2);
}

/// case-insensitive equal strings (with locale)
template <typename CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>>
requires type_any_of<CharT, char, wchar_t>
bool
ci_equal(const CharT* s1,
         const std::basic_string<CharT, Traits, Allocator>& s2,
         const std::locale& loc)
{
    return ci_equal(std::basic_string<CharT>{s1}, s2, loc);
}

/// case-insensitive equal strings
template <character CharT>
bool
ci_equal(const CharT* s1, const CharT* s2)
{
    return ci_equal(std::basic_string<CharT>{s1}, std::basic_string<CharT>{s2});
}

/// case-insensitive equal strings (with locale)
template <typename CharT>
requires type_any_of<CharT, char, wchar_t>
bool
ci_equal(const CharT* s1, const CharT* s2, const std::locale& loc)
{
    return ci_equal(std::basic_string<CharT>{s1}, std::basic_string<CharT>{s2}, loc);
}
