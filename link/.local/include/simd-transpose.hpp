// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Transpose an array of 128-bit integer vectors (treating it as a square matrix of integers)
/**
* \file
* \author Steven Ward
*/

#pragma once

#if defined(__x86_64__) && defined(__SSE2__)

#include "simd-transpose.x86.hpp"

#elif defined(__aarch64__) && defined(__ARM_NEON)

#include "simd-transpose.arm.hpp"

#else

#error "Architecture not supported"

#endif
