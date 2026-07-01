// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Unions with data members that are standard unsigned integers and x86 SIMD types
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "simd-array.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <immintrin.h>

union alignas(__m128i) simd128i
{
    std::array<std::byte, sizeof(__m128i) / sizeof(std::byte)> bytes{};
    std::array<uint8_t, sizeof(__m128i) / sizeof(uint8_t)> u8;
    std::array<uint16_t, sizeof(__m128i) / sizeof(uint16_t)> u16;
    std::array<uint32_t, sizeof(__m128i) / sizeof(uint32_t)> u32;
    std::array<uint64_t, sizeof(__m128i) / sizeof(uint64_t)> u64;
#if defined(__SIZEOF_INT128__)
    std::array<__uint128_t, sizeof(__m128i) / sizeof(__uint128_t)> u128;
#endif
    __m128i xmm;
};

static_assert(sizeof(simd128i) == sizeof(__m128i));

union alignas(__m256i) simd256i
{
    std::array<std::byte, sizeof(__m256i) / sizeof(std::byte)> bytes{};
    std::array<uint8_t, sizeof(__m256i) / sizeof(uint8_t)> u8;
    std::array<uint16_t, sizeof(__m256i) / sizeof(uint16_t)> u16;
    std::array<uint32_t, sizeof(__m256i) / sizeof(uint32_t)> u32;
    std::array<uint64_t, sizeof(__m256i) / sizeof(uint64_t)> u64;
#if defined(__SIZEOF_INT128__)
    std::array<__uint128_t, sizeof(__m256i) / sizeof(__uint128_t)> u128;
#endif
    arr_m128i<sizeof(__m256i) / sizeof(__m128i)> xmm;
    __m256i ymm;
};

static_assert(sizeof(simd256i) == sizeof(__m256i));
