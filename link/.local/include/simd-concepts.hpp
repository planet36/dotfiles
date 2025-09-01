// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concepts for SIMD types
/**
* \file
* \author Steven Ward
* Typedefs defined in:
* - xmmintrin.h
* - emmintrin.h
* - avxintrin.h
* - avx512fintrin.h
*/

#pragma once

#include <concepts>
#include <immintrin.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"

template <typename T>
concept simd_float_t = std::same_as<T, __m128> ||
                       std::same_as<T, __m256> ||
                       std::same_as<T, __m512>;

template <typename T>
concept simd_double_t = std::same_as<T, __m128d> ||
                        std::same_as<T, __m256d> ||
                        std::same_as<T, __m512d>;

template <typename T>
concept simd_int_t = std::same_as<T, __m128i> ||
                     std::same_as<T, __m256i> ||
                     std::same_as<T, __m512i>;

#pragma GCC diagnostic pop

template <typename T>
concept simd_t = simd_float_t<T> || simd_double_t<T> || simd_int_t<T>;
