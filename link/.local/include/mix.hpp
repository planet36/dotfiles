// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// mix/avalanche the bits of integers
/**
* \file
* \author Steven Ward
* \sa https://www.pcg-random.org/posts/developing-a-seed_seq-alternative.html
*/

#pragma once

#include "bit_patterns.hpp"
#if defined(USE_CTRAND)
#include "ctrand.hpp"
#include "map_int.hpp"
#endif
#include "mum.hpp"

#include <concepts>
#include <cstdint>

constexpr void
mumx_mix_u32x2(uint32_t& x0, uint32_t& x1)
{
    using namespace bit_patterns_32;

#if defined(USE_CTRAND)
    // step 0
    x0 += C[map_int(CTRAND64, C.size())];
    x1 += C[map_int(CTRAND64, C.size())];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[map_int(CTRAND64, C.size())]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[map_int(CTRAND64, C.size())]);
#else
    // step 0
    x0 += C[shuf_i[0]];
    x1 += C[shuf_i[1]];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[shuf_i[2]]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[shuf_i[3]]);
#endif
}

constexpr void
mumx_mix_u32x3(uint32_t& x0, uint32_t& x1, uint32_t& x2)
{
    using namespace bit_patterns_32;

#if defined(USE_CTRAND)
    // step 0
    x0 += C[map_int(CTRAND64, C.size())];
    x1 += C[map_int(CTRAND64, C.size())];
    x2 += C[map_int(CTRAND64, C.size())];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[map_int(CTRAND64, C.size())]);
    x2 = mumx(x2, x0 + C[map_int(CTRAND64, C.size())]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[map_int(CTRAND64, C.size())]);
    x2 = mumx(x2, x1 + C[map_int(CTRAND64, C.size())]);

    // step 3 -- keep x2
    x0 = mumx(x0, x2 + C[map_int(CTRAND64, C.size())]);
    x1 = mumx(x1, x2 + C[map_int(CTRAND64, C.size())]);
#else
    // step 0
    x0 += C[shuf_i[4]];
    x1 += C[shuf_i[5]];
    x2 += C[shuf_i[6]];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[shuf_i[7]]);
    x2 = mumx(x2, x0 + C[shuf_i[8]]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[shuf_i[9]]);
    x2 = mumx(x2, x1 + C[shuf_i[10]]);

    // step 3 -- keep x2
    x0 = mumx(x0, x2 + C[shuf_i[11]]);
    x1 = mumx(x1, x2 + C[shuf_i[12]]);
#endif
}

constexpr void
mumx_mix_u32x4(uint32_t& x0, uint32_t& x1, uint32_t& x2, uint32_t& x3)
{
    using namespace bit_patterns_32;

#if defined(USE_CTRAND)
    // step 0
    x0 += C[map_int(CTRAND64, C.size())];
    x1 += C[map_int(CTRAND64, C.size())];
    x2 += C[map_int(CTRAND64, C.size())];
    x3 += C[map_int(CTRAND64, C.size())];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[map_int(CTRAND64, C.size())]);
    x2 = mumx(x2, x0 + C[map_int(CTRAND64, C.size())]);
    x3 = mumx(x3, x0 + C[map_int(CTRAND64, C.size())]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[map_int(CTRAND64, C.size())]);
    x2 = mumx(x2, x1 + C[map_int(CTRAND64, C.size())]);
    x3 = mumx(x3, x1 + C[map_int(CTRAND64, C.size())]);

    // step 3 -- keep x2
    x0 = mumx(x0, x2 + C[map_int(CTRAND64, C.size())]);
    x1 = mumx(x1, x2 + C[map_int(CTRAND64, C.size())]);
    x3 = mumx(x3, x2 + C[map_int(CTRAND64, C.size())]);

    // step 4 -- keep x3
    x0 = mumx(x0, x3 + C[map_int(CTRAND64, C.size())]);
    x1 = mumx(x1, x3 + C[map_int(CTRAND64, C.size())]);
    x2 = mumx(x2, x3 + C[map_int(CTRAND64, C.size())]);
#else
    // step 0
    x0 += C[shuf_i[13]];
    x1 += C[shuf_i[14]];
    x2 += C[shuf_i[15]];
    x3 += C[shuf_i[16]];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[shuf_i[17]]);
    x2 = mumx(x2, x0 + C[shuf_i[18]]);
    x3 = mumx(x3, x0 + C[shuf_i[19]]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[shuf_i[20]]);
    x2 = mumx(x2, x1 + C[shuf_i[21]]);
    x3 = mumx(x3, x1 + C[shuf_i[22]]);

    // step 3 -- keep x2
    x0 = mumx(x0, x2 + C[shuf_i[23]]);
    x1 = mumx(x1, x2 + C[shuf_i[24]]);
    x3 = mumx(x3, x2 + C[shuf_i[25]]);

    // step 4 -- keep x3
    x0 = mumx(x0, x3 + C[shuf_i[26]]);
    x1 = mumx(x1, x3 + C[shuf_i[27]]);
    x2 = mumx(x2, x3 + C[shuf_i[28]]);
#endif
}

constexpr void
mumx_mix_u64x2(uint64_t& x0, uint64_t& x1)
{
    using namespace bit_patterns_64;

#if defined(USE_CTRAND)
    // step 0
    x0 += C[map_int(CTRAND64, C.size())];
    x1 += C[map_int(CTRAND64, C.size())];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[map_int(CTRAND64, C.size())]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[map_int(CTRAND64, C.size())]);
#else
    // step 0
    x0 += C[shuf_i[0]];
    x1 += C[shuf_i[1]];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[shuf_i[2]]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[shuf_i[3]]);
#endif
}

constexpr void
mumx_mix_u64x3(uint64_t& x0, uint64_t& x1, uint64_t& x2)
{
    using namespace bit_patterns_64;

#if defined(USE_CTRAND)
    // step 0
    x0 += C[map_int(CTRAND64, C.size())];
    x1 += C[map_int(CTRAND64, C.size())];
    x2 += C[map_int(CTRAND64, C.size())];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[map_int(CTRAND64, C.size())]);
    x2 = mumx(x2, x0 + C[map_int(CTRAND64, C.size())]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[map_int(CTRAND64, C.size())]);
    x2 = mumx(x2, x1 + C[map_int(CTRAND64, C.size())]);

    // step 3 -- keep x2
    x0 = mumx(x0, x2 + C[map_int(CTRAND64, C.size())]);
    x1 = mumx(x1, x2 + C[map_int(CTRAND64, C.size())]);
#else
    // step 0
    x0 += C[shuf_i[4]];
    x1 += C[shuf_i[5]];
    x2 += C[shuf_i[6]];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[shuf_i[7]]);
    x2 = mumx(x2, x0 + C[shuf_i[8]]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[shuf_i[9]]);
    x2 = mumx(x2, x1 + C[shuf_i[10]]);

    // step 3 -- keep x2
    x0 = mumx(x0, x2 + C[shuf_i[11]]);
    x1 = mumx(x1, x2 + C[shuf_i[12]]);
#endif
}

constexpr void
mumx_mix_u64x4(uint64_t& x0, uint64_t& x1, uint64_t& x2, uint64_t& x3)
{
    using namespace bit_patterns_64;

#if defined(USE_CTRAND)
    // step 0
    x0 += C[map_int(CTRAND64, C.size())];
    x1 += C[map_int(CTRAND64, C.size())];
    x2 += C[map_int(CTRAND64, C.size())];
    x3 += C[map_int(CTRAND64, C.size())];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[map_int(CTRAND64, C.size())]);
    x2 = mumx(x2, x0 + C[map_int(CTRAND64, C.size())]);
    x3 = mumx(x3, x0 + C[map_int(CTRAND64, C.size())]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[map_int(CTRAND64, C.size())]);
    x2 = mumx(x2, x1 + C[map_int(CTRAND64, C.size())]);
    x3 = mumx(x3, x1 + C[map_int(CTRAND64, C.size())]);

    // step 3 -- keep x2
    x0 = mumx(x0, x2 + C[map_int(CTRAND64, C.size())]);
    x1 = mumx(x1, x2 + C[map_int(CTRAND64, C.size())]);
    x3 = mumx(x3, x2 + C[map_int(CTRAND64, C.size())]);

    // step 4 -- keep x3
    x0 = mumx(x0, x3 + C[map_int(CTRAND64, C.size())]);
    x1 = mumx(x1, x3 + C[map_int(CTRAND64, C.size())]);
    x2 = mumx(x2, x3 + C[map_int(CTRAND64, C.size())]);
#else
    // step 0
    x0 += C[shuf_i[13]];
    x1 += C[shuf_i[14]];
    x2 += C[shuf_i[15]];
    x3 += C[shuf_i[16]];

    // step 1 -- keep x0
    x1 = mumx(x1, x0 + C[shuf_i[17]]);
    x2 = mumx(x2, x0 + C[shuf_i[18]]);
    x3 = mumx(x3, x0 + C[shuf_i[19]]);

    // step 2 -- keep x1
    x0 = mumx(x0, x1 + C[shuf_i[20]]);
    x2 = mumx(x2, x1 + C[shuf_i[21]]);
    x3 = mumx(x3, x1 + C[shuf_i[22]]);

    // step 3 -- keep x2
    x0 = mumx(x0, x2 + C[shuf_i[23]]);
    x1 = mumx(x1, x2 + C[shuf_i[24]]);
    x3 = mumx(x3, x2 + C[shuf_i[25]]);

    // step 4 -- keep x3
    x0 = mumx(x0, x3 + C[shuf_i[26]]);
    x1 = mumx(x1, x3 + C[shuf_i[27]]);
    x2 = mumx(x2, x3 + C[shuf_i[28]]);
#endif
}
