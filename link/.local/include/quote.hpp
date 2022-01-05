// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Quote a string
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/io/manip/quoted
*/

#pragma once

#include <string>
#include <string_view>

namespace
{
constexpr char backslash = '\\';
constexpr char single_quote = '\'';
constexpr char double_quote = '"';

// single quote, backslash, single quote, single quote
constexpr std::string_view single_quote_escaped{R"('\'')"};
}

bool isword(const char c)
{
	return std::isalnum(c) || c == '_';
}

/**
\sa https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_02
*/
bool contains_shell_special_chars(const std::string& s)
{
	for (const char c : s)
	{
		if (
			(c == '\t') ||
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
			(c == '~' )
			)
			return true;
	}

	return false;
}

std::string quote(const std::string& s, const char delim = double_quote,
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

std::string quote(const std::string_view& s, const char delim = double_quote,
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

std::string quote(const char* s, const char delim = double_quote,
                  const char escape = backslash)
{
	std::string result;
	result.push_back(delim);
	while (*s)
	{
		if (*s == delim || *s == escape)
			result.push_back(escape);
		result.push_back(*s);
		++s;
	}
	result.push_back(delim);
	return result;
}
