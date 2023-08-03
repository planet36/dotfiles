// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// AES PRNG
/**
\file
\author Steven Ward
\sa https://github.com/dragontamer/AESRand/blob/master/AESRand_Linux/AESRand.cpp
\sa https://www.intel.com/content/dam/doc/white-paper/advanced-encryption-standard-new-instructions-set-paper.pdf
\sa https://www.felixcloutier.com/x86/aesenc
\sa https://www.felixcloutier.com/x86/aesdec
*/

#include "byteprimes.hpp"
#include "def_urbg_class_details.hpp"
#include "simd-types.hpp"

#include <immintrin.h>

struct aesencrand
{
	using state_type = simd128;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(aesencrand)

	result_type next()
	{
		static constexpr simd128 roundKey{.u64{byteprimes[0], byteprimes[1]}};
		s.u64 += roundKey.u64;
		const __m128i penultimate = _mm_aesenc_si128(s.i64, roundKey.i64);
		const __m128i result = _mm_aesenc_si128(penultimate, roundKey.i64);
		return result[0];
	}
};

struct aesdecrand
{
	using state_type = simd128;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(aesdecrand)

	result_type next()
	{
		static constexpr simd128 roundKey{.u64{byteprimes[0], byteprimes[1]}};
		s.u64 += roundKey.u64;
		//const __m128i penultimate = _mm_aesenc_si128(s.i64, roundKey.i64);
		const __m128i penultimate = _mm_aesdec_si128(s.i64, roundKey.i64); // (SDW)
		const __m128i result = _mm_aesdec_si128(penultimate, roundKey.i64);
		return result[0];
	}
};
