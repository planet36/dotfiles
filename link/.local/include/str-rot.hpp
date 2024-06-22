// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Rotate a string left or right by a number of places
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/algorithm/rotate
*/

#pragma once

#include <algorithm>
#include <iterator>
#include <string>

/// rotate \a s left by \a n places
void
rotl(std::string& s, unsigned int n)
{
	n %= std::size(s);
	auto new_first = std::begin(s);
	std::advance(new_first, n);
	(void)std::rotate(std::begin(s), new_first, std::end(s));
}

/// rotate \a s left by \a n places
inline std::string
rotl_copy(std::string s, unsigned int n) // intentionally pass by value
{
	rotl(s, n);
	return s;
}

/// rotate \a s right by \a n places
void
rotr(std::string& s, unsigned int n)
{
	n %= std::size(s);
	auto new_first = std::rbegin(s);
	std::advance(new_first, n);
	(void)std::rotate(std::rbegin(s), new_first, std::rend(s));
}

/// rotate \a s right by \a n places
inline std::string
rotr_copy(std::string s, unsigned int n) // intentionally pass by value
{
	rotr(s, n);
	return s;
}
