// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Transpose an array of 128-bit integer vectors (treating it as a square matrix of integers) using ARM Neon intrinsics
/**
* \file
* \author Steven Ward
* \sa https://arm-software.github.io/acle/neon_intrinsics/advsimd.html#zip-elements
* \sa https://arm-software.github.io/acle/neon_intrinsics/advsimd.html#transpose-elements
* \sa https://developer.arm.com/architectures/instruction-sets/intrinsics/#f:@navigationhierarchiessimdisa=[Neon]&f:@navigationhierarchiesreturnbasetype=[uint]&q=vzip
* \sa https://developer.arm.com/architectures/instruction-sets/intrinsics/#f:@navigationhierarchiessimdisa=[Neon]&f:@navigationhierarchiesreturnbasetype=[uint]&q=vtrn
*
* TRN1, TRN2, ZIP1, and ZIP2 have the same latency, throughput, and pipelines.
* https://developer.arm.com/documentation/109824/0002/?lang=en
* "Arm Cortex-A725 Core Software Optimization Guide"
*/

#pragma once

#if defined(__aarch64__) && defined(__ARM_NEON)


#endif
