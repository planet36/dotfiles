// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// A seed sequence that uses \c std::random_device
/**
\file
\author Steven Ward
*/

#pragma once

#include <algorithm>
#include <iterator>
#include <random>

/// A seed sequence (mimicking \c std::seed_seq) that uses \c std::random_device
/**
This partially satisfies the named requirement \c SeedSequence.

\sa https://en.cppreference.com/w/cpp/named_req/SeedSequence
\sa https://en.cppreference.com/w/cpp/numeric/random/seed_seq/generate
\sa https://en.cppreference.com/w/cpp/algorithm/generate

Adapted from the following sources.
\sa https://old.reddit.com/r/cpp/comments/31857s/random_number_generation_it_might_be_harder_than/cq08lli/
\sa https://probablydance.com/2016/12/29/random_seed_seq-a-small-utility-to-properly-seed-random-number-generators-in-c/
\sa https://codingnest.com/generating-random-numbers-using-c-standard-library-the-solutions/

\sa https://www.pcg-random.org/posts/cpp-seeding-surprises.html
*/
struct random_device_seed_seq
{
	using result_type = std::seed_seq::result_type;

	template <std::random_access_iterator Iter>
	void generate(Iter first, Iter last)
	{
		std::generate(first, last, std::ref(random_device));
	}

private:
	std::random_device random_device;
};

/// Return an instance of \c PRNG that has been seeded with \c random_device_seed_seq
/**
\pre \a PRNG satisfies the named requirement \c RandomNumberEngine.

\sa https://en.cppreference.com/w/cpp/named_req/RandomNumberEngine

Use it like this
\code{.cpp}
auto rng = random_device_seeded<std::mt19937_64>();
\endcode

Adapted from the following source.
\sa http://www.gockelhut.com/cpp-pirate/random-seed.html
*/
template <typename PRNG = std::mt19937_64>
PRNG
random_device_seeded()
{
	thread_local random_device_seed_seq rd_ss;
	return PRNG{rd_ss};
}

/// A seed sequence (mimicking \c std::seed_seq) that uses a constant value
/**
This partially satisfies the named requirement \c SeedSequence.

\sa https://en.cppreference.com/w/cpp/named_req/SeedSequence
\sa https://en.cppreference.com/w/cpp/numeric/random/seed_seq/generate
\sa https://en.cppreference.com/w/cpp/algorithm/fill
*/
template <std::seed_seq::result_type value = 0>
struct fill_seed_seq
{
	using result_type = std::seed_seq::result_type;

	template <std::random_access_iterator Iter>
	void generate(Iter first, Iter last)
	{
		std::fill(first, last, value);
	}
};

/// A seed sequence (mimicking \c std::seed_seq) that uses sequentially increasing values
/**
This partially satisfies the named requirement \c SeedSequence.

\sa https://en.cppreference.com/w/cpp/named_req/SeedSequence
\sa https://en.cppreference.com/w/cpp/numeric/random/seed_seq/generate
\sa https://en.cppreference.com/w/cpp/algorithm/iota
*/
template <std::seed_seq::result_type value = 0>
struct iota_seed_seq
{
	using result_type = std::seed_seq::result_type;

	template <std::random_access_iterator Iter>
	void generate(Iter first, Iter last)
	{
		std::iota(first, last, value);
	}
};
