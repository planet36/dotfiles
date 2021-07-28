// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// case-insensitive character and string comparison
/**
\file
\author Steven Ward
*/

#pragma once

#include <cctype>
#include <locale>

/// case-insensitive equal characters
template <class CharT>
bool ci_equal(const CharT& c1, const CharT& c2)
{
	return (c1 == c2) || (std::toupper(c1) == std::toupper(c2));
}

/// case-insensitive equal characters
template <class CharT>
bool ci_equal(const CharT& c1, const CharT& c2, const std::locale& loc)
{
	return (c1 == c2) || (std::toupper(c1, loc) == std::toupper(c2, loc));
}

/// case-insensitive equal strings
template<
	class CharT,
	class Traits = std::char_traits<CharT>,
	class Allocator = std::allocator<CharT>
>
bool ci_equal(
	const std::basic_string<CharT, Traits, Allocator>& s1,
	const std::basic_string<CharT, Traits, Allocator>& s2)
{
	return std::equal(
			s1.begin(), s1.end(),
			s2.begin(), s2.end(),
			[](const CharT& c1, const CharT& c2) {return ci_equal(c1, c2);}
			);
}

/// case-insensitive equal strings
template<
	class CharT,
	class Traits = std::char_traits<CharT>,
	class Allocator = std::allocator<CharT>
>
bool ci_equal(
	const std::basic_string<CharT, Traits, Allocator>& s1,
	const std::basic_string<CharT, Traits, Allocator>& s2,
	const std::locale& loc)
{
	return std::equal(
			s1.begin(), s1.end(),
			s2.begin(), s2.end(),
			[loc](const CharT& c1, const CharT& c2) {return ci_equal(c1, c2, loc);}
			);
}
