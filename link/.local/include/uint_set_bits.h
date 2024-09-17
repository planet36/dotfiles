// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Macro to create low-pass bitmask
/**
\file
\author Steven Ward
*/

#pragma once

#include <limits.h>

#ifdef __cplusplus
extern "C"
{
#endif

static_assert(CHAR_BIT == 8);

#define UINT_SET_BITS(N) \
	(((N) >= 64) ? UINT64_MAX : (UINT64_C(1) << (N)) - UINT64_C(1))
#define UINT_SET_BYTES(N) UINT_SET_BITS((N) * CHAR_BIT)

#ifdef __cplusplus
} // extern "C"
#endif
