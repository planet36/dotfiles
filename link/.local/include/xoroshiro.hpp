// SPDX-FileCopyrightText: David Blackman
// SPDX-FileCopyrightText: Sebastiano Vigna (vigna@acm.org)
// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: CC0-1.0

/// xoroshiro PRNG
/**
\file
\author Steven Ward
\sa https://prng.di.unimi.it/
\sa https://vigna.di.unimi.it/ftp/papers/ScrambledLinear.pdf
*/

#pragma once

#include "bytes.hpp"
#include "fill_rand.hpp"

#include <array>
#include <bit>
#include <cstdint>
#include <limits>
#include <type_traits>

// https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator
#define NAMED_REQ_URBG(RESULT_TYPE)                     \
	using result_type = RESULT_TYPE;                    \
	static_assert(std::is_unsigned_v<result_type>);     \
	static constexpr result_type min()                  \
	{                                                   \
		return std::numeric_limits<result_type>::min(); \
	}                                                   \
	static constexpr result_type max()                  \
	{                                                   \
		return std::numeric_limits<result_type>::max(); \
	}                                                   \
	result_type operator()() { return next(); }

#define DEF_CTORS(CLASS_NAME) \
	CLASS_NAME() { seed(); } \
	CLASS_NAME(const state_type& new_s) { seed(new_s); } \
	CLASS_NAME(const seed_bytes_type& bytes) { seed(bytes); }

#define DEF_SEEDS \
	void seed() { fill_rand(s); } \
	void seed(const state_type& new_s) { s = new_s; } \
	void seed(const seed_bytes_type& bytes) { s = bytes_to_datum<state_type>(bytes); }

#define DEF_SEEDS_NONZERO \
	void seed() { fill_rand(s); while (s == state_type{}) [[unlikely]] { fill_rand(s); } } \
	void seed(const state_type& new_s) { s = new_s; } \
	void seed(const seed_bytes_type& bytes) { s = bytes_to_datum<state_type>(bytes); }

#define DEF_JUMP                                                     \
	void jump()                                                      \
	{                                                                \
		state_type new_s;                                            \
		new_s.fill(0);                                               \
		for (const auto x : JUMP)                                    \
		{                                                            \
			for (int b = 0; b < std::numeric_limits<T>::digits; b++) \
			{                                                        \
				if (x & (T{1} << b))                                 \
					for (size_t i = 0; i < s.size(); i++)            \
					{                                                \
						new_s[i] ^= s[i];                            \
					}                                                \
				(void)next();                                        \
			}                                                        \
		}                                                            \
		s = new_s;                                                   \
	}

#define DEF_LONG_JUMP                                                \
	void long_jump()                                                 \
	{                                                                \
		state_type new_s;                                            \
		new_s.fill(0);                                               \
		for (const auto x : LONG_JUMP)                               \
		{                                                            \
			for (int b = 0; b < std::numeric_limits<T>::digits; b++) \
			{                                                        \
				if (x & (T{1} << b))                                 \
					for (size_t i = 0; i < s.size(); i++)            \
					{                                                \
						new_s[i] ^= s[i];                            \
					}                                                \
				(void)next();                                        \
			}                                                        \
		}                                                            \
		s = new_s;                                                   \
	}

#define DEF_JUMP_2                                                   \
	void jump()                                                      \
	{                                                                \
		state_type new_s;                                            \
		new_s.fill(0);                                               \
		for (const auto x : JUMP)                                    \
		{                                                            \
			for (int b = 0; b < std::numeric_limits<T>::digits; b++) \
			{                                                        \
				if (x & (T{1} << b))                                 \
					for (size_t i = 0; i < s.size(); i++)            \
					{                                                \
						new_s[i] ^= s[(i + p) % s.size()];           \
					}                                                \
				(void)next();                                        \
			}                                                        \
		}                                                            \
		for (size_t i = 0; i < s.size(); i++)                        \
		{                                                            \
			s[(i + p) % s.size()] = new_s[i];                        \
		}                                                            \
	}

#define DEF_LONG_JUMP_2                                              \
	void long_jump()                                                 \
	{                                                                \
		state_type new_s;                                            \
		new_s.fill(0);                                               \
		for (const auto x : LONG_JUMP)                               \
		{                                                            \
			for (int b = 0; b < std::numeric_limits<T>::digits; b++) \
			{                                                        \
				if (x & (T{1} << b))                                 \
					for (size_t i = 0; i < s.size(); i++)            \
					{                                                \
						new_s[i] ^= s[(i + p) % s.size()];           \
					}                                                \
				(void)next();                                        \
			}                                                        \
		}                                                            \
		for (size_t i = 0; i < s.size(); i++)                        \
		{                                                            \
			s[(i + p) % s.size()] = new_s[i];                        \
		}                                                            \
	}

/** This is xoroshiro64* 1.0, our best and fastest 32-bit small-state generator
 * for 32-bit floating-point numbers. We suggest to use its upper bits for
 * floating-point generation, as it is slightly faster than xoroshiro64**. It
 * passes all tests we are aware of except for linearity tests, as the lowest
 * six bits have low linear complexity, so if low linear complexity is not
 * considered an issue (as it is usually the case) it can be used to generate
 * 32-bit outputs, too.
 *
 * We suggest to use a sign test to extract a random Boolean value, and right
 * shifts to extract subsets of bits.
 *
 * The state must be seeded so that it is not everywhere zero.
 */
struct xoroshiro64star
{
	using T = uint32_t;
	using state_type = std::array<T, 2>;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(T)

private:
	state_type s{};

public:
DEF_CTORS(xoroshiro64star)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto s0 = s[0];
		auto s1 = s[1];
		const auto result = s0 * 0x9E3779BB;

		s1 ^= s0;
		s[0] = std::rotl(s0, 26) ^ s1 ^ (s1 << 9); // a, b
		s[1] = std::rotl(s1, 13); // c

		return result;
	}
};

/** This is xoroshiro64** 1.0, our 32-bit all-purpose, rock-solid, small-state
 * generator. It is extremely fast and it passes all tests we are aware of, but
 * its state space is not large enough for any parallel application.
 *
 * For generating just single-precision (i.e., 32-bit) floating-point numbers,
 * xoroshiro64* is even faster.
 *
 * The state must be seeded so that it is not everywhere zero.
 */
struct xoroshiro64starstar
{
	using T = uint32_t;
	using state_type = std::array<T, 2>;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(T)

private:
	state_type s{};

public:
DEF_CTORS(xoroshiro64starstar)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto s0 = s[0];
		auto s1 = s[1];
		const auto result = std::rotl(s0 * 0x9E3779BB, 5) * 5;

		s1 ^= s0;
		s[0] = std::rotl(s0, 26) ^ s1 ^ (s1 << 9); // a, b
		s[1] = std::rotl(s1, 13); // c

		return result;
	}
};

/** This is xoroshiro128+ 1.0, our best and fastest small-state generator for
 * floating-point numbers. We suggest to use its upper bits for floating-point
 * generation, as it is slightly faster than xoroshiro128++/xoroshiro128**. It
 * passes all tests we are aware of except for the four lower bits, which might
 * fail linearity tests (and just those), so if low linear complexity is not
 * considered an issue (as it is usually the case) it can be used to generate
 * 64-bit outputs, too; moreover, this generator has a very mild Hamming-weight
 * dependency making our test (http://prng.di.unimi.it/hwd.php) fail after 5 TB
 * of output; we believe this slight bias cannot affect any application. If you
 * are concerned, use xoroshiro128++, xoroshiro128** or xoshiro256+.
 *
 * We suggest to use a sign test to extract a random Boolean value, and right
 * shifts to extract subsets of bits.
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 *
 * NOTE: the parameters (a=24, b=16, b=37) of this version give slightly better
 * results in our test than the 2016 version (a=55, b=14, c=36).
 */
struct xoroshiro128plus
{
	using T = uint64_t;
	using state_type = std::array<T, 2>;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(T)

private:
	state_type s{};
	static constexpr state_type JUMP{
	    0xdf900294d8f554a5, 0x170865df4b3201fc};
	static constexpr state_type LONG_JUMP{
	    0xd2a98b26625eee7b, 0xdddf9b1090aa7ac1};

public:
DEF_CTORS(xoroshiro128plus)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto s0 = s[0];
		auto s1 = s[1];
		const auto result = s0 + s1;

		s1 ^= s0;
		s[0] = std::rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
		s[1] = std::rotl(s1, 37); // c

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^64
	 * calls to next(); it can be used to generate 2^64 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^96 calls to next(); it can be used to generate 2^32 starting points,
	 * from each of which jump() will generate 2^32 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP
};

/** This is xoroshiro128++ 1.0, one of our all-purpose, rock-solid, small-state
 * generators. It is extremely (sub-ns) fast and it passes all tests we are
 * aware of, but its state space is large enough only for mild parallelism.
 *
 * For generating just floating-point numbers, xoroshiro128+ is even faster
 * (but it has a very mild bias, see notes in the comments).
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoroshiro128plusplus
{
	using T = uint64_t;
	using state_type = std::array<T, 2>;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(T)

private:
	state_type s{};
	static constexpr state_type JUMP{
	    0x2bd7a6a6e99c2ddc, 0x0992ccaf6a6fca05};
	static constexpr state_type LONG_JUMP{
	    0x360fd5f2cf8d5d99, 0x9c6e6877736c46e3};

public:
DEF_CTORS(xoroshiro128plusplus)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto s0 = s[0];
		auto s1 = s[1];
		const auto result = std::rotl(s0 + s1, 17) + s0;

		s1 ^= s0;
		s[0] = std::rotl(s0, 49) ^ s1 ^ (s1 << 21); // a, b
		s[1] = std::rotl(s1, 28); // c

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^64
	 * calls to next(); it can be used to generate 2^64 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^96 calls to next(); it can be used to generate 2^32 starting points,
	 * from each of which jump() will generate 2^32 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP
};

/** This is xoroshiro128** 1.0, one of our all-purpose, rock-solid, small-state
 * generators. It is extremely (sub-ns) fast and it passes all tests we are
 * aware of, but its state space is large enough only for mild parallelism.
 *
 * For generating just floating-point numbers, xoroshiro128+ is even faster
 * (but it has a very mild bias, see notes in the comments).
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoroshiro128starstar
{
	using T = uint64_t;
	using state_type = std::array<T, 2>;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(T)

private:
	state_type s{};
	static constexpr state_type JUMP{
	    0xdf900294d8f554a5, 0x170865df4b3201fc};
	static constexpr state_type LONG_JUMP{
	    0xd2a98b26625eee7b, 0xdddf9b1090aa7ac1};

public:
DEF_CTORS(xoroshiro128starstar)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto s0 = s[0];
		auto s1 = s[1];
		const auto result = std::rotl(s0 * 5, 7) * 9;

		s1 ^= s0;
		s[0] = std::rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
		s[1] = std::rotl(s1, 37); // c

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^64
	 * calls to next(); it can be used to generate 2^64 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^96 calls to next(); it can be used to generate 2^32 starting points,
	 * from each of which jump() will generate 2^32 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP
};

/** This is xoroshiro1024++ 1.0, one of our all-purpose, rock-solid,
 * large-state generators. It is extremely fast and it passes all tests we are
 * aware of. Its state however is too large--in general, the xoshiro256 family
 * should be preferred.
 *
 * For generating just floating-point numbers, xoroshiro1024* is even faster
 * (but it has a very mild bias, see notes in the comments).
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoroshiro1024plusplus
{
	using T = uint64_t;
	using state_type = std::array<T, 16>;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(T)

private:
	state_type s{};
	unsigned int p{};
	static constexpr state_type JUMP{
	    0x931197d8e3177f17, 0xb59422e0b9138c5f, 0xf06a6afb49d668bb,
	    0xacb8a6412c8a1401, 0x12304ec85f0b3468, 0xb7dfe7079209891e,
	    0x405b7eec77d9eb14, 0x34ead68280c44e4a, 0xe0e4ba3e0ac9e366,
	    0x8f46eda8348905b7, 0x328bf4dbad90d6ff, 0xc8fd6fb31c9effc3,
	    0xe899d452d4b67652, 0x45f387286ade3205, 0x03864f454a8920bd,
	    0xa68fa28725b1b384};
	static constexpr state_type LONG_JUMP{
	    0x7374156360bbf00f, 0x4630c2efa3b3c1f6, 0x6654183a892786b1,
	    0x94f7bfcbfb0f1661, 0x27d8243d3d13eb2d, 0x9701730f3dfb300f,
	    0x2f293baae6f604ad, 0xa661831cb60cd8b6, 0x68280c77d9fe008c,
	    0x50554160f5ba9459, 0x2fc20b17ec7b2a9a, 0x49189bbdc8ec9f8f,
	    0x92a65bca41852cc1, 0xf46820dd0509c12a, 0x52b00c35fbf92185,
	    0x1e5b3b7f589e03c1};

public:
DEF_CTORS(xoroshiro1024plusplus)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto q = p;
		p = (p + 1) % s.size();
		const auto s0 = s[p];
		auto s15 = s[q];
		const auto result = std::rotl(s0 + s15, 23) + s15;

		s15 ^= s0;
		s[q] = std::rotl(s0, 25) ^ s15 ^ (s15 << 27);
		s[p] = std::rotl(s15, 36);

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^512
	 * calls to next(); it can be used to generate 2^512 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP_2

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^768 calls to next(); it can be used to generate 2^256 starting points,
	 * from each of which jump() will generate 2^256 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP_2
};

/** This is xoroshiro1024* 1.0, our large-state generator for floating-point
 * numbers. We suggest to use its upper bits for floating-point generation, as
 * it is slightly faster than xoroshiro1024++/xoroshiro1024**.  Its state
 * however is too large--in general, the xoshiro256 family should be preferred.
 * It is a better replacement for xorshift1024*.
 *
 * It passes all tests we are aware of except for the lowest three bits, which
 * might fail linearity tests (and just those), so if low linear complexity is
 * not considered an issue (as it is usually the case) it can be used to
 * generate 64-bit outputs, too.
 *
 * We suggest to use a sign test to extract a random Boolean value, and right
 * shifts to extract subsets of bits.
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoroshiro1024star
{
	using T = uint64_t;
	using state_type = std::array<T, 16>;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(T)

private:
	state_type s{};
	unsigned int p{};
	static constexpr state_type JUMP{
	    0x931197d8e3177f17, 0xb59422e0b9138c5f, 0xf06a6afb49d668bb,
	    0xacb8a6412c8a1401, 0x12304ec85f0b3468, 0xb7dfe7079209891e,
	    0x405b7eec77d9eb14, 0x34ead68280c44e4a, 0xe0e4ba3e0ac9e366,
	    0x8f46eda8348905b7, 0x328bf4dbad90d6ff, 0xc8fd6fb31c9effc3,
	    0xe899d452d4b67652, 0x45f387286ade3205, 0x03864f454a8920bd,
	    0xa68fa28725b1b384};
	static constexpr state_type LONG_JUMP{
	    0x7374156360bbf00f, 0x4630c2efa3b3c1f6, 0x6654183a892786b1,
	    0x94f7bfcbfb0f1661, 0x27d8243d3d13eb2d, 0x9701730f3dfb300f,
	    0x2f293baae6f604ad, 0xa661831cb60cd8b6, 0x68280c77d9fe008c,
	    0x50554160f5ba9459, 0x2fc20b17ec7b2a9a, 0x49189bbdc8ec9f8f,
	    0x92a65bca41852cc1, 0xf46820dd0509c12a, 0x52b00c35fbf92185,
	    0x1e5b3b7f589e03c1};

public:
DEF_CTORS(xoroshiro1024star)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto q = p;
		p = (p + 1) % s.size();
		const auto s0 = s[p];
		auto s15 = s[q];
		const auto result = s0 * 0x9e3779b97f4a7c13;

		s15 ^= s0;
		s[q] = std::rotl(s0, 25) ^ s15 ^ (s15 << 27);
		s[p] = std::rotl(s15, 36);

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^512
	 * calls to next(); it can be used to generate 2^512 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP_2

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^768 calls to next(); it can be used to generate 2^256 starting points,
	 * from each of which jump() will generate 2^256 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP_2
};

/** This is xoroshiro1024** 1.0, one of our all-purpose, rock-solid,
 * large-state generators. It is extremely fast and it passes all tests we are
 * aware of. Its state however is too large--in general, the xoshiro256 family
 * should be preferred.
 *
 * For generating just floating-point numbers, xoroshiro1024* is even faster
 * (but it has a very mild bias, see notes in the comments).
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoroshiro1024starstar
{
	using T = uint64_t;
	using state_type = std::array<T, 16>;
	using seed_bytes_type = std::array<uint8_t, sizeof(state_type)>;

NAMED_REQ_URBG(T)

private:
	state_type s{};
	unsigned int p{};
	static constexpr state_type JUMP{
	    0x931197d8e3177f17, 0xb59422e0b9138c5f, 0xf06a6afb49d668bb,
	    0xacb8a6412c8a1401, 0x12304ec85f0b3468, 0xb7dfe7079209891e,
	    0x405b7eec77d9eb14, 0x34ead68280c44e4a, 0xe0e4ba3e0ac9e366,
	    0x8f46eda8348905b7, 0x328bf4dbad90d6ff, 0xc8fd6fb31c9effc3,
	    0xe899d452d4b67652, 0x45f387286ade3205, 0x03864f454a8920bd,
	    0xa68fa28725b1b384};
	static constexpr state_type LONG_JUMP{
	    0x7374156360bbf00f, 0x4630c2efa3b3c1f6, 0x6654183a892786b1,
	    0x94f7bfcbfb0f1661, 0x27d8243d3d13eb2d, 0x9701730f3dfb300f,
	    0x2f293baae6f604ad, 0xa661831cb60cd8b6, 0x68280c77d9fe008c,
	    0x50554160f5ba9459, 0x2fc20b17ec7b2a9a, 0x49189bbdc8ec9f8f,
	    0x92a65bca41852cc1, 0xf46820dd0509c12a, 0x52b00c35fbf92185,
	    0x1e5b3b7f589e03c1};

public:
DEF_CTORS(xoroshiro1024starstar)

	// XXX: must not give zero seed
DEF_SEEDS_NONZERO

	result_type next()
	{
		const auto q = p;
		p = (p + 1) % s.size();
		const auto s0 = s[p];
		auto s15 = s[q];
		const auto result = std::rotl(s0 * 5, 7) * 9;

		s15 ^= s0;
		s[q] = std::rotl(s0, 25) ^ s15 ^ (s15 << 27);
		s[p] = std::rotl(s15, 36);

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^512
	 * calls to next(); it can be used to generate 2^512 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP_2

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^768 calls to next(); it can be used to generate 2^256 starting points,
	 * from each of which jump() will generate 2^256 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP_2
};

#undef NAMED_REQ_URBG
#undef DEF_CTORS
#undef DEF_SEEDS
#undef DEF_SEEDS_NONZERO
#undef DEF_JUMP
#undef DEF_LONG_JUMP
#undef DEF_JUMP_2
#undef DEF_LONG_JUMP_2
