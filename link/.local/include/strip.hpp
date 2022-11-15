// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// strip leading and trailing characters from a string
/**
\file
\author Steven Ward

Note: Only \c std::string is supported.

The \c strip() functions use \c std::string member functions to find delimiters.
The \c trim() functions use <code><algorithm></code> functions to find delimiters.
*/

#pragma once

#include "ascii.hpp"

#include <string>

void rstrip(std::string& s, const std::string& delim_set = ascii_whitespace_s)
{
	const auto i = s.find_last_not_of(delim_set);
	(void)s.erase(i+1);
	//s.resize(i+1);
}

void lstrip(std::string& s, const std::string& delim_set = ascii_whitespace_s)
{
	const auto i = s.find_first_not_of(delim_set);
	(void)s.erase(0, i);
}

void strip(std::string& s, const std::string& delim_set = ascii_whitespace_s)
{
	rstrip(s, delim_set);
	lstrip(s, delim_set);
}

std::string rstrip_copy(std::string s, const std::string& delim_set = ascii_whitespace_s)
{
	rstrip(s, delim_set);
	return s;
}

std::string lstrip_copy(std::string s, const std::string& delim_set = ascii_whitespace_s)
{
	lstrip(s, delim_set);
	return s;
}

std::string strip_copy(std::string s, const std::string& delim_set = ascii_whitespace_s)
{
	strip(s, delim_set);
	return s;
}
