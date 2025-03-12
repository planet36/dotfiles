// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Aliases for vectors of SIMD types
/**
\file
\author Steven Ward
*/

#pragma once

#include <immintrin.h>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"

using vec_m128i = std::vector<alignas(sizeof(__m128i)) __m128i>;

using vec_m256i = std::vector<alignas(sizeof(__m256i)) __m256i>;

using vec_m512i = std::vector<alignas(sizeof(__m512i)) __m512i>;

#pragma GCC diagnostic pop
