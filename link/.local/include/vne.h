// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Von Neumann extractor
/**
* \file
* \author Steven Ward
* \sa https://en.wikipedia.org/wiki/Randomness_extractor#Von_Neumann_extractor
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

inline int
von_neumann_extractor(unsigned char x)
{
    switch (x & 0b11)
    {
    case 0b10: return 0;
    case 0b01: return 1;
    default: return -1;
    }
}

#ifdef __cplusplus
} // extern "C"
#endif
