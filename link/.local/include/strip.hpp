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

#include <algorithm>
#include <functional>
#include <string>

// {{{ strip a character from a std::string

void rstrip(std::string& s, const char delim)
{
	const auto i = s.find_last_not_of(delim);
	(void)s.erase(i+1);
	//s.resize(i+1);
}

void lstrip(std::string& s, const char delim)
{
	const auto i = s.find_first_not_of(delim);
	(void)s.erase(0, i);
}

void strip(std::string& s, const char delim)
{
	rstrip(s, delim);
	lstrip(s, delim);
}

std::string rstrip_copy(std::string s, const char delim)
{
	rstrip(s, delim);
	return s;
}

std::string lstrip_copy(std::string s, const char delim)
{
	lstrip(s, delim);
	return s;
}

std::string strip_copy(std::string s, const char delim)
{
	strip(s, delim);
	return s;
}

// }}}

// {{{ strip a set of characters from a std::string

void rstrip(std::string& s, const std::string& delim_set)
{
	const auto i = s.find_last_not_of(delim_set);
	(void)s.erase(i+1);
	//s.resize(i+1);
}

void lstrip(std::string& s, const std::string& delim_set)
{
	const auto i = s.find_first_not_of(delim_set);
	(void)s.erase(0, i);
}

void strip(std::string& s, const std::string& delim_set)
{
	rstrip(s, delim_set);
	lstrip(s, delim_set);
}

std::string rstrip_copy(std::string s, const std::string& delim_set)
{
	rstrip(s, delim_set);
	return s;
}

std::string lstrip_copy(std::string s, const std::string& delim_set)
{
	lstrip(s, delim_set);
	return s;
}

std::string strip_copy(std::string s, const std::string& delim_set)
{
	strip(s, delim_set);
	return s;
}

// }}}

// {{{ strip characters that satisfy a predicate from a std::string

void rstrip(std::string& s, const std::function<bool(char)>& pred)
{
	(void)s.erase(std::find_if_not(s.rbegin(), s.rend(), pred).base(), s.end());
}

void lstrip(std::string& s, const std::function<bool(char)>& pred)
{
	(void)s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), pred));
}

void strip(std::string& s, const std::function<bool(char)>& pred)
{
	rstrip(s, pred);
	lstrip(s, pred);
}

std::string rstrip_copy(std::string s, const std::function<bool(char)>& pred)
{
	rstrip(s, pred);
	return s;
}

std::string lstrip_copy(std::string s, const std::function<bool(char)>& pred)
{
	lstrip(s, pred);
	return s;
}

std::string strip_copy(std::string s, const std::function<bool(char)>& pred)
{
	strip(s, pred);
	return s;
}

// }}}

// {{{ strip whitespace characters from a std::string

void rstrip(std::string& s)
{
	rstrip(s, ascii_whitespace_s);
}

void lstrip(std::string& s)
{
	lstrip(s, ascii_whitespace_s);
}

void strip(std::string& s)
{
	rstrip(s);
	lstrip(s);
}

std::string rstrip_copy(std::string s)
{
	rstrip(s);
	return s;
}

std::string lstrip_copy(std::string s)
{
	lstrip(s);
	return s;
}

std::string strip_copy(std::string s)
{
	strip(s);
	return s;
}

// }}}