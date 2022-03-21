// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

#include <limits.h>
#include <stdlib.h>

int strtoi(const char* s)
{
	long i = strtol(s, NULL, 0);

	if (i < INT_MIN)
		i = INT_MIN;
	else if (i > INT_MAX)
		i = INT_MAX;

	return (int)i;
}
