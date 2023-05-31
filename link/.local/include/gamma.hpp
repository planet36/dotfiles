// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Gamma integer constants
/**
\file
\author Steven Ward
*/

#pragma once

#include <cstdint>

/// The golden ratio scaled to 32 bits
/**
* "BaseForm[Round[(2^32 - 1)/GoldenRatio], 16]"
* https://www.wolframalpha.com/input?i=BaseForm%5BRound%5B%282%5E32+-+1%29%2FGoldenRatio%5D%2C+16%5D
* This is coprime to 2^32.
* https://www.wolframalpha.com/input?i=CoprimeQ%5B0x9e3779b9%2C+2%5E32%5D
*/
inline constexpr uint32_t gamma32 = 0x9e3779b9; // not prime (popcount = 20)
static_assert((gamma32 & 1) != 0, "must be odd");

/// The golden ratio scaled to 64 bits
/**
* "BaseForm[Round[(2^64 - 1)/GoldenRatio], 16]"
* https://www.wolframalpha.com/input?i=BaseForm%5BRound%5B%282%5E64+-+1%29%2FGoldenRatio%5D%2C+16%5D
* This is coprime to 2^64.
* https://www.wolframalpha.com/input?i=CoprimeQ%5B0x9e3779b97f4a7c15%2C+2%5E64%5D
*/
inline constexpr uint64_t gamma64 = 0x9e3779b97f4a7c15; // not prime (popcount = 38)
static_assert((gamma64 & 1) != 0, "must be odd");
