// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Read Time-Stamp Counter
/**
\file
\author Steven Ward
\sa https://en.wikipedia.org/wiki/Time_Stamp_Counter
*/

#pragma once

#include <concepts>
#include <immintrin.h>

template <std::unsigned_integral T>
T
rdtsc(const T time_0 = 0)
{
    // enforce integers of size 32-bit or 64-bit
    static_assert((sizeof(T) == 4) || (sizeof(T) == 8));

    T time_1 = 0;

    // XXX: GCC should optimize the 32-bit cast but does not.
    // Bug 92180 - Missed optimization on casting __builtin_ia32_rdtsc result to int32
    // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92180

    _mm_lfence();
    do
    {
        time_1 = static_cast<T>(__builtin_ia32_rdtsc());
    }
    while ((time_1 == 0) || (time_1 == time_0));
    _mm_lfence();

    return time_1;
}
