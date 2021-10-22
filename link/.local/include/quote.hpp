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

std::string quote(const std::string& s, const char delim = '"',
                  const char escape = '\\')
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

std::string quote(const std::string_view& s, const char delim = '"',
                  const char escape = '\\')
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

std::string quote(const char* s, const char delim = '"',
                  const char escape = '\\')
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
