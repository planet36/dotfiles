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

union alignas(sizeof(__m128i)) simd128i
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

union alignas(sizeof(__m256i)) simd256i
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

union alignas(sizeof(__m512i)) simd512i
{
    std::array<std::byte, sizeof(__m512i) / sizeof(std::byte)> bytes{};
    std::array<uint8_t, sizeof(__m512i) / sizeof(uint8_t)> u8;
    std::array<uint16_t, sizeof(__m512i) / sizeof(uint16_t)> u16;
    std::array<uint32_t, sizeof(__m512i) / sizeof(uint32_t)> u32;
    std::array<uint64_t, sizeof(__m512i) / sizeof(uint64_t)> u64;
#if defined(__SIZEOF_INT128__)
    std::array<__uint128_t, sizeof(__m512i) / sizeof(__uint128_t)> u128;
#endif
    arr_m128i<sizeof(__m512i) / sizeof(__m128i)> xmm;
    arr_m256i<sizeof(__m512i) / sizeof(__m256i)> ymm;
    __m512i zmm;
};

static_assert(sizeof(simd512i) == sizeof(__m512i));

template <size_t N>
constexpr auto
arr_m128i_to_simd128i(const arr_m128i<N>& x)
{
    std::array<simd128i, N> y;

    // __m128i to simd128i
    for (size_t i = 0; i < N; ++i)
    {
        y[i].xmm = x[i];
    }

    return y;
}

template <size_t N>
constexpr auto
arr_m256i_to_simd256i(const arr_m256i<N>& x)
{
    std::array<simd256i, N> y;

    // __m256i to simd256i
    for (size_t i = 0; i < N; ++i)
    {
        y[i].ymm = x[i];
    }

    return y;
}

template <size_t N>
constexpr auto
arr_m512i_to_simd512i(const arr_m512i<N>& x)
{
    std::array<simd512i, N> y;

    // __m512i to simd512i
    for (size_t i = 0; i < N; ++i)
    {
        y[i].zmm = x[i];
    }

    return y;
}

template <size_t N>
constexpr auto
arr_simd128i_to_m128i(const std::array<simd128i, N>& x)
{
    arr_m128i<N> y;

    // simd128i to __m128i
    for (size_t i = 0; i < N; ++i)
    {
        y[i] = x[i].xmm;
    }

    return y;
}

template <size_t N>
constexpr auto
arr_simd256i_to_m256i(const std::array<simd256i, N>& x)
{
    arr_m256i<N> y;

    // simd256i to __m256i
    for (size_t i = 0; i < N; ++i)
    {
        y[i] = x[i].ymm;
    }

    return y;
}

template <size_t N>
constexpr auto
arr_simd512i_to_m512i(const std::array<simd512i, N>& x)
{
    arr_m512i<N> y;

    // simd512i to __m512i
    for (size_t i = 0; i < N; ++i)
    {
        y[i] = x[i].zmm;
    }

    return y;
}
