// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// automatically close file stream
/**
\file
\author Steven Ward
\sa https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html
*/

#pragma once

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#define ACFILE(varname) \
	__attribute__((cleanup(cleanup_close_file))) FILE* varname = NULL

static
void
cleanup_close_file(FILE** fpp)
{
	if (*fpp != NULL)
	{
		if (fclose(*fpp) < 0)
		{
			*fpp = NULL;
			err(EXIT_FAILURE, "fclose");
		}
		*fpp = NULL;
	}
}
