// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// An array of hexadecimal digits of the fractional part of transcendental numbers
/**
\file
\author Steven Ward
*/

#pragma once

#include <array>
#include <immintrin.h>

/// an array of hexadecimal digits of the fractional part of transcendental numbers of the form \f$ e^{\pi \sqrt{n}}, n \in \Bbb{Z}_{\ge 0} \f$
/**
Mathematica expression: <code>RealDigits[E^(Pi*sqrt(Range[20])), 256, 16, -1]</code>
\sa https://www.wolframalpha.com/input?i=RealDigits%5BE%5E%28Pi*sqrt%28Range%5B20%5D%29%29%2C+256%2C+16%2C+-1%5D
\sa https://mathworld.wolfram.com/TranscendentalNumber.html
\sa https://mathworld.wolfram.com/GelfondsTheorem.html
\sa https://en.wikipedia.org/wiki/Nothing-up-my-sleeve_number
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
const std::array<__m128i, 20> tn_hexdigits {
	// most significant byte first
	_mm_set_epi8( 36,   4, 110, 176, 147,  57, 158, 205, 167,  72, 159, 154, 183, 105,  77,  49),
	_mm_set_epi8(  5,  10, 191,   3, 143, 250, 189, 152, 117,  63,  29,  98, 184, 155, 133,  23),
	_mm_set_epi8(195, 188,  15,  97, 162, 153, 249, 227, 167, 159,  38, 186, 214, 157, 137,   5),
	_mm_set_epi8(125, 221,  34, 239, 195,  35, 143, 187,  36, 228, 164, 214,  42, 144,   7, 171),
	_mm_set_epi8( 47, 174, 236, 195,   3, 133,  44, 191,  39, 170,  40, 168, 240,  85, 238,  86),
	_mm_set_epi8(253, 169, 160,  92, 212,  35,  11, 226, 223,  19,  34, 239, 137,   1, 162, 188),
	_mm_set_epi8(238, 157, 202, 237,  65,  17,  93, 134, 230,  91,  65, 198, 217, 154, 242, 235),
	_mm_set_epi8( 89,  60,  68,  71,  58, 239,  67,  33, 120,  43,  41, 144, 216, 178, 218, 223),
	_mm_set_epi8(165, 214, 189,  88,  78,  58,  48, 108, 245, 246,  26,  46, 192,   7,  64, 193),
	_mm_set_epi8(201, 177, 178, 206, 192, 228, 192, 188, 101, 107, 141, 221, 238, 148, 240,  63),
	_mm_set_epi8( 36, 159, 242,  88, 181,  22,  14,   8, 163, 151,  55,  28, 144, 235,  85, 146),
	_mm_set_epi8( 75, 147, 173,   5, 130, 183,   0,  51, 180, 243, 135, 133, 155, 199,  27,  46),
	_mm_set_epi8(242, 134, 209, 136,  74, 182, 110,  16, 235,  76,  55, 253, 100,  88,   3, 110),
	_mm_set_epi8(197, 157,  88,   7,  92,  86,  90,  25, 213, 173,  53, 153, 110, 113,  84, 166),
	_mm_set_epi8(207, 101, 115,  34,  98,  87,  71,   3, 109,  31,  71, 133, 100,  34, 181, 112),
	_mm_set_epi8( 80,  41, 185,  69,  25, 238, 246,  90, 130,  33,  58,   6, 252,  29, 229,  61),
	_mm_set_epi8(255, 103, 172,  99, 141, 228,  68, 139,  65, 133, 172, 217, 165, 150,  82,  23),
	_mm_set_epi8(254,  45, 192, 129,   0, 183,  99,  54, 221, 108, 168,  52, 198, 218, 150, 181),
	_mm_set_epi8(199,  22,  11, 237, 140, 235, 238, 253, 180,   5,  73, 129,  66, 192,  76, 225),
	_mm_set_epi8(192, 240, 194, 237,  56, 204, 193,  23,  58,  14, 114, 103, 234,  12,  10, 162),
};
#pragma GCC diagnostic pop
