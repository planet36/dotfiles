// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Scaled integer constants
/**
\file
\author Steven Ward
\sa https://reference.wolfram.com/language/guide/MathematicalConstants.html
These scaled constants are coprime with their integer range.
*/

#pragma once

#include <cstdint>

/// Pi scaled to 32 bits
/**
https://www.wolframalpha.com/input?i=BaseForm%5BRound%5B%282%5E64+-+1%29%2FPi%5D%2C+16%5D
https://www.wolframalpha.com/input?i=PrimeQ%5BRound%5B%282%5E64+-+1%29%2FPi%5D%5D
https://www.wolframalpha.com/input?i=DigitCount%5BRound%5B%282%5E64+-+1%29%2FPi%5D%2C+2%2C+1%5D
https://www.wolframalpha.com/input?i=CoprimeQ%5BRound%5B%282%5E64+-+1%29%2FPi%5D%2C+2%5E64%5D
*/
inline constexpr uint32_t Pi_32 = 0x517cc1b7; // not prime (popcount = 17)
static_assert((Pi_32 & 1) != 0, "must be odd");

/// Pi scaled to 64 bits
/**
https://www.wolframalpha.com/input?i=BaseForm%5BRound%5B%282%5E64+-+1%29%2FPi%5D%2C+16%5D
https://www.wolframalpha.com/input?i=PrimeQ%5BRound%5B%282%5E64+-+1%29%2FPi%5D%5D
https://www.wolframalpha.com/input?i=DigitCount%5BRound%5B%282%5E64+-+1%29%2FPi%5D%2C+2%2C+1%5D
https://www.wolframalpha.com/input?i=CoprimeQ%5BRound%5B%282%5E64+-+1%29%2FPi%5D%2C+2%5E64%5D
*/
inline constexpr uint64_t Pi_64 = 0x517cc1b727220a95; // not prime (popcount = 29)
static_assert((Pi_64 & 1) != 0, "must be odd");

/// GoldenRatio scaled to 32 bits
/**
https://www.wolframalpha.com/input?i=BaseForm%5BRound%5B%282%5E32+-+1%29%2FGoldenRatio%5D%2C+16%5D
https://www.wolframalpha.com/input?i=PrimeQ%5BRound%5B%282%5E32+-+1%29%2FGoldenRatio%5D%5D
https://www.wolframalpha.com/input?i=CoprimeQ%5BRound%5B%282%5E32+-+1%29%2FGoldenRatio%5D%2C+2%5E32%5D
https://www.wolframalpha.com/input?i=DigitCount%5BRound%5B%282%5E32+-+1%29%2FGoldenRatio%5D%2C+2%2C+1%5D
*/
inline constexpr uint32_t GoldenRatio_32 = 0x9e3779b9; // not prime (popcount = 20)
static_assert((GoldenRatio_32 & 1) != 0, "must be odd");

/// GoldenRatio scaled to 64 bits
/**
https://www.wolframalpha.com/input?i=BaseForm%5BRound%5B%282%5E64+-+1%29%2FGoldenRatio%5D%2C+16%5D
https://www.wolframalpha.com/input?i=PrimeQ%5BRound%5B%282%5E64+-+1%29%2FGoldenRatio%5D%5D
https://www.wolframalpha.com/input?i=DigitCount%5BRound%5B%282%5E64+-+1%29%2FGoldenRatio%5D%2C+2%2C+1%5D
https://www.wolframalpha.com/input?i=CoprimeQ%5BRound%5B%282%5E64+-+1%29%2FGoldenRatio%5D%2C+2%5E64%5D
*/
inline constexpr uint64_t GoldenRatio_64 = 0x9e3779b97f4a7c15; // not prime (popcount = 38)
static_assert((GoldenRatio_64 & 1) != 0, "must be odd");
