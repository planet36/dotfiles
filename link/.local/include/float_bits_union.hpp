// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Union that holds a floating-point value and an unsigned integer of the given size
/**
\file
\author Steven Ward
*/

#pragma once

#include "float_bytes.hpp"
#include "int_bytes.hpp"

#include <cstdint>

static_assert(sizeof(uint32_t) == sizeof(float));
static_assert(sizeof(uint64_t) == sizeof(double));
static_assert(__BYTE_ORDER__ == __FLOAT_WORD_ORDER__);

template <unsigned int N>
union float_bits_union;

template <>
union float_bits_union<4>
{
	uint32_t i = 0;
	float f;
};

template <>
union float_bits_union<8>
{
	uint64_t i = 0;
	double f;
};
