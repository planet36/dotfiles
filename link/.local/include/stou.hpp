// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// string to unsigned int
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/string/basic_string/stoul
\sa https://en.cppreference.com/w/cpp/string/basic_string/stol
*/

#pragma once

#include <limits>
#include <string>

unsigned int
stou(const std::string& s, std::size_t* pos = nullptr, int base = 10)
{
	const unsigned long i = std::stoul(s, pos, base);
	return (i > std::numeric_limits<unsigned int>::max()) ?
		std::numeric_limits<unsigned int>::max() :
		static_cast<unsigned int>(i);
}
