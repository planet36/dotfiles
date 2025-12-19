// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Typedef for a 128-bit SIMD data type
/**
* \file
* \author Steven Ward
*/

#pragma once

#if defined(__x86_64__)

#include <immintrin.h>
typedef __m128i simd128_t;

#elif defined(__aarch64__)

#include <arm_neon.h>
typedef uint8x16_t simd128_t;

#else

#error "Architecture not supported"

#endif
