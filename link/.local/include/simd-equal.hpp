// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Test if two SIMD values are equal
/**
\file
\author Steven Ward
*/

#pragma once

#include "simd-concepts.hpp"

#include <cstring>

template <simd_t T>
inline bool
simd_equal(const T& a, const T& b)
{
    return std::memcmp(&a, &b, sizeof(T)) == 0;
}
