// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Test if two SIMD values are equal
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <cstring>
#include <immintrin.h>

/// Test if \a a and \a b have the same bytes
inline bool
simd_equal(const __m128i& a, const __m128i& b)
{
    return std::memcmp(&a, &b, sizeof(a)) == 0;
}
