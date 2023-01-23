// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Union that holds parts of a whole unsigned integer
/**
\file
\author Steven Ward
*/

#pragma once

#include "int_bytes.hpp"

#include <array>
#include <concepts>

template <std::unsigned_integral T>
union int_whole
{
	T whole{};
	std::array<next_smaller<T>, 2> parts;
	static_assert(sizeof(parts) == sizeof(whole));

	/// named ctor
	static constexpr auto from_parts(const decltype(parts)& new_parts)
	{
		return int_whole<T>{.parts = new_parts};
	}

	/// named ctor
	static constexpr auto from_whole(const decltype(whole)& new_whole)
	{
		return int_whole<T>{.whole = new_whole};
	}
};
