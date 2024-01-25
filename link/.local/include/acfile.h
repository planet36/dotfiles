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

#define acfile \
	__attribute__((cleanup(cleanup_close_file))) FILE*

static void
cleanup_close_file(FILE** fpp)
{
	if (*fpp != nullptr)
	{
		if (fclose(*fpp) < 0)
		{
			*fpp = nullptr;
			err(EXIT_FAILURE, "fclose");
		}
		*fpp = nullptr;
	}
}
