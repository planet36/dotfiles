// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Test if two SIMD values are equal
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "simd-concepts.hpp"

#include <cstring>

/// Test if \a a and \a b have the same bytes
/**
* Floating-point lanes compare by representation, not by value.  So \c +0.0 and
* \c -0.0 differ, and a NaN equals a NaN with the same bits.
*/
template <simd_t T>
inline bool
simd_equal(const T& a, const T& b)
{
    return std::memcmp(&a, &b, sizeof(T)) == 0;
}
