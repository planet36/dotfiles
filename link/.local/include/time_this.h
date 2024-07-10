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

#include "timespec.h"
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
#define TIME_THIS                                                      \
	(void)fflush(stdout);                                              \
	__attribute__((cleanup(print_timerdata_now_diff))) const timerdata \
	TOKENPASTE2(_time_this_, __COUNTER__) = timerdata_now()
#else
#define TIME_THIS                                                             \
	(void)fflush(stdout);                                                     \
	__attribute__((cleanup(print_timerdata_now_diff))) const struct timerdata \
	TOKENPASTE2(_time_this_, __COUNTER__) = timerdata_now()
#endif

// https://stackoverflow.com/a/1597129/1892784
#define TOKENPASTE(x, y)  x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)

struct timerdata
{
#ifdef __cplusplus
	timespec rtime{}; // real
	timeval utime{};  // user
	timeval stime{};  // system
#else
	struct timespec rtime; // real
	struct timeval utime;  // user
	struct timeval stime;  // system
#endif
};

#ifdef __cplusplus
static timerdata
#else
static struct timerdata
#endif
timerdata_now()
{
#ifdef __cplusplus
	timerdata now{};
	rusage ru{};
#else
	struct timerdata now = {0};
	struct rusage ru = {0};
#endif

	// https://pubs.opengroup.org/onlinepubs/9699919799/functions/getrusage.html
	(void)getrusage(RUSAGE_SELF, &ru);
	now.utime = ru.ru_utime;
	now.stime = ru.ru_stime;

	// https://pubs.opengroup.org/onlinepubs/9699919799/functions/clock_gettime.html
	(void)clock_gettime(CLOCK_MONOTONIC_RAW, &now.rtime);

	return now;
}

static void
#ifdef __cplusplus
print_timerdata_now_diff(const timerdata* t0)
#else
print_timerdata_now_diff(const struct timerdata* t0)
#endif
{
#ifdef __cplusplus
	const timerdata t1 = timerdata_now();
	timerdata diff{};
#else
	const struct timerdata t1 = timerdata_now();
	struct timerdata diff = {0};
#endif
	timespecsub(&t1.rtime, &t0->rtime, &diff.rtime);
	timevalsub(&t1.utime, &t0->utime, &diff.utime);
	timevalsub(&t1.stime, &t0->stime, &diff.stime);
	(void)fflush(stdout);
	(void)fprintf(stderr, "%.2f  %.2f  %.2f\n", timespec_to_sec(&diff.rtime),
	              timeval_to_sec(&diff.utime), timeval_to_sec(&diff.stime));
}

#ifdef __cplusplus
#pragma GCC diagnostic pop
#endif
