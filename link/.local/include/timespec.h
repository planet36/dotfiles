// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// timespec utils
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/c/chrono/timespec
*/

#pragma once

#include <math.h>
#include <time.h>

// copied from my slstatus
// https://github.com/planet36/slstatus/blob/main/util.c

static
double
timespec_to_sec(const struct timespec* ts)
{
	return (double)ts->tv_sec + copysign((double)ts->tv_nsec, (double)ts->tv_sec) / 1E9;
}
