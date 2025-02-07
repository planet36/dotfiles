// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// AES-128 utilities
/**
\file
\author Steven Ward
\sa https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197-upd1.pdf
\sa https://www.intel.com/content/dam/doc/white-paper/advanced-encryption-standard-new-instructions-set-paper.pdf
\sa https://doi.org/10.1007/978-3-662-60769-5
"The Design of Rijndael: The Advanced Encryption Standard (AES), Second Edition"
> Two rounds of Rijndael provide 'full diffusion' in the following sense:
> every state bit depends on all state bits two rounds ago, or a change in
> one state bit is likely to affect half of the state bits after two rounds.
\sa https://crypto.stackexchange.com/questions/44532/how-2-rounds-in-aes-achieve-full-diffusion
*/

#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <immintrin.h>
#include <utility>

inline bool
equal_m128i(const __m128i& a, const __m128i& b)
{
	return std::memcmp(&a, &b, sizeof(__m128i)) == 0;
}

inline bool
equal_m256i(const __m256i& a, const __m256i& b)
{
	return std::memcmp(&a, &b, sizeof(__m256i)) == 0;
}

inline bool
equal_m512i(const __m512i& a, const __m512i& b)
{
	return std::memcmp(&a, &b, sizeof(__m512i)) == 0;
}

/// Get the next AES round constant
/**
\sa https://en.wikipedia.org/wiki/AES_key_schedule#Round_constants
\sa https://engineering.purdue.edu/kak/compsec/NewLectures/Lecture8.pdf
\sa https://crypto.stackexchange.com/a/2420/110486
*/
inline uint8_t
aes_next_rcon(uint8_t rcon_i, const uint8_t i)
{
	if (i == 1)
		rcon_i = 1;
	else
	{
		// get the most significant bit before shifting
		const bool msb = rcon_i & 0b10000000;
		rcon_i = static_cast<decltype(rcon_i)>(rcon_i << 1);
		if (msb)
			rcon_i ^= 0b00011011;
	}

	return rcon_i;
}

/// Do \c _mm_aeskeygenassist_si128 with the key \a key for round number \a round
inline __m128i
aes_keygenassist_round(const __m128i key, const unsigned int round)
{
	// the last argument of _mm_aeskeygenassist_si128 must be an 8-bit immediate

	// inspired by
	// https://github.com/Legrandin/pycryptodome/blob/master/src/AESNI.c#L70

	//switch (round % 51)
	switch ((round - 1) % 51 + 1)
	{
	case  1: return _mm_aeskeygenassist_si128(key, 0x01);
	case  2: return _mm_aeskeygenassist_si128(key, 0x02);
	case  3: return _mm_aeskeygenassist_si128(key, 0x04);
	case  4: return _mm_aeskeygenassist_si128(key, 0x08);
	case  5: return _mm_aeskeygenassist_si128(key, 0x10);
	case  6: return _mm_aeskeygenassist_si128(key, 0x20);
	case  7: return _mm_aeskeygenassist_si128(key, 0x40);
	case  8: return _mm_aeskeygenassist_si128(key, 0x80);
	case  9: return _mm_aeskeygenassist_si128(key, 0x1b);
	case 10: return _mm_aeskeygenassist_si128(key, 0x36);
	case 11: return _mm_aeskeygenassist_si128(key, 0x6c);
	case 12: return _mm_aeskeygenassist_si128(key, 0xd8);
	case 13: return _mm_aeskeygenassist_si128(key, 0xab);
	case 14: return _mm_aeskeygenassist_si128(key, 0x4d);
	case 15: return _mm_aeskeygenassist_si128(key, 0x9a);
	case 16: return _mm_aeskeygenassist_si128(key, 0x2f);
	case 17: return _mm_aeskeygenassist_si128(key, 0x5e);
	case 18: return _mm_aeskeygenassist_si128(key, 0xbc);
	case 19: return _mm_aeskeygenassist_si128(key, 0x63);
	case 20: return _mm_aeskeygenassist_si128(key, 0xc6);
	case 21: return _mm_aeskeygenassist_si128(key, 0x97);
	case 22: return _mm_aeskeygenassist_si128(key, 0x35);
	case 23: return _mm_aeskeygenassist_si128(key, 0x6a);
	case 24: return _mm_aeskeygenassist_si128(key, 0xd4);
	case 25: return _mm_aeskeygenassist_si128(key, 0xb3);
	case 26: return _mm_aeskeygenassist_si128(key, 0x7d);
	case 27: return _mm_aeskeygenassist_si128(key, 0xfa);
	case 28: return _mm_aeskeygenassist_si128(key, 0xef);
	case 29: return _mm_aeskeygenassist_si128(key, 0xc5);
	case 30: return _mm_aeskeygenassist_si128(key, 0x91);
	case 31: return _mm_aeskeygenassist_si128(key, 0x39);
	case 32: return _mm_aeskeygenassist_si128(key, 0x72);
	case 33: return _mm_aeskeygenassist_si128(key, 0xe4);
	case 34: return _mm_aeskeygenassist_si128(key, 0xd3);
	case 35: return _mm_aeskeygenassist_si128(key, 0xbd);
	case 36: return _mm_aeskeygenassist_si128(key, 0x61);
	case 37: return _mm_aeskeygenassist_si128(key, 0xc2);
	case 38: return _mm_aeskeygenassist_si128(key, 0x9f);
	case 39: return _mm_aeskeygenassist_si128(key, 0x25);
	case 40: return _mm_aeskeygenassist_si128(key, 0x4a);
	case 41: return _mm_aeskeygenassist_si128(key, 0x94);
	case 42: return _mm_aeskeygenassist_si128(key, 0x33);
	case 43: return _mm_aeskeygenassist_si128(key, 0x66);
	case 44: return _mm_aeskeygenassist_si128(key, 0xcc);
	case 45: return _mm_aeskeygenassist_si128(key, 0x83);
	case 46: return _mm_aeskeygenassist_si128(key, 0x1d);
	case 47: return _mm_aeskeygenassist_si128(key, 0x3a);
	case 48: return _mm_aeskeygenassist_si128(key, 0x74);
	case 49: return _mm_aeskeygenassist_si128(key, 0xe8);
	case 50: return _mm_aeskeygenassist_si128(key, 0xcb);
	case 51: return _mm_aeskeygenassist_si128(key, 0x8d);
	default: /*std::unreachable();*/ break;
	//default: return {}; break; // unreachable
	}
	std::unreachable();
}

constexpr unsigned int aes128_num_rounds = 10;
constexpr unsigned int aes192_num_rounds = 12;
constexpr unsigned int aes256_num_rounds = 14;

/**
\pre \a tmp is the result of \c _mm_aeskeygenassist_si128
*/
inline __m128i
aes128_expand_key(__m128i key, __m128i tmp)
{
	// get the most significant element (3)
	const int e3 = _mm_extract_epi32(tmp, 3);
	// copy the most significant element (3) to all elements (0, 1, 2, 3)
	tmp = _mm_set1_epi32(e3);

	// inspired by
	// https://github.com/Tarsnap/tarsnap/blob/master/libcperciva/crypto/crypto_aes_aesni.c#L28
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 8));

	return _mm_xor_si128(key, tmp);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
/**
\pre <code>round_keys_enc[0]</code> has the cipher key
*/
template <size_t Nk>
requires (Nk >= 2)
void
aes128_gen_round_keys_enc(std::array<__m128i, Nk>& round_keys_enc)
{
	for (unsigned int round = 1; round < Nk; ++round)
	{
		const __m128i tmp = aes_keygenassist_round(round_keys_enc[round-1], round);
		round_keys_enc[round] = aes128_expand_key(round_keys_enc[round-1], tmp);
	}
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
/**
\pre \a round_keys_enc have been properly prepared
*/
template <size_t Nk>
requires (Nk >= 2)
void
aes128_gen_round_keys_dec(const std::array<__m128i, Nk>& round_keys_enc,
		std::array<__m128i, Nk>& round_keys_dec)
{
	// See "Intel Advanced Encryption Standard (AES) New Instructions Set"
	// Figure 6. Preparing the Decryption Round Keys
	round_keys_dec[0] = round_keys_enc[Nk-1];
	for (unsigned int round = 1; round < Nk-1; ++round)
	{
		round_keys_dec[round] = _mm_aesimc_si128(round_keys_enc[Nk-1 - round]);
	}
	round_keys_dec[Nk-1] = round_keys_enc[0];
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
/// Do AES-128 encryption
template <size_t Nk>
requires (Nk >= 2)
__m128i
aes128_enc(__m128i data, const std::array<__m128i, Nk>& round_keys_enc)
{
	data = _mm_xor_si128(data, round_keys_enc[0]);
	for (unsigned int round = 1; round < Nk-1; ++round)
	{
		data = _mm_aesenc_si128(data, round_keys_enc[round]);
	}
	data = _mm_aesenclast_si128(data, round_keys_enc[Nk-1]);
	return data;
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
/// Do AES-128 decryption
template <size_t Nk>
requires (Nk >= 2)
__m128i
aes128_dec(__m128i data, const std::array<__m128i, Nk>& round_keys_dec)
{
	data = _mm_xor_si128(data, round_keys_dec[0]);
	for (unsigned int round = 1; round < Nk-1; ++round)
	{
		data = _mm_aesdec_si128(data, round_keys_dec[round]);
	}
	data = _mm_aesdeclast_si128(data, round_keys_dec[Nk-1]);
	return data;
}
#pragma GCC diagnostic pop

/// Wrapper for \c _mm_aesenc_si128
inline auto aesenc(const __m128i a, const __m128i key) { return _mm_aesenc_si128(a, key); }

/// Wrapper for \c _mm_aesdec_si128
inline auto aesdec(const __m128i a, const __m128i key) { return _mm_aesdec_si128(a, key); }

#if defined(__VAES__)

/// Wrapper for \c _mm256_aesenc_epi128
inline auto aesenc(const __m256i a, const __m256i key) { return _mm256_aesenc_epi128(a, key); }

/// Wrapper for \c _mm256_aesdec_epi128
inline auto aesdec(const __m256i a, const __m256i key) { return _mm256_aesdec_epi128(a, key); }

/// Wrapper for \c _mm512_aesenc_epi128
inline auto aesenc(const __m512i a, const __m512i key) { return _mm512_aesenc_epi128(a, key); }

/// Wrapper for \c _mm512_aesdec_epi128
inline auto aesdec(const __m512i a, const __m512i key) { return _mm512_aesdec_epi128(a, key); }

#endif

/// Do \c aesenc \a Nr times on data \a a with key \c 0
/**
\pre \a Nr must be at least \c 1.
\tparam Nr the number of rounds of encryption to perform
*/
template <unsigned int Nr = 3>
requires (Nr >= 1)
inline auto
aes128_enc_permute(__m128i a)
{
	const decltype(a) key{};

	// https://gcc.gnu.org/onlinedocs/gcc/Loop-Specific-Pragmas.html#index-pragma-GCC-unroll-n
#pragma GCC unroll Nr
	for (unsigned int round = 0; round < Nr; ++round)
	{
		a = aesenc(a, key);
	}
	return a;
}

/// Do \c aesdec \a Nr times on data \a a with key \c 0
/**
\pre \a Nr must be at least \c 1.
\tparam Nr the number of rounds of decryption to perform
*/
template <unsigned int Nr = 3>
requires (Nr >= 1)
inline auto
aes128_dec_permute(__m128i a)
{
	const decltype(a) key{};

	// https://gcc.gnu.org/onlinedocs/gcc/Loop-Specific-Pragmas.html#index-pragma-GCC-unroll-n
#pragma GCC unroll Nr
	for (unsigned int round = 0; round < Nr; ++round)
	{
		a = aesdec(a, key);
	}
	return a;
}

/// Davies-Meyer single-block-length compression function that uses AES as the block cipher
/**
\sa https://en.wikipedia.org/wiki/One-way_compression_function#Davies%E2%80%93Meyer
\pre \a Nr must be at least \c 1.
\tparam Nr the number of rounds of encryption to perform
\param H the previous hash value
\param m the block of the message
\return the next hash value
*/
template <unsigned int Nr = 3>
requires (Nr >= 1)
inline auto
aes128_enc_davies_meyer(const __m128i H, const __m128i m)
{
	auto a = H;

	// scramble H Nr-1 times with m as the key
	for (unsigned int round = 1; round < Nr; ++round)
	{
		a = aesenc(a, m);
	}

	// scramble Hʹ 1 time with H as the key
	return aesenc(a, H);
}

/// Davies-Meyer single-block-length compression function that uses AES as the block cipher
/**
\sa https://en.wikipedia.org/wiki/One-way_compression_function#Davies%E2%80%93Meyer
\pre \a Nr must be at least \c 1.
\tparam Nr the number of rounds of decryption to perform
\param H the previous hash value
\param m the block of the message
\return the next hash value
*/
template <unsigned int Nr = 3>
requires (Nr >= 1)
inline auto
aes128_dec_davies_meyer(const __m128i H, const __m128i m)
{
	auto a = H;

	// scramble H Nr-1 times with m as the key
	for (unsigned int round = 1; round < Nr; ++round)
	{
		a = aesdec(a, m);
	}

	// scramble Hʹ 1 time with H as the key
	return aesdec(a, H);
}
