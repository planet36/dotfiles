// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

#include <ctype.h>
#include <err.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Not re-entrant
char* escape_char(int ch)
{
	static char buf[32] = {'\0'};
	(void)snprintf(buf, sizeof (buf), isprint(ch) ? "%c" : "%#X", ch);
	return buf;
}

unsigned int strtou(const char* s)
{
	unsigned long i = strtoul(s, NULL, 0);
	if (i > UINT_MAX)
		i = UINT_MAX;
	return (unsigned int)i;
}

int scandir_filter(const struct dirent *dirent)
{
	// Exclude these names
	return strcmp(dirent->d_name, ".") != 0 &&
	       strcmp(dirent->d_name, "..") != 0 &&
	       strcmp(dirent->d_name, "lo") != 0;
}

// {{{ copied from my slstatus
// https://github.com/planet36/slstatus/blob/master/util.c

int
pscanf(const char *path, const char *fmt, ...)
{
	FILE *fp;
	va_list ap;
	int n;

	if (!(fp = fopen(path, "r"))) {
		warn("fopen '%s'", path);
		return -1;
	}
	va_start(ap, fmt);
	n = vfscanf(fp, fmt, ap);
	va_end(ap);
	fclose(fp);

	return (n == EOF) ? -1 : n;
}

double
timespec_to_double(const struct timespec *ts)
{
	return ts->tv_sec + copysign(ts->tv_nsec, ts->tv_sec) / 1E9;
}

struct timeval
milliseconds_to_timeval(unsigned int milliseconds)
{
	return (struct timeval){
		.tv_sec = milliseconds / 1000U,
		.tv_usec = (milliseconds % 1000U) * 1000U,
	};
}

// }}}
