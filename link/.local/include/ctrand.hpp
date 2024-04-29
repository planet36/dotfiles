// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// compile-time pseudo-random number
/**
\file
\author Steven Ward
*/

#pragma once

#include "fnv.hpp"
#include "stringize.h"

// The most mutable information should be given first.
#if defined (_MSC_FULL_VER)
#define SEED_STR ( \
		XSTR(__COUNTER__) \
		__TIME__ \
		XSTR(__LINE__) \
		__DATE__ \
		__TIMESTAMP__ \
		__FILE__ \
		XSTR(_MSC_FULL_VER) \
		)
#else
#define SEED_STR ( \
		XSTR(__COUNTER__) \
		__TIME__ \
		XSTR(__LINE__) \
		__DATE__ \
		__TIMESTAMP__ \
		__FILE__ \
		__VERSION__ \
		)
#endif

#define CTRAND32 fnv1a_32(SEED_STR)
#define CTRAND64 fnv1a_64(SEED_STR)
