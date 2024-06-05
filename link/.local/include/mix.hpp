// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// mix/avalanche the bits of integers
/**
\file
\author Steven Ward
\sa https://www.pcg-random.org/posts/developing-a-seed_seq-alternative.html
*/

#pragma once

#include "bit_patterns.hpp"
#include "mum.hpp"

#include <concepts>
#include <cstdint>

constexpr void
mumx_mix_u64x2(uint64_t& x0, uint64_t& x1)
{
	using namespace bit_patterns_64;

	// step 0
	x0 += C[shuf_i[0]];
	x1 += C[shuf_i[1]];

	// step 1 -- keep x0
	x1 = mumx(x1, x0 + C[shuf_i[2]]);

	// step 2 -- keep x1
	x0 = mumx(x0, x1 + C[shuf_i[3]]);
}

constexpr void
mumx_mix_u64x3(uint64_t& x0, uint64_t& x1, uint64_t& x2)
{
	using namespace bit_patterns_64;

	// step 0
	x0 += C[shuf_i[0]];
	x1 += C[shuf_i[1]];
	x2 += C[shuf_i[2]];

	// step 1 -- keep x0
	x1 = mumx(x1, x0 + C[shuf_i[3]]);
	x2 = mumx(x2, x0 + C[shuf_i[4]]);

	// step 2 -- keep x1
	x0 = mumx(x0, x1 + C[shuf_i[5]]);
	x2 = mumx(x2, x1 + C[shuf_i[6]]);

	// step 3 -- keep x2
	x0 = mumx(x0, x2 + C[shuf_i[7]]);
	x1 = mumx(x1, x2 + C[shuf_i[8]]);
}

constexpr void
mumx_mix_u64x4(uint64_t& x0, uint64_t& x1, uint64_t& x2, uint64_t& x3)
{
	using namespace bit_patterns_64;

	// step 0
	x0 += C[shuf_i[0]];
	x1 += C[shuf_i[1]];
	x2 += C[shuf_i[2]];
	x3 += C[shuf_i[3]];

	// step 1 -- keep x0
	x1 = mumx(x1, x0 + C[shuf_i[4]]);
	x2 = mumx(x2, x0 + C[shuf_i[5]]);
	x3 = mumx(x3, x0 + C[shuf_i[6]]);

	// step 2 -- keep x1
	x0 = mumx(x0, x1 + C[shuf_i[7]]);
	x2 = mumx(x2, x1 + C[shuf_i[8]]);
	x3 = mumx(x3, x1 + C[shuf_i[9]]);

	// step 3 -- keep x2
	x0 = mumx(x0, x2 + C[shuf_i[10]]);
	x1 = mumx(x1, x2 + C[shuf_i[11]]);
	x3 = mumx(x3, x2 + C[shuf_i[12]]);

	// step 4 -- keep x3
	x0 = mumx(x0, x3 + C[shuf_i[13]]);
	x1 = mumx(x1, x3 + C[shuf_i[14]]);
	x2 = mumx(x2, x3 + C[shuf_i[15]]);
}
