// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

#include <err.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int
strtou(const char* s)
{
	unsigned long i = strtoul(s, NULL, 0);
	if (i > UINT_MAX)
		i = UINT_MAX;
	return (unsigned int)i;
}

void
cleanup_close_file(FILE** fpp)
{
	if (*fpp != NULL)
	{
		if (fclose(*fpp) < 0)
		{
			*fpp = NULL;
			err(EXIT_FAILURE, "fclose");
		}
		*fpp = NULL;
	}
}

// {{{ copied from my slstatus
// https://github.com/planet36/slstatus/blob/main/util.c

int
pscanf(const char* path, const char* fmt, ...)
{
	FILE* fp;
	va_list ap;
	int n;

	fp = fopen(path, "r");
	if (fp == NULL)
	{
		warn("fopen '%s'", path);
		return -1;
	}
	va_start(ap, fmt);
	n = vfscanf(fp, fmt, ap);
	va_end(ap);
	if (fclose(fp) < 0)
	{
		err(EXIT_FAILURE, "fclose");
	}

	return (n == EOF) ? -1 : n;
}

double
timespec_to_sec(const struct timespec* ts)
{
	return (double)ts->tv_sec + copysign((double)ts->tv_nsec, (double)ts->tv_sec) / 1E9;
}

struct timeval
msec_to_timeval(unsigned int msec)
{
	return (struct timeval){
	    .tv_sec = msec / 1000U,
	    .tv_usec = (msec % 1000U) * 1000UL,
	};
}

// }}}

// {{{ copied from my slstatus
// https://github.com/planet36/slstatus/blob/main/components/cpu.c

int
calc_idle(uintmax_t* idle, uintmax_t* sum)
{
	uintmax_t a[6];

	// cpu user nice system idle iowait irq softirq
	if (pscanf("/proc/stat", "%*s %ju %ju %ju %ju %*s %ju %ju",
	           &a[0], &a[1], &a[2], &a[3], &a[4], &a[5]) != 6)
	{
		return -1;
	}

	*idle = a[3];
	*sum = a[0] + a[1] + a[2] + a[3] + a[4] + a[5];

	return 0;
}

// }}}
