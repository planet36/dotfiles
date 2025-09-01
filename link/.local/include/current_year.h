// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// get the current year
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/c/chrono/time
* \sa https://en.cppreference.com/w/c/chrono/localtime
* \sa https://en.cppreference.com/w/c/chrono/gmtime
*/

#pragma once

#ifdef DEBUG
#include <limits.h>
#include <stdio.h>
#endif
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

static int
current_year_local()
{
    const time_t now_time_t = time(nullptr);
    struct tm now_tm = {0};
#ifdef DEBUG
    // https://pubs.opengroup.org/onlinepubs/9699919799/functions/tzset.html
    tzset();
    if (localtime_r(&now_time_t, &now_tm) == nullptr)
    {
        perror("localtime_r");
        return INT_MIN;
    }
#else
    return localtime(&now_time_t)->tm_year + 1900;
#endif
    return now_tm.tm_year + 1900;
}

static int
current_year_utc()
{
    const time_t now_time_t = time(nullptr);
    struct tm now_tm = {0};
#ifdef DEBUG
    if (gmtime_r(&now_time_t, &now_tm) == nullptr)
    {
        perror("gmtime_r");
        return INT_MIN;
    }
#else
    now_tm = *gmtime(&now_time_t);
#endif
    return now_tm.tm_year + 1900;
}

#ifdef __cplusplus
} // extern "C"
#endif
