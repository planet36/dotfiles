// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// character type predicates and character case conversions
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/header/cctype
\sa https://en.cppreference.com/w/cpp/string/byte
\sa https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/ctype.h.html
*/

#pragma once

#include "unary_predicate.hpp"

#include <functional>
#include <string>

constexpr bool
is_ascii(const char c)
{
#pragma GCC diagnostic ignored "-Wtype-limits"
	return (c >= 0x00) && (c <= 0x7F);
}

constexpr bool
is_uppercase(const char c)
{
	return (c >= 'A') && (c <= 'Z');
}

constexpr bool
is_lowercase(const char c)
{
	return (c >= 'a') && (c <= 'z');
}

constexpr bool
is_alphabetical(const char c)
{
	return is_uppercase(c) || is_lowercase(c);
}

constexpr bool
is_decimal(const char c)
{
	return (c >= '0') && (c <= '9');
}

constexpr bool
is_alphanumeric(const char c)
{
	return is_alphabetical(c) || is_decimal(c);
}

constexpr bool
is_word(const char c)
{
	return is_alphanumeric(c) || (c == '_');
}

constexpr bool
is_hexadecimal(const char c)
{
	return is_decimal(c) ||
	       ((c >= 'A') && (c <= 'F')) || ((c >= 'a') && (c <= 'f'));
}

constexpr bool
is_octal(const char c)
{
	return (c >= '0') && (c <= '7');
}

constexpr bool
is_binary(const char c)
{
	return (c == '0') || (c == '1');
}

constexpr bool
is_whitespace(const char c)
{
	return (c == '\t') || (c == '\n') || (c == '\v') ||
	       (c == '\f') || (c == '\r') || (c == ' ');
}

constexpr bool
is_blank(const char c)
{
	return (c == '\t') || (c == ' ');
}

constexpr bool
is_visible(const char c)
{
	return (c > ' ') && (c < 0x7F);
}

constexpr bool
is_printable(const char c)
{
	return (c >= ' ') && (c < 0x7F);
}

constexpr bool
is_control(const char c)
{
	return ((c >= 0x00) && (c < ' ')) || (c == 0x7F);
}

constexpr bool
is_punctuation(const char c)
{
	return is_visible(c) && !is_alphanumeric(c);
}

#define DEF_CHAR_PRED(NAME) \
const unary_predicate<char> is_ ## NAME ## _pred = is_ ## NAME; \
const unary_predicate<char> is_non_ ## NAME ## _pred = std::not_fn(is_ ## NAME ## _pred);

DEF_CHAR_PRED(ascii       )
DEF_CHAR_PRED(uppercase   )
DEF_CHAR_PRED(lowercase   )
DEF_CHAR_PRED(alphabetical)
DEF_CHAR_PRED(decimal     )
DEF_CHAR_PRED(alphanumeric)
DEF_CHAR_PRED(word        )
DEF_CHAR_PRED(hexadecimal )
DEF_CHAR_PRED(octal       )
DEF_CHAR_PRED(binary      )
DEF_CHAR_PRED(whitespace  )
DEF_CHAR_PRED(blank       )
DEF_CHAR_PRED(visible     )
DEF_CHAR_PRED(printable   )
DEF_CHAR_PRED(control     )
DEF_CHAR_PRED(punctuation )

#undef DEF_CHAR_PRED

constexpr char
to_ascii(char c)
{
#if 0
	c &= 0x7F;
	return c;
#else
	return c & 0x7F;
#endif
}

constexpr char
to_uppercase(char c)
{
#if 0
	if (is_lowercase(c))
		c -= ('a' - 'A');
	return c;
#else
	return is_lowercase(c) ? c - ('a' - 'A') : c;
#endif
}

constexpr char
to_lowercase(char c)
{
#if 0
	if (is_uppercase(c))
		c += ('a' - 'A');
	return c;
#else
	return is_uppercase(c) ? c + ('a' - 'A') : c;
#endif
}

constexpr char
to_othercase(char c)
{
#if 0
	if (is_uppercase(c))
		c += ('a' - 'A');
	else if (is_lowercase(c))
		c -= ('a' - 'A');
	return c;
#else
	return is_uppercase(c) ? c + ('a' - 'A') :
	      (is_lowercase(c) ? c - ('a' - 'A') : c);
#endif
}

void
to_uppercase(std::string& s)
{
	for (auto& c : s) { c = to_uppercase(c); }
}

void
to_lowercase(std::string& s)
{
	for (auto& c : s) { c = to_lowercase(c); }
}

void
to_othercase(std::string& s)
{
	for (auto& c : s) { c = to_othercase(c); }
}

std::string
to_uppercase_copy(std::string s)
{
	to_uppercase(s);
	return s;
}

std::string
to_lowercase_copy(std::string s)
{
	to_lowercase(s);
	return s;
}

std::string
to_othercase_copy(std::string s)
{
	to_othercase(s);
	return s;
}
