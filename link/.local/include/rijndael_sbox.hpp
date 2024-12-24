// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Rijndael S-box
/**
\file
\author Steven Ward
\sa https://en.wikipedia.org/wiki/Rijndael_S-box
\sa https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197-upd1.pdf
\sa https://cryptography.fandom.com/wiki/Rijndael_S-box
\sa https://github.com/planet36/rijndael-s-box
*/

#pragma once

#include <array>
#include <cstdint>

inline constexpr std::array<uint8_t, 256> rijndael_sbox_fwd {
/*         00    01    02    03    04    05    06    07    08    09    0a    0b    0c    0d    0e    0f */
/* 00 */ 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
/* 10 */ 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
/* 20 */ 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
/* 30 */ 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
/* 40 */ 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
/* 50 */ 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
/* 60 */ 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
/* 70 */ 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
/* 80 */ 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
/* 90 */ 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
/* a0 */ 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
/* b0 */ 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
/* c0 */ 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
/* d0 */ 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
/* e0 */ 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
/* f0 */ 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16,
};

inline constexpr std::array<uint8_t, 256> rijndael_sbox_inv {
/*         00    01    02    03    04    05    06    07    08    09    0a    0b    0c    0d    0e    0f */
/* 00 */ 0xd3, 0xa1, 0xec, 0x37, 0xb2, 0x00, 0x6e, 0x59, 0x88, 0x96, 0xb8, 0x76, 0xad, 0xdd, 0x8b, 0xe4,
/* 10 */ 0x32, 0x02, 0xce, 0xef, 0x1e, 0x23, 0x7a, 0xe6, 0x91, 0xb5, 0x4c, 0x13, 0x60, 0x4f, 0xc1, 0x42,
/* 20 */ 0x83, 0x9a, 0x86, 0x7c, 0xcd, 0xeb, 0x2f, 0xf8, 0xb6, 0x43, 0xf5, 0x3e, 0xcb, 0xcc, 0x20, 0x4d,
/* 30 */ 0xb7, 0x21, 0x09, 0xed, 0xe1, 0xaa, 0x6c, 0x30, 0x9e, 0x84, 0x71, 0x26, 0x46, 0xd7, 0x04, 0xc5,
/* 40 */ 0x8f, 0x3d, 0x9f, 0x73, 0x94, 0x0f, 0xcf, 0x9c, 0x51, 0x67, 0xaf, 0xfa, 0x3a, 0x19, 0xee, 0x01,
/* 50 */ 0x24, 0xab, 0xdf, 0x10, 0x0a, 0x66, 0x5f, 0xe8, 0xe7, 0x1f, 0x6d, 0xf7, 0x07, 0xac, 0xb3, 0x5b,
/* 60 */ 0x69, 0x18, 0x70, 0x36, 0x6f, 0x55, 0x52, 0xfd, 0x57, 0xfb, 0x7e, 0x89, 0xa3, 0x9d, 0x1a, 0xd6,
/* 70 */ 0x78, 0xc8, 0x9b, 0x72, 0x53, 0xdb, 0x68, 0xe3, 0xe9, 0x5c, 0x79, 0x3b, 0x92, 0x44, 0xb0, 0x4b,
/* 80 */ 0x5d, 0x34, 0xae, 0xfc, 0xde, 0xa4, 0xd2, 0xe0, 0x99, 0xc0, 0x98, 0x39, 0xf4, 0x3c, 0x87, 0x64,
/* 90 */ 0x40, 0x8d, 0xf1, 0x77, 0x5e, 0x81, 0x17, 0x1d, 0x0e, 0x7d, 0xd5, 0xda, 0x14, 0xbe, 0x48, 0xa5,
/* a0 */ 0xc7, 0x74, 0x45, 0xa2, 0x85, 0x33, 0x25, 0x05, 0x8c, 0x08, 0x27, 0xe2, 0xd9, 0xd8, 0x75, 0x12,
/* b0 */ 0x41, 0x0d, 0x0b, 0x6b, 0x7f, 0xdc, 0xbd, 0xc3, 0x7b, 0x3f, 0xf2, 0xc9, 0xd0, 0xa6, 0x2d, 0xf0,
/* c0 */ 0x15, 0xf3, 0x2b, 0x29, 0xbf, 0xa7, 0x47, 0xba, 0x63, 0x1b, 0x50, 0x38, 0x62, 0x0c, 0x6a, 0xb9,
/* d0 */ 0xc4, 0xd4, 0xc6, 0xa0, 0x65, 0x8e, 0x2a, 0x56, 0x5a, 0xbb, 0xff, 0xf6, 0x61, 0xfe, 0x16, 0x82,
/* e0 */ 0xa9, 0xea, 0x03, 0x4e, 0x11, 0x4a, 0x95, 0x8a, 0x2c, 0xc2, 0xe5, 0xb4, 0x54, 0xca, 0x97, 0x93,
/* f0 */ 0x35, 0xa8, 0xd1, 0x58, 0x31, 0x22, 0x06, 0x49, 0x28, 0x90, 0x1c, 0xb1, 0xbc, 0x2e, 0x80, 0xf9,
};
