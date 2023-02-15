// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// timeval utils
/**
\file
\author Steven Ward
\sa https://man7.org/linux/man-pages/man0/sys_time.h.0p.html
*/

#pragma once

#include <sys/time.h>

// copied from my slstatus
// https://github.com/planet36/slstatus/blob/main/util.c
static
struct timeval
msec_to_timeval(unsigned int msec)
{
	return (struct timeval){
	    .tv_sec = msec / 1000U,
	    .tv_usec = (msec % 1000U) * 1000UL,
	};
}

// https://cgit.freedesktop.org/libbsd/tree/include/bsd/sys/time.h#n132
static void
timevalsub(const struct timeval* t1,
           const struct timeval* t0,
           struct timeval* diff)
{
	diff->tv_sec = t1->tv_sec - t0->tv_sec;
	diff->tv_usec = t1->tv_usec - t0->tv_usec;
	if (diff->tv_usec < 0)
	{
		diff->tv_sec--;
		diff->tv_usec += 1000000L;
	}
}