// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Join smaller unsigned ints into larger unsigned ints
/**
\file
\author Steven Ward
*/

#pragma once

static_assert(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__);

#include "int_parts_union.hpp"

#include <concepts>

template <std::unsigned_integral T>
constexpr auto
int_join(const T hi, const T lo)
{
	return int_parts<T>{.parts = {lo, hi}}.whole;
}
