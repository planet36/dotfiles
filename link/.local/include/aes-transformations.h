// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// AES Transformations, Isolated
/**
\file
\author Steven Ward
\sa https://www.intel.com/content/dam/doc/white-paper/advanced-encryption-standard-new-instructions-set-paper.pdf


Adapted from
https://www.intel.com/content/dam/doc/white-paper/advanced-encryption-standard-new-instructions-set-paper.pdf
"Intel® Advanced Encryption Standard (AES) New Instructions Set"

Page 16

The Four AES Round Instructions

"""
AESENC, AESENCLAST, AESDEC, AESDECLAST are defined by the pseudo code in the
following figures (“xmm1” and “xmm2” are aliases to any two xmm
registers). These instructions perform a grouped sequence of transformations of
the AES encryption/decryption flows (in fact, they perform the longest sequence
possible, without introducing a branch in an instruction).
"""


Figure 9. The AESENC and AESENCLAST Instructions

AESENC xmm1, xmm2/m128                 AESENCLAST xmm1, xmm2/m128
Tmp := xmm1                            Tmp := xmm1
Round Key := xmm2/m128                 Round Key := xmm2/m128
Tmp := ShiftRows (Tmp)                 Tmp := Shift Rows (Tmp)
Tmp := SubBytes (Tmp)                  Tmp := SubBytes (Tmp)
Tmp := MixColumns (Tmp)
xmm1 := Tmp xor Round Key              xmm1 := Tmp xor Round Key


Figure 10. The AESDEC and AESDECLAST Instructions

AESDEC xmm1, xmm2/m128                 AESDECLAST xmm1, xmm2/m128
Tmp := xmm1                            Tmp := xmm1
Round Key := xmm2/m128                 Round Key := xmm2/m128
Tmp := InvShift Rows (Tmp)             Tmp := InvShift Rows (Tmp)
Tmp := InvSubBytes (Tmp)               Tmp := InvSubBytes (Tmp)
Tmp := InvMixColumns (Tmp)
xmm1 := Tmp xor Round Key              xmm1:= Tmp xor Round Key


Page 34

"""
In particular, the AES transformations can be useful building blocks for hash functions.
For example, the use the MixColumns transformation provides rapid diffusion and the
AES S-box is a good nonlinear mixer. Operating on large block sizes could be useful in
constructing hash functions with a long digest size.
"""

Figure 31. Isolating the AES Transformations with Combinations of AES Instructions

Figure 32. Isolating the AES Transformations (C Code)

*/

#pragma once

#include <immintrin.h>

/**
\verbatim
_mm_xor_si128
\endverbatim
*/
inline __m128i
AddRoundKey(__m128i data, __m128i key)
{
	data = _mm_xor_si128(data, key);
	return data;
}

/**
\verbatim
PSHUFB xmm0, 0x0b06010c07020d08030e09040f0a0500
\endverbatim
*/
inline __m128i
ShiftRows(__m128i data)
{
	const __m128i ISOLATE_SROWS_MASK = _mm_set_epi32(0x0b06010c, 0x07020d08, 0x030e0904, 0x0f0a0500);
	data = _mm_shuffle_epi8(data, ISOLATE_SROWS_MASK);
	return data;
}

/**
\verbatim
PSHUFB xmm0, 0x0306090c0f0205080b0e0104070a0d00
\endverbatim
*/
inline __m128i
InvShiftRows(__m128i data)
{
	const __m128i ISOLATE_SBOX_MASK = _mm_set_epi32(0x0306090c, 0x0f020508, 0x0b0e0104, 0x070a0d00);
	data = _mm_shuffle_epi8(data, ISOLATE_SBOX_MASK);
	return data;
}

/**
\verbatim
AESDECLAST xmm0, 0x00000000000000000000000000000000
AESENC xmm0, 0x00000000000000000000000000000000
\endverbatim
*/
inline __m128i
MixColumns(__m128i data)
{
	const __m128i ZERO = _mm_setzero_si128();
	data = _mm_aesdeclast_si128(data, ZERO);
	data = _mm_aesenc_si128(data, ZERO);
	return data;
}

/**
\verbatim
AESENCLAST xmm0, 0x00000000000000000000000000000000
AESDEC xmm0, 0x00000000000000000000000000000000
\endverbatim
*/
inline __m128i
InvMixColumns(__m128i data)
{
	// the performance of these two is practically identical
#if 0
	const __m128i ZERO = _mm_setzero_si128(); // Latency = 1; Throughput (CPI) = 0.333...
	data = _mm_aesenclast_si128(data, ZERO); // Latency = 3; Throughput (CPI) = 0.5
	data = _mm_aesdec_si128(data, ZERO); // Latency = 3; Throughput (CPI) = 0.5
#else
	data = _mm_aesimc_si128(data); // Latency = 6; Throughput (CPI) = 1
#endif
	return data;
}

/**
\verbatim
PSHUFB xmm0, 0x0306090c0f0205080b0e0104070a0d00
AESENCLAST xmm0, 0x00000000000000000000000000000000
\endverbatim
*/
inline __m128i
SubBytes(__m128i data)
{
	const __m128i ZERO = _mm_setzero_si128();
	const __m128i ISOLATE_SBOX_MASK = _mm_set_epi32(0x0306090c, 0x0f020508, 0x0b0e0104, 0x070a0d00);
	data = _mm_shuffle_epi8(data, ISOLATE_SBOX_MASK);
	data = _mm_aesenclast_si128(data, ZERO);
	return data;
}

/**
\verbatim
PSHUFB xmm0, 0x0b06010c07020d08030e09040f0a0500
AESDECLAST xmm0, 0x00000000000000000000000000000000
\endverbatim
*/
inline __m128i
InvSubBytes(__m128i data)
{
	const __m128i ZERO = _mm_setzero_si128();
	const __m128i ISOLATE_SROWS_MASK = _mm_set_epi32(0x0b06010c, 0x07020d08, 0x030e0904, 0x0f0a0500);
	data = _mm_shuffle_epi8(data, ISOLATE_SROWS_MASK);
	data = _mm_aesdeclast_si128(data, ZERO);
	return data;
}
