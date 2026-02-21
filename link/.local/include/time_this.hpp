// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Timer macro
/**
* \file
* \author Steven Ward
*
* The "TIME_THIS" macro creates an anonymous timer object that prints its
* lifetime (as measured by a steady clock) upon destruction.
*
* When the timer object goes out of scope, stdout is flushed, the time (to the
* nearest hundredth of a second) is printed (with a trailing newline) to stderr.
*/

#pragma once

#include <chrono>
#include <cstdio>

#define TIME_THIS              \
    (void)std::fflush(stdout); \
    const time_this TOKENPASTE2(_time_this_, __COUNTER__)

// https://stackoverflow.com/a/1597129/1892784
#define TOKENPASTE(x, y)  x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)

struct time_this
{
public:
    // https://cplusplus.com/forum/general/187899/#msg913531
    using timer_clock =
        typename std::conditional_t<std::chrono::high_resolution_clock::is_steady,
                                    std::chrono::high_resolution_clock,
                                    std::chrono::steady_clock>;

    time_this() noexcept : t0(timer_clock::now()) {}

    time_this(const time_this&) = delete;            // copy constructor
    time_this(time_this&&) = delete;                 // move constructor
    time_this& operator=(const time_this&) = delete; // copy assignment
    time_this& operator=(time_this&&) = delete;      // move assignment

    ~time_this()
    {
        const auto t1 = timer_clock::now();
        (void)fflush(stdout);
        (void)fprintf(stderr, "%.2f\n", std::chrono::duration<double>(t1 - t0).count());
    }

private:
    const std::chrono::time_point<timer_clock> t0;
};
