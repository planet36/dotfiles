// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get the English ordinal suffix for an integer
/**
\file
\author Steven Ward
\sa https://en.wikipedia.org/wiki/English_numerals#Ordinal_numbers
\sa https://en.wikipedia.org/wiki/Ordinal_indicator#English
\sa https://en.wikipedia.org/wiki/Ordinal_numeral#English
*/

#pragma once

#include "abs.hpp"

#include <concepts>
#include <string_view>

constexpr std::string_view
ordinal_suffix(std::unsigned_integral auto n)
{
	switch (n %= 100)
	{
	case 11:
	case 12:
	case 13:
		return "th";
	default: break;
	}

	switch (n %= 10)
	{
	case 1: return "st";
	case 2: return "nd";
	case 3: return "rd";
	default: break;
	}

	return "th";
}

constexpr std::string_view
ordinal_suffix(const std::signed_integral auto n)
{
	return ordinal_suffix(uabs(n));
}
