// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// automatically free string
/**
\file
\author Steven Ward
\sa https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html

Example usage
\code{.c}
const char* s = "Hello, world!";
// Use "afstr" as the declaration of a dynamically allocated string.
afstr s2 = strdup(s);
// When s2 goes out of scope, it will be automatically freed.
\endcode
*/

#pragma once

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define afstr __attribute__((cleanup(cleanup_free_str))) char*

static void
cleanup_free_str(char** spp)
{
	free(*spp);
}

#ifdef __cplusplus
} // extern "C"
#endif
