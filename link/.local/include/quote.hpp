// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Quote strings
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/io/manip/quoted
\sa https://www.gnu.org/software/bash/manual/bash.html#Single-Quotes

Note: Only \c std::string is supported.
*/

#pragma once

#include "ascii.hpp"

#include <cctype>
#include <cstdint>
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

/// Is the character special for POSIX shell?
/**
\sa https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_02
*/
constexpr bool
is_special_char_shell(const char c)
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
	       (c == '?' ) ||
	       (c == '[' ) ||
	       (c == '\\') ||
	       (c == '`' ) ||
	       (c == '|' ) ||
	       (c == '~' );
}

/// Does the string contain special characters for POSIX shell?
bool
contains_special_chars_shell(const std::string& s)
{
	for (const auto c : s)
	{
		if (is_special_char_shell(c))
			return true;
	}

	return false;
}

/// Get the octal representation of the byte
std::string
as_oct_str(const unsigned char c)
{
	static constexpr std::string_view oct_digits{"01234567"};
	return std::string{backslash,
		oct_digits[(c & 0700) >> 6],
		oct_digits[(c & 0070) >> 3],
		oct_digits[(c & 0007)     ],
	};
}

/// Get the hexadecimal representation of the byte
std::string
as_hex_str(const unsigned char c)
{
	static constexpr std::string_view hex_digits{"0123456789ABCDEF"};
	return std::string{backslash, 'x',
		hex_digits[(c & 0xF0) >> 4],
		hex_digits[(c & 0x0F)     ],
	};
}

/// Escape the character for POSIX shell
/**
\sa https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_02
*/
std::string
escape_char_shell(const char c)
{
	switch (c)
	{
	case '\t': return std::string{backslash, 't'};
	case '\n': return std::string{backslash, 'n'};
	case ' ' :
	case '"' :
	case '#' :
	case '$' :
	case '%' :
	case '&' :
	case '\'':
	case '(' :
	case ')' :
	case '*' :
	case ';' :
	case '<' :
	case '=' :
	case '>' :
	case '?' :
	case '[' :
	case '\\':
	case '`' :
	case '|' :
	case '~' : return std::string{backslash, c};
	default: break;
	}

	if (std::isprint(static_cast<unsigned char>(c)))
		return std::string{c};

	return as_hex_str(c);
}

/// Escape the character for C
auto
quote_char(const char c)
{
	static constexpr char delim = single_quote;
	std::string result;
	result.reserve(4 + 2);
	result.push_back(delim);
	result += c_simple_esc_seq_hex[static_cast<unsigned char>(c)];
	result.push_back(delim);
	return result;
}

/// Escape the character for C
/**
\sa https://en.cppreference.com/w/c/language/escape
\sa https://en.cppreference.com/w/cpp/language/escape
\sa https://eel.is/c++draft/lex.ccon#:simple-escape-sequence-char
*/
std::string
escape_char_c(const char c)
{
	// simple escape sequence
	switch (c)
	{
	case '\a': return std::string{backslash, 'a'};
	case '\b': return std::string{backslash, 'b'};
	case '\t': return std::string{backslash, 't'};
	case '\n': return std::string{backslash, 'n'};
	case '\v': return std::string{backslash, 'v'};
	case '\f': return std::string{backslash, 'f'};
	case '\r': return std::string{backslash, 'r'};
	case '\"': return std::string{backslash, c};
	//case '\'': return std::string{backslash, c};
	//case '\?': return std::string{backslash, c};
	case '\\': return std::string{backslash, c};
	default: break;
	}

	if (std::isprint(static_cast<unsigned char>(c)))
		return std::string{c};
	else
		return as_hex_str(c);
}

/**
\sa https://en.cppreference.com/w/cpp/io/manip/quoted
*/
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

/// Quote the string for POSIX shell
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

/// Conditionally quote the string for POSIX shell
auto
quote_shell(const std::string& s)
{
	if (s.empty() || contains_special_chars_shell(s))
		return quote_shell_always(s);
	else
		return s;
}

/// Escape control characters and space characters in the string
auto
quote_escape(const std::string& s)
{
	constexpr char escape = backslash;
	std::string result;
	result.reserve(s.size());
	for (const auto c : s)
	{
		if (std::iscntrl(static_cast<unsigned char>(c)))
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

/// Escape the string for C
auto
quote_c(const std::string& s)
{
	static constexpr char delim = double_quote;
	static constexpr char escape = backslash;
	std::string result;
	result.reserve(s.size() + 2);
	result.push_back(delim);
	for (const auto c : s)
	{
		if (std::iscntrl(static_cast<unsigned char>(c)))
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

/// Escape the string for PCRE
auto
quote_pcre(const std::string& s)
{
	static constexpr auto is_word = [](const char c)
	{
		return (c == '_') || std::isalnum(static_cast<unsigned char>(c));
	};

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
