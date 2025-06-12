// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Read Time-Stamp Counter
/**
\file
\author Steven Ward
\sa https://en.wikipedia.org/wiki/Time_Stamp_Counter
*/

#pragma once

#include <cstdint>
#include <immintrin.h>

uint64_t
rdtsc(const uint64_t time_0 = 0)
{
    uint64_t time_1 = 0;

    // XXX: GCC should optimize the 32-bit cast but does not.
    // Bug 92180 - Missed optimization on casting __builtin_ia32_rdtsc result to int32
    // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92180

    do
    {
        _mm_mfence();
        _mm_lfence();
        time_1 = __builtin_ia32_rdtsc();
        _mm_lfence();
    }
    while (time_1 == time_0);

    return time_1;
}
