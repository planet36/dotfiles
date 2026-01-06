// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Read Time-Stamp Counter
/**
* \file
* \author Steven Ward
* \sa https://en.wikipedia.org/wiki/Time_Stamp_Counter
* \sa https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html
*
* Intel® 64 and IA-32 Architectures
* Software Developer’s Manual
* Combined Volumes:
* 1, 2A, 2B, 2C, 2D, 3A, 3B, 3C, 3D, and 4
* March 2025
*
*
* Vol. 1 5-38 (page 152)
*
* RDTSC Read time stamp counter.
* RDTSCP Read time stamp counter and processor ID.
*
*
* Vol. 2B 4-557 (page 1782)
*
* The processor monotonically increments the time-stamp counter MSR every clock cycle and resets
* it to 0 whenever the processor is reset.
*
* The RDTSCP instruction is not a serializing instruction, but it does wait until all previous
* instructions have executed and all previous loads are globally visible. But it does not wait for
* previous stores to be globally visible, and subsequent instructions may begin execution before
* the read operation is performed. The following items may guide software seeking to order
* executions of RDTSCP:
*   • If software requires RDTSCP to be executed only after all previous stores are globally
*   visible, it can execute MFENCE immediately before RDTSCP.
*   • If software requires RDTSCP to be executed prior to execution of any subsequent instruction
*   (including any memory accesses), it can execute LFENCE immediately after RDTSCP.
*
*
* Vol. 2B 4-559 (page 1784)
*
* The processor monotonically increments the time-stamp counter MSR every clock cycle and resets
* it to 0 whenever the processor is reset.
*
* The RDTSC instruction is not a serializing instruction. It does not necessarily wait until all
* previous instructions have been executed before reading the counter. Similarly, subsequent
* instructions may begin execution before the read operation is performed. The following items may
* guide software seeking to order executions of RDTSC:
*   • If software requires RDTSC to be executed only after all previous instructions have executed
*   and all previous loads are globally visible,1 it can execute LFENCE immediately before RDTSC.
*   • If software requires RDTSC to be executed only after all previous instructions have executed
*   and all previous loads and stores are globally visible, it can execute the sequence
*   MFENCE;LFENCE immediately before RDTSC.
*   • If software requires RDTSC to be executed prior to execution of any subsequent instruction
*   (including any memory accesses), it can execute the sequence LFENCE immediately after RDTSC.
*
*
* Vol 3B 19-43 (page 3754)
*
* The RDTSC instruction reads the time-stamp counter and is guaranteed to return a monotonically
* increasing unique value whenever executed, except for a 64-bit counter wraparound. Intel
* guarantees that the time-stamp counter will not wraparound within 10 years after being
* reset. The period for counter wrap is longer for Pentium 4, Intel Xeon, P6 family, and Pentium
* processors.
*
* The RDTSC instruction is not serializing or ordered with other instructions. It does not
* necessarily wait until all previous instructions have been executed before reading the
* counter. Similarly, subsequent instructions may begin execution before the RDTSC instruction
* operation is performed.
*
* Processors based on Nehalem microarchitecture provide an auxiliary TSC register, IA32_TSC_AUX
* that is designed to be used in conjunction with IA32_TSC. IA32_TSC_AUX provides a 32-bit field
* that is initialized by privileged software with a signature value (for example, a logical
* processor ID).
*
* The primary usage of IA32_TSC_AUX in conjunction with IA32_TSC is to allow software to read the
* 64-bit time stamp in IA32_TSC and signature value in IA32_TSC_AUX with the instruction RDTSCP in
* an atomic operation. RDTSCP returns the 64-bit time stamp in EDX:EAX and the 32-bit TSC_AUX
* signature value in ECX. The atomicity of RDTSCP ensures that no context switch can occur between
* the reads of the TSC and TSC_AUX values.
*
* User mode software can use RDTSCP to detect if CPU migration has occurred between successive
* reads of the TSC. It can also be used to adjust for per-CPU differences in TSC values in a NUMA
* system.
*
*/

#pragma once

#include <cstdint>
#include <immintrin.h>

static inline uint64_t
rdtsc()
{
    _mm_mfence();
    _mm_lfence();
    const uint64_t tsc = __rdtsc();
    _mm_lfence();
    return tsc;
}

static inline uint64_t
rdtscp(unsigned int* aux)
{
    _mm_mfence();
    const uint64_t tsc = __rdtscp(aux);
    _mm_lfence();
    return tsc;
}

static inline uint64_t
rdtscp()
{
    unsigned int aux;
    return rdtscp(&aux);
}
