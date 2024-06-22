// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Wrappers for SIMD load and store functions
/**
\file
\author Steven Ward
\sa https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html
*/

#pragma once

#include <immintrin.h>

#if defined(__SSE2__)
inline __m128i
to_m128i(const void* mem_addr)
{
	// Instruction: movdqu xmm, m128
	// CPUID Flags: SSE2
	return _mm_loadu_si128((const __m128i*)(mem_addr));
}

inline void
from_m128i(void* mem_addr, const __m128i a)
{
	// Instruction: movdqa m128, xmm
	// CPUID Flags: SSE2
	_mm_store_si128((__m128i*)(mem_addr), a);
}

#endif

#if defined(__AVX__)
inline __m256i
to_m256i(const void* mem_addr)
{
	// Instruction: vmovdqu ymm, m256
	// CPUID Flags: AVX
	return _mm256_loadu_si256((const __m256i*)(mem_addr));
}


inline void
from_m256i(void* mem_addr, const __m256i a)
{
	// Instruction: vmovdqa m256, ymm
	// CPUID Flags: AVX
	_mm256_store_si256((__m256i*)(mem_addr), a);
}

#endif

#if defined(__AVX512F__)
inline __m512i
to_m512i(const void* mem_addr)
{
	// Instruction: vmovdqu32 zmm, m512
	// CPUID Flags: AVX512F
	return _mm512_loadu_si512(mem_addr);
}

inline void
from_m512i(void* mem_addr, const __m512i a)
{
	// Instruction: vmovdqa32 m512, zmm
	// CPUID Flags: AVX512F
	_mm512_store_si512(mem_addr, a);
}
#endif
