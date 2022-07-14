// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// get the current year
/**
\file
\author Steven Ward
*/

#pragma once

#include <limits.h>
#include <stdio.h>
#include <time.h>

static int
current_year_local()
{
	// https://en.cppreference.com/w/c/chrono/time
	const time_t now_time_t = time(NULL);
	struct tm now_tm = {0};
	// https://pubs.opengroup.org/onlinepubs/9699919799/functions/tzset.html
	tzset();
	// https://en.cppreference.com/w/c/chrono/localtime
	if (localtime_r(&now_time_t, &now_tm) == NULL)
	{
		perror("localtime_r");
		return INT_MIN;
	}
	return now_tm.tm_year + 1900;
}

static int
current_year_utc()
{
	// https://en.cppreference.com/w/c/chrono/time
	const time_t now_time_t = time(NULL);
	struct tm now_tm = {0};
	// https://en.cppreference.com/w/c/chrono/gmtime
	if (gmtime_r(&now_time_t, &now_tm) == NULL)
	{
		perror("gmtime_r");
		return INT_MIN;
	}
	return now_tm.tm_year + 1900;
}
