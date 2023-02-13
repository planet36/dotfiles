// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// string to unsigned int
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/c/string/byte/strtoul
*/

#pragma once

#include <limits.h>
#include <stdlib.h>

static
unsigned int
strtou(const char* s)
{
	unsigned long i = strtoul(s, NULL, 0);
	if (i > UINT_MAX)
		i = UINT_MAX;
	return (unsigned int)i;
}
