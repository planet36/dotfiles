// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Absolute value functions
/**
\file
\author Steven Ward
*/

#pragma once

#include <concepts>
#include <cstdlib>
#include <type_traits>

constexpr auto
iabs(const std::signed_integral auto x)
{
	return std::abs(x);
}

constexpr auto
iabs(const std::unsigned_integral auto x)
{
	return x;
}

/**
\return the absolute value of \a x as an unsigned type
*/
constexpr auto
uabs(const std::signed_integral auto x) -> std::make_unsigned_t<decltype(x)>
{
	return std::abs(x);
}

/**
\return the absolute value of \a x as an unsigned type
*/
constexpr auto
uabs(const std::unsigned_integral auto x)
{
	return x;
}

/// Cast the int to unsigned int
constexpr auto
to_unsigned(const std::integral auto x) -> std::make_unsigned_t<decltype(x)>
{
	return x;
}

/// Cast the int to signed int
constexpr auto
to_signed(const std::integral auto x) -> std::make_signed_t<decltype(x)>
{
	return x;
}
