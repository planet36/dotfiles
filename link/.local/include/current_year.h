// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// get the current year
/**
\file
\author Steven Ward
*/

#pragma once

#include <time.h>

static int
current_year_local()
{
	// https://en.cppreference.com/w/c/chrono/time
	const time_t now_time_t = time(NULL);
	// https://en.cppreference.com/w/c/chrono/localtime
	struct tm now_tm = *localtime(&now_time_t);
	return now_tm.tm_year + 1900;
}

static int
current_year_utc()
{
	// https://en.cppreference.com/w/c/chrono/time
	const time_t now_time_t = time(NULL);
	// https://en.cppreference.com/w/c/chrono/gmtime
	struct tm now_tm = *gmtime(&now_time_t);
	return now_tm.tm_year + 1900;
}
