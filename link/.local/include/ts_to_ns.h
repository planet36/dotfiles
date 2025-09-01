// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Convert \c timespec to nanoseconds
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <time.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wno-redundant-tags"
#endif

/// Convert \a ts to nanoseconds
/**
* \pre \a ts is non-negative
*
* \sa https://en.cppreference.com/w/c/chrono/timespec
* \c tv_sec is only valid >= 0
* Signed seconds will overflow after approx. 292 years
* > (2**63 - 1) / 1_000_000_000 / 60 / 60 / 24 / 365.2425 = 292.27702462692775
* Unsigned seconds will overflow after approx. 584 years
* > (2**64 - 1) / 1_000_000_000 / 60 / 60 / 24 / 365.2425 = 584.5540492538555
*/
inline static uint64_t
ts_to_ns(const struct timespec* ts)
{ return (uint64_t)ts->tv_sec * UINT64_C(1'000'000'000) + (uint64_t)ts->tv_nsec; }

#ifdef __cplusplus
#pragma GCC diagnostic pop
#endif

#ifdef __cplusplus
} // extern "C"
#endif
