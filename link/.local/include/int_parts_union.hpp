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
union int_parts
{
	T parts[2];
	uint_bytes<sizeof (T) * 2> whole;
	static_assert(sizeof (parts) == sizeof (whole));
};
