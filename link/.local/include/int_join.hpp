// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Join smaller unsigned ints into larger unsigned ints
/**
\file
\author Steven Ward
*/

#pragma once

#include "int_bytes.hpp"

#include <concepts>
#include <limits>

template <std::unsigned_integral T>
constexpr auto
int_join(const T hi, const T lo)
{
	using T2 = next_larger<T>;
	return (static_cast<T2>(hi) << std::numeric_limits<T>::digits) | lo;
}
