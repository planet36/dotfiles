// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Bitmask for 128-bit SIMD type
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <cstdint>

#if defined(__x86_64__)

#include <immintrin.h>
typedef __m128i uint8x16_t;

static inline uint8x16_t
combine_u64x2(const uint64_t hi, const uint64_t lo)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
    return _mm_set_epi64x(hi, lo);
#pragma GCC diagnostic pop
}

#elif defined(__aarch64__)

#include <arm_neon.h>

/**
* \sa https://developer.arm.com/architectures/instruction-sets/intrinsics/vcreate_u64
* \sa https://developer.arm.com/architectures/instruction-sets/intrinsics/vcombine_u64
* \sa https://developer.arm.com/architectures/instruction-sets/intrinsics/vreinterpretq_u8_u64
*/
static inline uint8x16_t
combine_u64x2(const uint64_t hi, const uint64_t lo)
{
    return vreinterpretq_u8_u64(vcombine_u64(vcreate_u64(lo), vcreate_u64(hi)));
}

#else
#error "Architecture not supported"
#endif

#include <array>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"

const std::array<uint8x16_t, 128> bitmask128_arr {
    // hi, lo
    combine_u64x2(0ULL, 1ULL <<  0),
    combine_u64x2(0ULL, 1ULL <<  1),
    combine_u64x2(0ULL, 1ULL <<  2),
    combine_u64x2(0ULL, 1ULL <<  3),
    combine_u64x2(0ULL, 1ULL <<  4),
    combine_u64x2(0ULL, 1ULL <<  5),
    combine_u64x2(0ULL, 1ULL <<  6),
    combine_u64x2(0ULL, 1ULL <<  7),
    combine_u64x2(0ULL, 1ULL <<  8),
    combine_u64x2(0ULL, 1ULL <<  9),
    combine_u64x2(0ULL, 1ULL << 10),
    combine_u64x2(0ULL, 1ULL << 11),
    combine_u64x2(0ULL, 1ULL << 12),
    combine_u64x2(0ULL, 1ULL << 13),
    combine_u64x2(0ULL, 1ULL << 14),
    combine_u64x2(0ULL, 1ULL << 15),
    combine_u64x2(0ULL, 1ULL << 16),
    combine_u64x2(0ULL, 1ULL << 17),
    combine_u64x2(0ULL, 1ULL << 18),
    combine_u64x2(0ULL, 1ULL << 19),
    combine_u64x2(0ULL, 1ULL << 20),
    combine_u64x2(0ULL, 1ULL << 21),
    combine_u64x2(0ULL, 1ULL << 22),
    combine_u64x2(0ULL, 1ULL << 23),
    combine_u64x2(0ULL, 1ULL << 24),
    combine_u64x2(0ULL, 1ULL << 25),
    combine_u64x2(0ULL, 1ULL << 26),
    combine_u64x2(0ULL, 1ULL << 27),
    combine_u64x2(0ULL, 1ULL << 28),
    combine_u64x2(0ULL, 1ULL << 29),
    combine_u64x2(0ULL, 1ULL << 30),
    combine_u64x2(0ULL, 1ULL << 31),
    combine_u64x2(0ULL, 1ULL << 32),
    combine_u64x2(0ULL, 1ULL << 33),
    combine_u64x2(0ULL, 1ULL << 34),
    combine_u64x2(0ULL, 1ULL << 35),
    combine_u64x2(0ULL, 1ULL << 36),
    combine_u64x2(0ULL, 1ULL << 37),
    combine_u64x2(0ULL, 1ULL << 38),
    combine_u64x2(0ULL, 1ULL << 39),
    combine_u64x2(0ULL, 1ULL << 40),
    combine_u64x2(0ULL, 1ULL << 41),
    combine_u64x2(0ULL, 1ULL << 42),
    combine_u64x2(0ULL, 1ULL << 43),
    combine_u64x2(0ULL, 1ULL << 44),
    combine_u64x2(0ULL, 1ULL << 45),
    combine_u64x2(0ULL, 1ULL << 46),
    combine_u64x2(0ULL, 1ULL << 47),
    combine_u64x2(0ULL, 1ULL << 48),
    combine_u64x2(0ULL, 1ULL << 49),
    combine_u64x2(0ULL, 1ULL << 50),
    combine_u64x2(0ULL, 1ULL << 51),
    combine_u64x2(0ULL, 1ULL << 52),
    combine_u64x2(0ULL, 1ULL << 53),
    combine_u64x2(0ULL, 1ULL << 54),
    combine_u64x2(0ULL, 1ULL << 55),
    combine_u64x2(0ULL, 1ULL << 56),
    combine_u64x2(0ULL, 1ULL << 57),
    combine_u64x2(0ULL, 1ULL << 58),
    combine_u64x2(0ULL, 1ULL << 59),
    combine_u64x2(0ULL, 1ULL << 60),
    combine_u64x2(0ULL, 1ULL << 61),
    combine_u64x2(0ULL, 1ULL << 62),
    combine_u64x2(0ULL, 1ULL << 63),
    combine_u64x2(1ULL <<  0, 0ULL),
    combine_u64x2(1ULL <<  1, 0ULL),
    combine_u64x2(1ULL <<  2, 0ULL),
    combine_u64x2(1ULL <<  3, 0ULL),
    combine_u64x2(1ULL <<  4, 0ULL),
    combine_u64x2(1ULL <<  5, 0ULL),
    combine_u64x2(1ULL <<  6, 0ULL),
    combine_u64x2(1ULL <<  7, 0ULL),
    combine_u64x2(1ULL <<  8, 0ULL),
    combine_u64x2(1ULL <<  9, 0ULL),
    combine_u64x2(1ULL << 10, 0ULL),
    combine_u64x2(1ULL << 11, 0ULL),
    combine_u64x2(1ULL << 12, 0ULL),
    combine_u64x2(1ULL << 13, 0ULL),
    combine_u64x2(1ULL << 14, 0ULL),
    combine_u64x2(1ULL << 15, 0ULL),
    combine_u64x2(1ULL << 16, 0ULL),
    combine_u64x2(1ULL << 17, 0ULL),
    combine_u64x2(1ULL << 18, 0ULL),
    combine_u64x2(1ULL << 19, 0ULL),
    combine_u64x2(1ULL << 20, 0ULL),
    combine_u64x2(1ULL << 21, 0ULL),
    combine_u64x2(1ULL << 22, 0ULL),
    combine_u64x2(1ULL << 23, 0ULL),
    combine_u64x2(1ULL << 24, 0ULL),
    combine_u64x2(1ULL << 25, 0ULL),
    combine_u64x2(1ULL << 26, 0ULL),
    combine_u64x2(1ULL << 27, 0ULL),
    combine_u64x2(1ULL << 28, 0ULL),
    combine_u64x2(1ULL << 29, 0ULL),
    combine_u64x2(1ULL << 30, 0ULL),
    combine_u64x2(1ULL << 31, 0ULL),
    combine_u64x2(1ULL << 32, 0ULL),
    combine_u64x2(1ULL << 33, 0ULL),
    combine_u64x2(1ULL << 34, 0ULL),
    combine_u64x2(1ULL << 35, 0ULL),
    combine_u64x2(1ULL << 36, 0ULL),
    combine_u64x2(1ULL << 37, 0ULL),
    combine_u64x2(1ULL << 38, 0ULL),
    combine_u64x2(1ULL << 39, 0ULL),
    combine_u64x2(1ULL << 40, 0ULL),
    combine_u64x2(1ULL << 41, 0ULL),
    combine_u64x2(1ULL << 42, 0ULL),
    combine_u64x2(1ULL << 43, 0ULL),
    combine_u64x2(1ULL << 44, 0ULL),
    combine_u64x2(1ULL << 45, 0ULL),
    combine_u64x2(1ULL << 46, 0ULL),
    combine_u64x2(1ULL << 47, 0ULL),
    combine_u64x2(1ULL << 48, 0ULL),
    combine_u64x2(1ULL << 49, 0ULL),
    combine_u64x2(1ULL << 50, 0ULL),
    combine_u64x2(1ULL << 51, 0ULL),
    combine_u64x2(1ULL << 52, 0ULL),
    combine_u64x2(1ULL << 53, 0ULL),
    combine_u64x2(1ULL << 54, 0ULL),
    combine_u64x2(1ULL << 55, 0ULL),
    combine_u64x2(1ULL << 56, 0ULL),
    combine_u64x2(1ULL << 57, 0ULL),
    combine_u64x2(1ULL << 58, 0ULL),
    combine_u64x2(1ULL << 59, 0ULL),
    combine_u64x2(1ULL << 60, 0ULL),
    combine_u64x2(1ULL << 61, 0ULL),
    combine_u64x2(1ULL << 62, 0ULL),
    combine_u64x2(1ULL << 63, 0ULL),
};

#pragma GCC diagnostic pop
