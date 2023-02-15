// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Timer macro
/**
\file
\author Steven Ward

The "TIME_THIS" macro creates an anonymous timer object that measures the real
time, user CPU time, and system CPU time elapsed/used during the lifetime of
the timer object.

When the timer object is automatically destroyed, stdout is flushed, the times
(to the nearest hundredth of a second) are printed on a single line (with a
trailing newline) to stderr.
*/

#pragma once

#include "timeval.h"

#include <stdio.h>
#include <sys/resource.h>
#include <time.h>

#ifdef __cplusplus
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wredundant-tags"
#endif

// https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#index-cleanup-variable-attribute
#ifdef __cplusplus
#define TIME_THIS (void)fflush(stdout);                     \
	__attribute__((cleanup(print_timerdata_now_diff)))      \
	const timerdata TOKENPASTE2(_time_this_, __COUNTER__) = \
	timerdata_now()
#else
#define TIME_THIS (void)fflush(stdout);                            \
	__attribute__((cleanup(print_timerdata_now_diff)))             \
	const struct timerdata TOKENPASTE2(_time_this_, __COUNTER__) = \
	timerdata_now()
#endif

// https://stackoverflow.com/a/1597129/1892784
#define TOKENPASTE(x, y)  x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)

#define TIMESPEC_TO_SEC(ts) ((double)(ts).tv_sec + (double)(ts).tv_nsec / 1E9)
#define TIMEVAL_TO_SEC(tv)  ((double)(tv).tv_sec + (double)(tv).tv_usec / 1E6)

struct timerdata
{
	struct timespec rtime; // real
	struct timeval utime; // user
	struct timeval stime; // system
};

static struct timerdata
timerdata_now()
{
	struct timerdata now;
	struct rusage ru;

	// https://pubs.opengroup.org/onlinepubs/9699919799/functions/getrusage.html
	(void)getrusage(RUSAGE_SELF, &ru);
	now.utime = ru.ru_utime;
	now.stime = ru.ru_stime;

	// https://pubs.opengroup.org/onlinepubs/9699919799/functions/clock_gettime.html
	(void)clock_gettime(CLOCK_MONOTONIC_RAW, &now.rtime);

	return now;
}

// https://cgit.freedesktop.org/libbsd/tree/include/bsd/sys/time.h#n92
static void
timespecsub(const struct timespec* t1,
            const struct timespec* t0,
            struct timespec* diff)
{
	diff->tv_sec = t1->tv_sec - t0->tv_sec;
	diff->tv_nsec = t1->tv_nsec - t0->tv_nsec;
	if (diff->tv_nsec < 0)
	{
		diff->tv_sec--;
		diff->tv_nsec += 1000000000L;
	}
}

static void
print_timerdata_now_diff(const struct timerdata* t0)
{
	const struct timerdata t1 = timerdata_now();
	struct timerdata diff;
	timespecsub(&t1.rtime, &t0->rtime, &diff.rtime);
	timevalsub(&t1.utime, &t0->utime, &diff.utime);
	timevalsub(&t1.stime, &t0->stime, &diff.stime);
	(void)fflush(stdout);
	(void)fprintf(stderr, "%.2f  %.2f  %.2f\n",
	        TIMESPEC_TO_SEC(diff.rtime),
	        TIMEVAL_TO_SEC(diff.utime),
	        TIMEVAL_TO_SEC(diff.stime));
}

#ifdef __cplusplus
#pragma GCC diagnostic pop
#endif
