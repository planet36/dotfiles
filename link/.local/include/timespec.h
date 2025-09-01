// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// timespec utils
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/c/chrono/timespec
*/

#pragma once

#include <math.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wredundant-tags"
#endif

// Copied from my slstatus
// https://github.com/planet36/slstatus/blob/main/util.c
static double
timespec_to_sec(const struct timespec* ts)
{
    return (double)ts->tv_sec + copysign((double)ts->tv_nsec, (double)ts->tv_sec) / 1E9;
}

// https://cgit.freedesktop.org/libbsd/tree/include/bsd/sys/time.h#n92
static void
timespecsub(const struct timespec* t1, const struct timespec* t0, struct timespec* diff)
{
    diff->tv_sec = t1->tv_sec - t0->tv_sec;
    diff->tv_nsec = t1->tv_nsec - t0->tv_nsec;
    if (diff->tv_nsec < 0)
    {
        diff->tv_sec--;
        diff->tv_nsec += 1'000'000'000L;
    }
}

#ifdef __cplusplus
#pragma GCC diagnostic pop
#endif

#ifdef __cplusplus
} // extern "C"
#endif
