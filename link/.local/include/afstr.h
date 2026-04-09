// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// automatically free string
/**
* \file
* \author Steven Ward
* \sa https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-cleanup
*
* Example usage
* \code{.c}
const char* s = "Hello, world!";
// Use "AFSTR" as the declaration of a dynamically allocated string.
AFSTR(s2) = strdup(s);
// When s2 goes out of scope, it will be automatically freed.
\endcode
*/

#pragma once

#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define AFSTR(IDENTIFIER) char* IDENTIFIER [[gnu::cleanup(cleanup_free_str)]]

static void
cleanup_free_str(char** spp)
{
    free(*spp);
}

#if defined(__cplusplus)
} // extern "C"
#endif
