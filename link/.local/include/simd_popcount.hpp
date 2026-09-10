// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Count the number of 1-bits
/**
* \file
* \author Steven Ward
* \sa https://cppreference.com/w/cpp/numeric/popcount.html
*/

#pragma once

#if defined(__x86_64__)

#include <bit>
#include <cstdint>
#include <immintrin.h>

#if defined(__SSE4_1__)
[[nodiscard]] inline int
simd_popcount(const __m128i x) noexcept
{
    const auto x0 = static_cast<uint64_t>(_mm_extract_epi64(x, 0));
    const auto x1 = static_cast<uint64_t>(_mm_extract_epi64(x, 1));
    return std::popcount(x0) + std::popcount(x1);
}
#endif

#if defined(__AVX__)
[[nodiscard]] inline int
simd_popcount(const __m256i x) noexcept
{
    const auto x0 = static_cast<uint64_t>(_mm256_extract_epi64(x, 0));
    const auto x1 = static_cast<uint64_t>(_mm256_extract_epi64(x, 1));
    const auto x2 = static_cast<uint64_t>(_mm256_extract_epi64(x, 2));
    const auto x3 = static_cast<uint64_t>(_mm256_extract_epi64(x, 3));
    return std::popcount(x0) + std::popcount(x1) + std::popcount(x2) + std::popcount(x3);
}
#endif

#if defined(__AVX512F__)
[[nodiscard]] inline int
simd_popcount(const __m512i x) noexcept
{
    const auto x0 = _mm512_extracti64x4_epi64(x, 0);
    const auto x1 = _mm512_extracti64x4_epi64(x, 1);
    return simd_popcount(x0) + simd_popcount(x1);
}
#endif

#elif defined(__aarch64__) && defined(__ARM_NEON)

#include <arm_neon.h>

[[nodiscard]] inline int
simd_popcount(const uint8x16_t x) noexcept
{
    return vaddvq_u8(vcntq_u8(x));
}

#else

#error "Architecture not supported"

#endif
