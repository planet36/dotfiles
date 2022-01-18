// SPDX-FileCopyrightText: David Blackman
// SPDX-FileCopyrightText: Sebastiano Vigna (vigna@acm.org)
// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: CC0-1.0

/// xoshiro PRNG
/**
\file
\author Steven Ward
\sa https://prng.di.unimi.it/
\sa https://vigna.di.unimi.it/ftp/papers/ScrambledLinear.pdf
*/

#pragma once

#include "fill_rand.hpp"

#include <array>
#include <bit>
#include <cstdint>
#include <limits>
#include <type_traits>

// https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator
#define NAMED_REQ_URBG                                  \
	using result_type = T;                              \
	static_assert(std::is_unsigned_v<result_type>);     \
	static constexpr result_type min()                  \
	{                                                   \
		return std::numeric_limits<result_type>::min(); \
	}                                                   \
	static constexpr result_type max()                  \
	{                                                   \
		return std::numeric_limits<result_type>::max(); \
	}                                                   \
	result_type operator()() {return next();}

#define DEF_JUMP                                                     \
	void jump()                                                      \
	{                                                                \
		decltype(s) new_s;                                           \
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
		decltype(s) new_s;                                           \
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

/** This is xoshiro128+ 1.0, our best and fastest 32-bit generator for 32-bit
 * floating-point numbers. We suggest to use its upper bits for floating-point
 * generation, as it is slightly faster than xoshiro128**.  It passes all tests
 * we are aware of except for linearity tests, as the lowest four bits have low
 * linear complexity, so if low linear complexity is not considered an issue
 * (as it is usually the case) it can be used to generate 32-bit outputs, too.
 *
 * We suggest to use a sign test to extract a random Boolean value, and right
 * shifts to extract subsets of bits.
 *
 * The state must be seeded so that it is not everywhere zero.
 */
struct xoshiro128plus
{
	using T = uint32_t;
	static constexpr size_t state_num_elems = 4;

NAMED_REQ_URBG

private:
	std::array<T, state_num_elems> s;
	static constexpr auto JUMP = std::to_array<T>({0x8764000b, 0xf542d2d3,
			0x6fa035c3, 0x77f2db5b});
	static constexpr auto LONG_JUMP = std::to_array<T>({0xb523952e,
			0x0b6f099f, 0xccf5a0ef, 0x1c580662});

public:
	xoshiro128plus() {fill_rand(s);}
	xoshiro128plus(const decltype(s)& new_s): s(new_s) {}
	void seed(const decltype(s)& new_s) {s = new_s;}

	T next()
	{
		const T result = s[0] + s[3];
		const T t = s[1] << 9;

		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];

		s[2] ^= t;

		s[3] = std::rotl(s[3], 11);

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

/** This is xoshiro128++ 1.0, one of our 32-bit all-purpose, rock-solid
 * generators. It has excellent speed, a state size (128 bits) that is large
 * enough for mild parallelism, and it passes all tests we are aware of.
 *
 * For generating just single-precision (i.e., 32-bit) floating-point numbers,
 * xoshiro128+ is even faster.
 *
 * The state must be seeded so that it is not everywhere zero.
 */
struct xoshiro128plusplus
{
	using T = uint32_t;
	static constexpr size_t state_num_elems = 4;

NAMED_REQ_URBG

private:
	std::array<T, state_num_elems> s;
	static constexpr auto JUMP = std::to_array<T>({0x8764000b, 0xf542d2d3,
			0x6fa035c3, 0x77f2db5b});
	static constexpr auto LONG_JUMP = std::to_array<T>({0xb523952e,
			0x0b6f099f, 0xccf5a0ef, 0x1c580662});

public:
	xoshiro128plusplus() {fill_rand(s);}
	xoshiro128plusplus(const decltype(s)& new_s): s(new_s) {}
	void seed(const decltype(s)& new_s) {s = new_s;}

	T next()
	{
		const T result = std::rotl(s[0] + s[3], 7) + s[0];
		const T t = s[1] << 9;

		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];

		s[2] ^= t;

		s[3] = std::rotl(s[3], 11);

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

/** This is xoshiro128** 1.1, one of our 32-bit all-purpose, rock-solid
 * generators. It has excellent speed, a state size (128 bits) that is large
 * enough for mild parallelism, and it passes all tests we are aware of.
 *
 * Note that version 1.0 had mistakenly s[0] instead of s[1] as state word
 * passed to the scrambler.
 *
 * For generating just single-precision (i.e., 32-bit) floating-point numbers,
 * xoshiro128+ is even faster.
 *
 * The state must be seeded so that it is not everywhere zero.
 */
struct xoshiro128starstar
{
	using T = uint32_t;
	static constexpr size_t state_num_elems = 4;

NAMED_REQ_URBG

private:
	std::array<T, state_num_elems> s;
	static constexpr auto JUMP = std::to_array<T>({0x8764000b, 0xf542d2d3,
			0x6fa035c3, 0x77f2db5b});
	static constexpr auto LONG_JUMP = std::to_array<T>({0xb523952e,
			0x0b6f099f, 0xccf5a0ef, 0x1c580662});

public:
	xoshiro128starstar() {fill_rand(s);}
	xoshiro128starstar(const decltype(s)& new_s): s(new_s) {}
	void seed(const decltype(s)& new_s) {s = new_s;}

	T next()
	{
		const T result = std::rotl(s[1] * 5, 7) * 9;
		const T t = s[1] << 9;

		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];

		s[2] ^= t;

		s[3] = std::rotl(s[3], 11);

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

/** This is xoshiro256+ 1.0, our best and fastest generator for floating-point
 * numbers. We suggest to use its upper bits for floating-point generation, as
 * it is slightly faster than xoshiro256++/xoshiro256**. It passes all tests we
 * are aware of except for the lowest three bits, which might fail linearity
 * tests (and just those), so if low linear complexity is not considered an
 * issue (as it is usually the case) it can be used to generate 64-bit outputs,
 * too.
 *
 * We suggest to use a sign test to extract a random Boolean value, and right
 * shifts to extract subsets of bits.
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoshiro256plus
{
	using T = uint64_t;
	static constexpr size_t state_num_elems = 4;

NAMED_REQ_URBG

private:
	std::array<T, state_num_elems> s;
	static constexpr auto JUMP = std::to_array<T>({0x180ec6d33cfd0aba,
			0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c});
	static constexpr auto LONG_JUMP = std::to_array<T>({0x76e15d3efefdcbbf,
			0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635});

public:
	xoshiro256plus() {fill_rand(s);}
	xoshiro256plus(const decltype(s)& new_s): s(new_s) {}
	void seed(const decltype(s)& new_s) {s = new_s;}

	T next()
	{
		const T result = s[0] + s[3];
		const T t = s[1] << 17;

		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];

		s[2] ^= t;

		s[3] = std::rotl(s[3], 45);

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^128
	 * calls to next(); it can be used to generate 2^128 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^192 calls to next(); it can be used to generate 2^64 starting points,
	 * from each of which jump() will generate 2^64 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP
};

/** This is xoshiro256++ 1.0, one of our all-purpose, rock-solid generators. It
 * has excellent (sub-ns) speed, a state (256 bits) that is large enough for
 * any parallel application, and it passes all tests we are aware of.
 *
 * For generating just floating-point numbers, xoshiro256+ is even faster.
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoshiro256plusplus
{
	using T = uint64_t;
	static constexpr size_t state_num_elems = 4;

NAMED_REQ_URBG

private:
	std::array<T, state_num_elems> s;
	static constexpr auto JUMP = std::to_array<T>({0x180ec6d33cfd0aba,
			0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c});
	static constexpr auto LONG_JUMP = std::to_array<T>({0x76e15d3efefdcbbf,
			0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635});

public:
	xoshiro256plusplus() {fill_rand(s);}
	xoshiro256plusplus(const decltype(s)& new_s): s(new_s) {}
	void seed(const decltype(s)& new_s) {s = new_s;}

	T next()
	{
		const T result = std::rotl(s[0] + s[3], 23) + s[0];
		const T t = s[1] << 17;

		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];

		s[2] ^= t;

		s[3] = std::rotl(s[3], 45);

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^128
	 * calls to next(); it can be used to generate 2^128 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^192 calls to next(); it can be used to generate 2^64 starting points,
	 * from each of which jump() will generate 2^64 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP
};

/** This is xoshiro256** 1.0, one of our all-purpose, rock-solid generators. It
 * has excellent (sub-ns) speed, a state (256 bits) that is large enough for
 * any parallel application, and it passes all tests we are aware of.
 *
 * For generating just floating-point numbers, xoshiro256+ is even faster.
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoshiro256starstar
{
	using T = uint64_t;
	static constexpr size_t state_num_elems = 4;

NAMED_REQ_URBG

private:
	std::array<T, state_num_elems> s;
	static constexpr auto JUMP = std::to_array<T>({0x180ec6d33cfd0aba,
			0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c});
	static constexpr auto LONG_JUMP = std::to_array<T>({0x76e15d3efefdcbbf,
			0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635});

public:
	xoshiro256starstar() {fill_rand(s);}
	xoshiro256starstar(const decltype(s)& new_s): s(new_s) {}
	void seed(const decltype(s)& new_s) {s = new_s;}

	T next()
	{
		const T result = std::rotl(s[1] * 5, 7) * 9;
		const T t = s[1] << 17;

		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];

		s[2] ^= t;

		s[3] = std::rotl(s[3], 45);

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^128
	 * calls to next(); it can be used to generate 2^128 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^192 calls to next(); it can be used to generate 2^64 starting points,
	 * from each of which jump() will generate 2^64 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP
};

/** This is xoshiro512+ 1.0, our generator for floating-point numbers with
 * increased state size. We suggest to use its upper bits for floating-point
 * generation, as it is slightly faster than xoshiro512**. It passes all tests
 * we are aware of except for the lowest three bits, which might fail linearity
 * tests (and just those), so if low linear complexity is not considered an
 * issue (as it is usually the case) it can be used to generate 64-bit outputs,
 * too.
 *
 * We suggest to use a sign test to extract a random Boolean value, and right
 * shifts to extract subsets of bits.
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoshiro512plus
{
	using T = uint64_t;
	static constexpr size_t state_num_elems = 8;

NAMED_REQ_URBG

private:
	std::array<T, state_num_elems> s;
	static constexpr auto JUMP = std::to_array<T>({0x33ed89b6e7a353f9,
			0x760083d7955323be, 0x2837f2fbb5f22fae, 0x4b8c5674d309511c,
			0xb11ac47a7ba28c25, 0xf1be7667092bcc1c, 0x53851efdb6df0aaf,
			0x1ebbc8b23eaf25db});
	static constexpr auto LONG_JUMP = std::to_array<T>({0x11467fef8f921d28,
			0xa2a819f2e79c8ea8, 0xa8299fc284b3959a, 0xb4d347340ca63ee1,
			0x1cb0940bedbff6ce, 0xd956c5c4fa1f8e17, 0x915e38fd4eda93bc,
			0x5b3ccdfa5d7daca5});

public:
	xoshiro512plus() {fill_rand(s);}
	xoshiro512plus(const decltype(s)& new_s): s(new_s) {}
	void seed(const decltype(s)& new_s) {s = new_s;}

	T next()
	{
		const T result = s[0] + s[2];
		const T t = s[1] << 11;

		s[2] ^= s[0];
		s[5] ^= s[1];
		s[1] ^= s[2];
		s[7] ^= s[3];
		s[3] ^= s[4];
		s[4] ^= s[5];
		s[0] ^= s[6];
		s[6] ^= s[7];

		s[6] ^= t;

		s[7] = std::rotl(s[7], 21);

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^256
	 * calls to next(); it can be used to generate 2^256 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^384 calls to next(); it can be used to generate 2^128 starting points,
	 * from each of which jump() will generate 2^128 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP
};

/** This is xoshiro512++ 1.0, one of our all-purpose, rock-solid generators. It
 * has excellent (about 1ns) speed, a state (512 bits) that is large enough for
 * any parallel application, and it passes all tests we are aware of.
 *
 * For generating just floating-point numbers, xoshiro512+ is even faster.
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoshiro512plusplus
{
	using T = uint64_t;
	static constexpr size_t state_num_elems = 8;

NAMED_REQ_URBG

private:
	std::array<T, state_num_elems> s;
	static constexpr auto JUMP = std::to_array<T>({0x33ed89b6e7a353f9,
			0x760083d7955323be, 0x2837f2fbb5f22fae, 0x4b8c5674d309511c,
			0xb11ac47a7ba28c25, 0xf1be7667092bcc1c, 0x53851efdb6df0aaf,
			0x1ebbc8b23eaf25db});
	static constexpr auto LONG_JUMP = std::to_array<T>({0x11467fef8f921d28,
			0xa2a819f2e79c8ea8, 0xa8299fc284b3959a, 0xb4d347340ca63ee1,
			0x1cb0940bedbff6ce, 0xd956c5c4fa1f8e17, 0x915e38fd4eda93bc,
			0x5b3ccdfa5d7daca5});

public:
	xoshiro512plusplus() {fill_rand(s);}
	xoshiro512plusplus(const decltype(s)& new_s): s(new_s) {}
	void seed(const decltype(s)& new_s) {s = new_s;}

	T next()
	{
		const T result = std::rotl(s[0] + s[2], 17) + s[2];
		const T t = s[1] << 11;

		s[2] ^= s[0];
		s[5] ^= s[1];
		s[1] ^= s[2];
		s[7] ^= s[3];
		s[3] ^= s[4];
		s[4] ^= s[5];
		s[0] ^= s[6];
		s[6] ^= s[7];

		s[6] ^= t;

		s[7] = std::rotl(s[7], 21);

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^256
	 * calls to next(); it can be used to generate 2^256 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^384 calls to next(); it can be used to generate 2^128 starting points,
	 * from each of which jump() will generate 2^128 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP
};

/** This is xoshiro512** 1.0, one of our all-purpose, rock-solid generators
 * with increased state size. It has excellent (about 1ns) speed, a state (512
 * bits) that is large enough for any parallel application, and it passes all
 * tests we are aware of.
 *
 * For generating just floating-point numbers, xoshiro512+ is even faster.
 *
 * The state must be seeded so that it is not everywhere zero. If you have a
 * 64-bit seed, we suggest to seed a splitmix64 generator and use its output to
 * fill s.
 */
struct xoshiro512starstar
{
	using T = uint64_t;
	static constexpr size_t state_num_elems = 8;

NAMED_REQ_URBG

private:
	std::array<T, state_num_elems> s;
	static constexpr auto JUMP = std::to_array<T>({0x33ed89b6e7a353f9,
			0x760083d7955323be, 0x2837f2fbb5f22fae, 0x4b8c5674d309511c,
			0xb11ac47a7ba28c25, 0xf1be7667092bcc1c, 0x53851efdb6df0aaf,
			0x1ebbc8b23eaf25db});
	static constexpr auto LONG_JUMP = std::to_array<T>({0x11467fef8f921d28,
			0xa2a819f2e79c8ea8, 0xa8299fc284b3959a, 0xb4d347340ca63ee1,
			0x1cb0940bedbff6ce, 0xd956c5c4fa1f8e17, 0x915e38fd4eda93bc,
			0x5b3ccdfa5d7daca5});

public:
	xoshiro512starstar() {fill_rand(s);}
	xoshiro512starstar(const decltype(s)& new_s): s(new_s) {}
	void seed(const decltype(s)& new_s) {s = new_s;}

	T next()
	{
		const T result = std::rotl(s[1] * 5, 7) * 9;
		const T t = s[1] << 11;

		s[2] ^= s[0];
		s[5] ^= s[1];
		s[1] ^= s[2];
		s[7] ^= s[3];
		s[3] ^= s[4];
		s[4] ^= s[5];
		s[0] ^= s[6];
		s[6] ^= s[7];

		s[6] ^= t;

		s[7] = std::rotl(s[7], 21);

		return result;
	}

	/** This is the jump function for the generator. It is equivalent to 2^256
	 * calls to next(); it can be used to generate 2^256 non-overlapping
	 * subsequences for parallel computations.
	 */
DEF_JUMP

	/** This is the long-jump function for the generator. It is equivalent to
	 * 2^384 calls to next(); it can be used to generate 2^128 starting points,
	 * from each of which jump() will generate 2^128 non-overlapping
	 * subsequences for parallel distributed computations.
	 */
DEF_LONG_JUMP
};

#undef NAMED_REQ_URBG
#undef DEF_JUMP
#undef DEF_LONG_JUMP
