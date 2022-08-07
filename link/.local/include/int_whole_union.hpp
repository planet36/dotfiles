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
	std::array<uint_bytes<sizeof(T) / 2>, 2> parts;
	T whole;
	static_assert(sizeof(parts) == sizeof(whole));
};
