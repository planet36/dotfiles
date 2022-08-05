// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Join smaller unsigned ints into larger unsigned ints
/**
\file
\author Steven Ward
*/

#pragma once

#include "int_parts_union.hpp"

#include <bit>
#include <concepts>

template <std::unsigned_integral T>
constexpr auto
int_join(const T hi, const T lo)
{
	if constexpr (std::endian::native == std::endian::little)
		return int_parts<T>{.parts = {lo, hi}}.whole;
	else if constexpr (std::endian::native == std::endian::big)
		return int_parts<T>{.parts = {hi, lo}}.whole;
	else // mixed endian
		__builtin_unreachable();
}
