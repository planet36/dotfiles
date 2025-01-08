// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// An array of hexadecimal digits of the fractional part of transcendental numbers
/**
\file
\author Steven Ward
\sa https://mathworld.wolfram.com/TranscendentalNumber.html
\sa https://mathworld.wolfram.com/GelfondsTheorem.html
\sa https://en.wikipedia.org/wiki/Nothing-up-my-sleeve_number
*/

#pragma once

#include <array>
#include <immintrin.h>

/// an array of hexadecimal digits of the fractional part of transcendental numbers of the form \f$ e^{\pi \sqrt{n}}, n \in \mathbb{Z}^{+} \f$
/**
Mathematica expression: <code>RealDigits[E^(Pi*sqrt(Range[20])), 256, 16, -1]</code>
\sa https://www.wolframalpha.com/input?i=RealDigits%5BE%5E%28Pi*sqrt%28Range%5B20%5D%29%29%2C+256%2C+16%2C+-1%5D
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
const auto tn_hexdigits_m128i = std::to_array({
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
});
#pragma GCC diagnostic pop

/// an array of hexadecimal digits of the fractional part of transcendental numbers of the form \f$ e^{\pi \sqrt{n}}, n \in \mathbb{Z}^{+} \f$
/**
Mathematica expression: <code>RealDigits[exp(Pi*sqrt(Range[8])), 256, 32, -1]</code>
\sa https://www.wolframalpha.com/input?i=RealDigits%5Bexp%28Pi*sqrt%28Range%5B8%5D%29%29%2C+256%2C+32%2C+-1%5D
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
const auto tn_hexdigits_m256i = std::to_array({
    // most significant byte first
    _mm256_set_epi8( 36,   4, 110, 176, 147,  57, 158, 205, 167,  72, 159, 154, 183, 105,  77,  49, 250,  25, 110, 146,  46, 146, 215,  21,  37, 242,  43,  84,  98,  16,  31,  47),
    _mm256_set_epi8(  5,  10, 191,   3, 143, 250, 189, 152, 117,  63,  29,  98, 184, 155, 133,  23, 173, 125, 228, 111,  43, 227, 178,  18,  99,  56,  64,  12, 186,  28, 135,  18),
    _mm256_set_epi8(195, 188,  15,  97, 162, 153, 249, 227, 167, 159,  38, 186, 214, 157, 137,   5, 221, 171, 238, 181,  65,  62, 227,  92, 244,  36, 186,  94,  18, 104, 192,  55),
    _mm256_set_epi8(125, 221,  34, 239, 195,  35, 143, 187,  36, 228, 164, 214,  42, 144,   7, 171, 213, 196, 246,  96,  51,  73,  18,  65,  99, 202, 111, 168,  47, 197, 230, 150),
    _mm256_set_epi8( 47, 174, 236, 195,   3, 133,  44, 191,  39, 170,  40, 168, 240,  85, 238,  86,  14, 184,   4,  83,  37,  74,  60, 237, 247, 182,  40, 102, 136, 239,  88, 240),
    _mm256_set_epi8(253, 169, 160,  92, 212,  35,  11, 226, 223,  19,  34, 239, 137,   1, 162, 188,  52,  26,  54, 117,  17,  50,  48,  38, 123,  57,  87,  79,  88,   3, 218,  41),
    _mm256_set_epi8(238, 157, 202, 237,  65,  17,  93, 134, 230,  91,  65, 198, 217, 154, 242, 235, 113, 153, 155, 184, 124, 237, 153, 171,  14, 116,  26, 108, 248,  67, 234,  25),
    _mm256_set_epi8( 89,  60,  68,  71,  58, 239,  67,  33, 120,  43,  41, 144, 216, 178, 218, 223,  61, 144,  86, 178,  57, 100, 218, 133, 211,  67,  68,  79, 228, 107, 144, 194),
    _mm256_set_epi8(165, 214, 189,  88,  78,  58,  48, 108, 245, 246,  26,  46, 192,   7,  64, 193, 111, 219, 170, 107, 196, 155, 246, 178, 150,  39, 216,  38, 187, 253, 121, 100),
    _mm256_set_epi8(201, 177, 178, 206, 192, 228, 192, 188, 101, 107, 141, 221, 238, 148, 240,  63,  30,  76, 163, 120, 109, 103, 218, 236, 253, 208,  42, 205,  16,   7, 224,  30),
    _mm256_set_epi8( 36, 159, 242,  88, 181,  22,  14,   8, 163, 151,  55,  28, 144, 235,  85, 146, 169,  61,  34, 237, 154, 188, 182,  83,  83, 139, 194,  98, 203, 218, 178, 120),
    _mm256_set_epi8( 75, 147, 173,   5, 130, 183,   0,  51, 180, 243, 135, 133, 155, 199,  27,  46, 168, 254,  12,  85,  70,  85, 108, 142, 145,  72, 104, 158,  56,  41,   4, 128),
    _mm256_set_epi8(242, 134, 209, 136,  74, 182, 110,  16, 235,  76,  55, 253, 100,  88,   3, 110,  44, 252,  69, 112,  50, 246, 178, 110, 172, 157,  72, 111, 125, 236,  59, 193),
    _mm256_set_epi8(197, 157,  88,   7,  92,  86,  90,  25, 213, 173,  53, 153, 110, 113,  84, 166,  27, 188,   6,  62,  34, 222,   4,  80, 140, 139, 139, 184, 127, 129, 251,  51),
    _mm256_set_epi8(207, 101, 115,  34,  98,  87,  71,   3, 109,  31,  71, 133, 100,  34, 181, 112, 251, 135, 128,  47,   3, 114,  65,  75, 144, 195, 250,  91, 243, 234,  81, 152),
    _mm256_set_epi8( 80,  41, 185,  69,  25, 238, 246,  90, 130,  33,  58,   6, 252,  29, 229,  61, 248, 143, 106, 118,  98,   8, 232,   3, 161,  25, 160, 158, 167,  85,  32, 222),
    _mm256_set_epi8(255, 103, 172,  99, 141, 228,  68, 139,  65, 133, 172, 217, 165, 150,  82,  23, 151, 182, 139, 111,  30, 117,  56, 107, 203, 159, 117,  15,  62, 144, 142,  43),
    _mm256_set_epi8(254,  45, 192, 129,   0, 183,  99,  54, 221, 108, 168,  52, 198, 218, 150, 181,  16, 192,  43,  50,  51, 189, 157,  34, 108, 156, 226, 148, 154,  48, 136, 165),
    _mm256_set_epi8(199,  22,  11, 237, 140, 235, 238, 253, 180,   5,  73, 129,  66, 192,  76, 225,  40,  67, 125, 107, 176, 149,  76,  52, 253,  97,  62, 148, 130,  26, 208,  70),
    _mm256_set_epi8(192, 240, 194, 237,  56, 204, 193,  23,  58,  14, 114, 103, 234,  12,  10, 162,  81, 213,  21,  42, 228, 232,  80, 122, 180, 120,  10, 135, 179, 132, 189, 151),
});
#pragma GCC diagnostic pop
