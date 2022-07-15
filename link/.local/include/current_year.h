// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// get the current year
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/c/chrono/time
\sa https://en.cppreference.com/w/c/chrono/localtime
\sa https://en.cppreference.com/w/c/chrono/gmtime
*/

#pragma once

#ifdef DEBUG
#include <limits.h>
#include <stdio.h>
#endif
#include <time.h>

static int
current_year_local()
{
	const time_t now_time_t = time(NULL);
#ifdef DEBUG
	struct tm now_tm = {0};
	// https://pubs.opengroup.org/onlinepubs/9699919799/functions/tzset.html
	tzset();
	if (localtime_r(&now_time_t, &now_tm) == NULL)
	{
		perror("localtime_r");
		return INT_MIN;
	}
	return now_tm.tm_year + 1900;
#else
	return localtime(&now_time_t)->tm_year + 1900;
#endif
}

static int
current_year_utc()
{
	const time_t now_time_t = time(NULL);
#ifdef DEBUG
	struct tm now_tm = {0};
	if (gmtime_r(&now_time_t, &now_tm) == NULL)
	{
		perror("gmtime_r");
		return INT_MIN;
	}
	return now_tm.tm_year + 1900;
#else
	return gmtime(&now_time_t)->tm_year + 1900;
#endif
}
