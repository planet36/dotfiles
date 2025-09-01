// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Aliases for vectors of SIMD types
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <immintrin.h>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"

using vec_m128i = std::vector<__m128i>;

using vec_m256i = std::vector<__m256i>;

using vec_m512i = std::vector<__m512i>;

#pragma GCC diagnostic pop
