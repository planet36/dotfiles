// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Union that holds parts of a whole unsigned integer
/**
\file
\author Steven Ward
*/

#pragma once

#include "int_bytes.hpp"

#include <concepts>

template <std::unsigned_integral T>
union int_whole
{
	uint_bytes<sizeof(T) / 2> parts[2];
	T whole;
	static_assert(sizeof(parts) == sizeof(whole));
};
