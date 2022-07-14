// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// get the current year
/**
\file
\author Steven Ward
*/

#pragma once

#include <ctime>

namespace
{

int
current_year_local()
{
	// https://en.cppreference.com/w/cpp/chrono/c/time
	const std::time_t now_time_t = std::time(nullptr);
	tm now_tm{};
	// https://pubs.opengroup.org/onlinepubs/9699919799/functions/tzset.html
	::tzset();
	// NOTE: localtime_r is not in std::
	// https://en.cppreference.com/w/c/chrono/localtime
	(void)::localtime_r(&now_time_t, &now_tm);
	return now_tm.tm_year + 1900;
}

int
current_year_utc()
{
	// https://en.cppreference.com/w/cpp/chrono/c/time
	const std::time_t now_time_t = std::time(nullptr);
	tm now_tm{};
	// NOTE: gmtime_r is not in std::
	// https://en.cppreference.com/w/c/chrono/gmtime
	(void)::gmtime_r(&now_time_t, &now_tm);
	return now_tm.tm_year + 1900;
}

}
