// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Quote a string
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/io/manip/quoted

Note: Only \c std::string is supported.
*/

#pragma once

#include "ascii.hpp"
#include "ctype.hpp"

#include <string>
#include <string_view>

namespace
{
inline constexpr char backslash = '\\';
inline constexpr char single_quote = '\'';
inline constexpr char double_quote = '"';

// single quote, backslash, single quote, single quote
inline constexpr std::string_view single_quote_escaped{R"('\'')"};
}

/**
\sa https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_02
*/
constexpr bool
is_shell_special_char(const char c)
{
	return (c == '\t') ||
	       (c == '\n') ||
	       (c == ' ' ) ||
	       (c == '"' ) ||
	       (c == '#' ) ||
	       (c == '$' ) ||
	       (c == '%' ) ||
	       (c == '&' ) ||
	       (c == '\'') ||
	       (c == '(' ) ||
	       (c == ')' ) ||
	       (c == '*' ) ||
	       (c == ';' ) ||
	       (c == '<' ) ||
	       (c == '=' ) ||
	       (c == '>' ) ||
	       (c == '\?') ||
	       (c == '[' ) ||
	       (c == '\\') ||
	       (c == '`' ) ||
	       (c == '|' ) ||
	       (c == '~' );
}

bool
contains_shell_special_chars(const std::string& s)
{
	for (const auto c : s)
	{
		if (is_shell_special_char(c))
			return true;
	}

	return false;
}

auto
quote_char(const char c, const char delim = single_quote)
{
	std::string result;
	result.reserve(4 + 2);
	result.push_back(delim);
	result += c_simple_esc_seq_hex[static_cast<unsigned char>(c)];
	result.push_back(delim);
	return result;
}

auto
quote(const std::string& s,
      const char delim = double_quote,
      const char escape = backslash)
{
	std::string result;
	result.reserve(s.size() + 2);
	result.push_back(delim);
	for (const auto c : s)
	{
		if (c == delim || c == escape)
			result.push_back(escape);
		result.push_back(c);
	}
	result.push_back(delim);
	return result;
}

auto
quote(const char* s,
      const char delim = double_quote,
      const char escape = backslash)
{
	std::string result;
	result.push_back(delim);
	while (*s != '\0')
	{
		if (*s == delim || *s == escape)
			result.push_back(escape);
		result.push_back(*s);
		++s;
	}
	result.push_back(delim);
	return result;
}

/**
\sa https://www.gnu.org/software/bash/manual/bash.html#Single-Quotes
<blockquote>
Enclosing characters in single quotes (‘'’) preserves the literal value of each
character within the quotes. A single quote may not occur between single
quotes, even when preceded by a backslash.
</blockquote>
*/
auto
quote_shell_always(const std::string& s)
{
	constexpr char delim = single_quote;
	std::string result;
	result.reserve(s.size() + 2);
	result.push_back(delim);
	for (const auto c : s)
	{
		if (c == delim)
			result += single_quote_escaped;
		else
			result.push_back(c);
	}
	result.push_back(delim);
	return result;
}

auto
quote_shell(const std::string& s)
{
	if (s.empty() || contains_shell_special_chars(s))
		return quote_shell_always(s);
	else
		return s;
}

auto
quote_escape(const std::string& s, const char escape = backslash)
{
	std::string result;
	result.reserve(s.size());
	for (const auto c : s)
	{
		if (is_control(c))
			result += c_simple_esc_seq_hex[static_cast<unsigned char>(c)];
		else
		{
			if ((c == ' ') || (c == escape))
				result.push_back(escape);
			result.push_back(c);
		}
	}
	return result;
}

auto
quote_c(const std::string& s,
        const char delim = double_quote,
        const char escape = backslash)
{
	std::string result;
	result.reserve(s.size() + 2);
	result.push_back(delim);
	for (const auto c : s)
	{
		if (is_control(c))
			result += c_simple_esc_seq_hex[static_cast<unsigned char>(c)];
		else
		{
			if ((c == delim) || (c == escape))
				result.push_back(escape);
			result.push_back(c);
		}
	}
	result.push_back(delim);
	return result;
}

auto
quote_pcre(const std::string& s)
{
	std::string result;
	result.reserve(s.size());
	for (const auto c : s)
	{
		if (!is_word(c))
			result.push_back(backslash);
		result.push_back(c);
	}
	return result;
}
