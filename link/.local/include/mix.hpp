// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// mix/avalanche the bits of integers
/**
\file
\author Steven Ward
\sa https://www.pcg-random.org/posts/developing-a-seed_seq-alternative.html
*/

#pragma once

#include "mum.hpp"

#include <concepts>
#include <cstdint>

constexpr void
mumx_mix(uint64_t& x0, uint64_t& x1)
{
	// step 0
	x0 += _mum_primes[0];
	x1 += _mum_primes[1];

	// step 1 -- keep x0
	x1 = mumx(x1, x0 + _mum_primes[2]);

	// step 2 -- keep x1
	x0 = mumx(x0, x1 + _mum_primes[3]);
}

constexpr void
mumx_mix(uint64_t& x0, uint64_t& x1, uint64_t& x2)
{
	// step 0
	x0 += _mum_primes[0];
	x1 += _mum_primes[1];
	x2 += _mum_primes[2];

	// step 1 -- keep x0
	x1 = mumx(x1, x0 + _mum_primes[3]);
	x2 = mumx(x2, x0 + _mum_primes[4]);

	// step 2 -- keep x1
	x0 = mumx(x0, x1 + _mum_primes[5]);
	x2 = mumx(x2, x1 + _mum_primes[6]);

	// step 3 -- keep x2
	x0 = mumx(x0, x2 + _mum_primes[7]);
	x1 = mumx(x1, x2 + _mum_primes[8]);
}

constexpr void
mumx_mix(uint64_t& x0, uint64_t& x1, uint64_t& x2, uint64_t& x3)
{
	// step 0
	x0 += _mum_primes[0];
	x1 += _mum_primes[1];
	x2 += _mum_primes[2];
	x3 += _mum_primes[3];

	// step 1 -- keep x0
	x1 = mumx(x1, x0 + _mum_primes[4]);
	x2 = mumx(x2, x0 + _mum_primes[5]);
	x3 = mumx(x3, x0 + _mum_primes[6]);

	// step 2 -- keep x1
	x0 = mumx(x0, x1 + _mum_primes[7]);
	x2 = mumx(x2, x1 + _mum_primes[8]);
	x3 = mumx(x3, x1 + _mum_primes[9]);

	// step 3 -- keep x2
	x0 = mumx(x0, x2 + _mum_primes[10]);
	x1 = mumx(x1, x2 + _mum_primes[11]);
	x3 = mumx(x3, x2 + _mum_primes[12]);

	// step 4 -- keep x3
	x0 = mumx(x0, x3 + _mum_primes[13]);
	x1 = mumx(x1, x3 + _mum_primes[14]);
	x2 = mumx(x2, x3 + _mum_primes[15]);
}
