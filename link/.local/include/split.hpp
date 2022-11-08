// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// split strings
/**
\file
\author Steven Ward

Note: Only std::string is supported.
*/

#pragma once

#include "ascii.hpp"

#include <limits>
#include <string>
#include <vector>

/// split the string about the delimiter string
/**
No more than \a max_splits will be performed.

If \a delim is empty, the result is a vector with \a s as its only element.
*/
std::vector<std::string>
split(const std::string& s, const std::string& delim,
      const size_t max_splits = std::numeric_limits<size_t>::max())
{
	size_t i = 0; // index of the front of a substring
	size_t j = 0; // index of the back of a substring
	std::vector<std::string> result;

	if (!delim.empty())
	{
		for (size_t num_splits = 0;
		     ((j = s.find(delim, i)) != std::string::npos) &&
		     (num_splits < max_splits);
		     ++num_splits)
		{
			result.emplace_back(s.substr(i, j - i));
			i = j + delim.size();
		}
	}

	result.emplace_back(s.substr(i));

	return result;
}

/// split the string about characters in the delimiter set
/**
No more than \a max_splits will be performed.

If \a delim_set is empty, the result is a vector with \a s as its only element.
*/
std::vector<std::string>
split_set(const std::string& s, const std::string& delim_set,
          const size_t max_splits = std::numeric_limits<size_t>::max())
{
	size_t i = 0; // index of the front of a substring
	size_t j = 0; // index of the back of a substring
	std::vector<std::string> result;

	if (!delim_set.empty())
	{
		for (size_t num_splits = 0;
		     ((i = s.find_first_not_of(delim_set, j)) != std::string::npos) &&
		     ((j = s.find_first_of(delim_set, i)) != std::string::npos) &&
		     (num_splits < max_splits);
		     ++num_splits)
		{
			result.emplace_back(s.substr(i, j - i));
		}
	}

	if (i != std::string::npos)
	{
		result.emplace_back(s.substr(i));
	}
	else if (result.empty())
	{
		result.emplace_back(std::string{});
	}

	return result;
}

/// split the string about characters not in the delimiter set
/**
No more than \a max_splits will be performed.

If \a delim_set is empty, the result is a vector with \a s as its only element.
*/
std::vector<std::string>
split_non_set(const std::string& s, const std::string& delim_set,
              const size_t max_splits = std::numeric_limits<size_t>::max())
{
	size_t i = 0; // index of the front of a substring
	size_t j = 0; // index of the back of a substring
	std::vector<std::string> result;

	if (!delim_set.empty())
	{
		for (size_t num_splits = 0;
		     ((i = s.find_first_of(delim_set, j)) != std::string::npos) &&
		     ((j = s.find_first_not_of(delim_set, i)) != std::string::npos) &&
		     (num_splits < max_splits);
		     ++num_splits)
		{
			result.emplace_back(s.substr(i, j - i));
		}
	}

	if (i != std::string::npos)
	{
		result.emplace_back(s.substr(i));
	}
	else if (result.empty())
	{
		result.emplace_back(std::string{});
	}

	return result;
}

/// split the string about ASCII whitespace characters
std::vector<std::string>
split(const std::string& s)
{
	return split_set(s, ascii_whitespace_s);
}
