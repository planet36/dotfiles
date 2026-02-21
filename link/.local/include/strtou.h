// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// string to unsigned int
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/c/string/byte/strtoul
*/

#pragma once

#include <limits.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

static unsigned int
strtou(const char* s)
{
    const unsigned long i = strtoul(s, nullptr, 0);
    return (i > UINT_MAX) ? UINT_MAX : (unsigned int)i;
}

#ifdef __cplusplus
} // extern "C"
#endif
