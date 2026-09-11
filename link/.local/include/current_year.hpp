// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// get the current year
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/chrono/c/time
* \sa https://en.cppreference.com/w/c/chrono/localtime
* \sa https://en.cppreference.com/w/cpp/chrono/c/localtime
* \sa https://en.cppreference.com/w/cpp/chrono/c/gmtime
* \sa https://en.cppreference.com/w/c/chrono/gmtime
*/

#pragma once

#include <cerrno>
#include <ctime>
#include <system_error>
// NOLINTNEXTLINE(hicpp-deprecated-headers,modernize-deprecated-headers)
#include <time.h> // gmtime_r, localtime_r, tzset

inline int
current_year_local()
{
    const std::time_t now_time_t = std::time(nullptr);
    tm now_tm{};
    // https://pubs.opengroup.org/onlinepubs/9699919799/functions/tzset.html
    ::tzset();
    // NOTE: localtime_r is not in std::
    if (::localtime_r(&now_time_t, &now_tm) == nullptr)
    {
        throw std::system_error(std::make_error_code(std::errc{errno}), "localtime_r");
    }
    return now_tm.tm_year + 1900;
}

inline int
current_year_utc()
{
    const std::time_t now_time_t = std::time(nullptr);
    tm now_tm{};
    // NOTE: gmtime_r is not in std::
    if (::gmtime_r(&now_time_t, &now_tm) == nullptr)
    {
        throw std::system_error(std::make_error_code(std::errc{errno}), "gmtime_r");
    }
    return now_tm.tm_year + 1900;
}
