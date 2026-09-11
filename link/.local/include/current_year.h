// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// get the current year
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/c/chrono/time
* \sa https://en.cppreference.com/w/c/chrono/localtime
* \sa https://en.cppreference.com/w/c/chrono/gmtime
*/

#pragma once

#include <limits.h>
#include <stdio.h>
#include <time.h>

#if defined(__cplusplus)
extern "C" {
#endif

static inline int
current_year_local()
{
    const time_t now_time_t = time(nullptr);
    struct tm now_tm = {};
    // https://pubs.opengroup.org/onlinepubs/9699919799/functions/tzset.html
    tzset();
    if (localtime_r(&now_time_t, &now_tm) == nullptr)
    {
        perror("localtime_r");
        return INT_MIN;
    }
    return now_tm.tm_year + 1900;
}

static inline int
current_year_utc()
{
    const time_t now_time_t = time(nullptr);
    struct tm now_tm = {};
    if (gmtime_r(&now_time_t, &now_tm) == nullptr)
    {
        perror("gmtime_r");
        return INT_MIN;
    }
    return now_tm.tm_year + 1900;
}

#if defined(__cplusplus)
} // extern "C"
#endif
