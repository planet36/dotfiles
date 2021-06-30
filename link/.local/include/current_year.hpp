// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#pragma once

#include <ctime>

static int current_year_local()
{
	const std::time_t t = std::time(nullptr);
	// https://en.cppreference.com/w/cpp/chrono/c/localtime
	return std::localtime(&t)->tm_year + 1900;
}

static int current_year_utc()
{
	const std::time_t t = std::time(nullptr);
	// https://en.cppreference.com/w/cpp/chrono/c/gmtime
	return std::gmtime(&t)->tm_year + 1900;
}
