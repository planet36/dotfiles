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
	// https://en.cppreference.com/w/cpp/chrono/c/localtime
	tm now_tm = *std::localtime(&now_time_t);
	return now_tm.tm_year + 1900;
}

int
current_year_utc()
{
	// https://en.cppreference.com/w/cpp/chrono/c/time
	const std::time_t now_time_t = std::time(nullptr);
	// https://en.cppreference.com/w/cpp/chrono/c/gmtime
	tm now_tm = *std::gmtime(&now_time_t);
	return now_tm.tm_year + 1900;
}

}
