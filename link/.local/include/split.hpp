// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// split strings
/**
\file
\author Steven Ward

Note: Only \c std::string is supported.
*/

#pragma once

#include "ascii.hpp"

#include <limits>
#include <string>
#include <vector>

/*
* These functions use emplace_back() with iterators instead of
* push_back() with temporary substrings.
*
*   s.substr(i) == std::string(s.begin() + i, s.end())
*
*   s.substr(i, j - i) == std::string(s.begin() + i, s.begin() + j)
*/

/// split the string about the delimiter character
/**
If \a limit is greater than \c 0, the result will have no more than \a limit strings.
*/
std::vector<std::string>
split(const std::string& s, const char delim, const size_t limit = 0)
{
	const auto begin = s.cbegin();
	const auto end = s.cend();
	using diff_t = std::string::difference_type;
	std::string::size_type i = 0; // index of the front of a substring
	std::string::size_type j = 0; // index of the back of a substring
	std::vector<std::string> result;

	while ((result.size() != limit - 1) &&
	       ((j = s.find(delim, i)) != std::string::npos))
	{
		result.emplace_back(begin + static_cast<diff_t>(i),
		                    begin + static_cast<diff_t>(j));
		i = j + 1;
	}

	result.emplace_back(begin + static_cast<diff_t>(i), end);

	return result;
}

/// split the string about the delimiter string
/**
If \a limit is greater than \c 0, the result will have no more than \a limit strings.

If \a delim is empty, the result is a vector with \a s as its only element.
*/
std::vector<std::string>
split(const std::string& s, const std::string& delim, const size_t limit = 0)
{
	const auto begin = s.cbegin();
	const auto end = s.cend();
	using diff_t = std::string::difference_type;
	std::string::size_type i = 0; // index of the front of a substring
	std::string::size_type j = 0; // index of the back of a substring
	std::vector<std::string> result;

	if (!delim.empty())
	{
		while ((result.size() != limit - 1) &&
		       ((j = s.find(delim, i)) != std::string::npos))
		{
			result.emplace_back(begin + static_cast<diff_t>(i),
			                    begin + static_cast<diff_t>(j));
			i = j + delim.size();
		}
	}

	result.emplace_back(begin + static_cast<diff_t>(i), end);

	return result;
}

/// split the string about characters in the delimiter set
/**
If \a limit is greater than \c 0, the result will have no more than \a limit strings.

If \a delim_set is empty, the result is a vector with \a s as its only element.
*/
std::vector<std::string>
split_set(const std::string& s,
          const std::string& delim_set,
          const size_t limit = 0)
{
	const auto begin = s.cbegin();
	const auto end = s.cend();
	using diff_t = std::string::difference_type;
	std::string::size_type i = 0; // index of the front of a substring
	std::string::size_type j = 0; // index of the back of a substring
	std::vector<std::string> result;

	if (!delim_set.empty())
	{
		while (((i = s.find_first_not_of(delim_set, j)) != std::string::npos) &&
		       (result.size() != limit - 1) &&
		       ((j = s.find_first_of(delim_set, i)) != std::string::npos))
		{
			result.emplace_back(begin + static_cast<diff_t>(i),
			                    begin + static_cast<diff_t>(j));
		}
	}

	if (i != std::string::npos)
	{
		result.emplace_back(begin + static_cast<diff_t>(i), end);
	}
	else if (result.empty())
	{
		result.emplace_back();
	}

	return result;
}

/// split the string about characters not in the delimiter set
/**
If \a limit is greater than \c 0, the result will have no more than \a limit strings.

If \a delim_set is empty, the result is a vector with \a s as its only element.
*/
std::vector<std::string>
split_non_set(const std::string& s,
              const std::string& delim_set,
              const size_t limit = 0)
{
	const auto begin = s.cbegin();
	const auto end = s.cend();
	using diff_t = std::string::difference_type;
	std::string::size_type i = 0; // index of the front of a substring
	std::string::size_type j = 0; // index of the back of a substring
	std::vector<std::string> result;

	if (!delim_set.empty())
	{
		while (((i = s.find_first_of(delim_set, j)) != std::string::npos) &&
		       (result.size() != limit - 1) &&
		       ((j = s.find_first_not_of(delim_set, i)) != std::string::npos))
		{
			result.emplace_back(begin + static_cast<diff_t>(i),
			                    begin + static_cast<diff_t>(j));
		}
	}

	if (i != std::string::npos)
	{
		result.emplace_back(begin + static_cast<diff_t>(i), end);
	}
	else if (result.empty())
	{
		result.emplace_back();
	}

	return result;
}

/// split the string about ASCII whitespace characters
std::vector<std::string>
split(const std::string& s)
{
	return split_set(s, ascii_whitespace_s);
}
