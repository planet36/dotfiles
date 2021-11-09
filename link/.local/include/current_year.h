// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// get the current year
/**
\file
\author Steven Ward
*/

#pragma once

#include <time.h>

static
int current_year_local()
{
	const time_t t = time(NULL);
	// https://en.cppreference.com/w/c/chrono/localtime
	return localtime(&t)->tm_year + 1900;
}

static
int current_year_utc()
{
	const time_t t = time(NULL);
	// https://en.cppreference.com/w/c/chrono/gmtime
	return gmtime(&t)->tm_year + 1900;
}
