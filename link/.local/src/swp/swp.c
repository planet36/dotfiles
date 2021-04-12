// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <fcntl.h>           /* Definition of AT_* constants */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if (argc < 1)
	{
		fprintf(stderr, "missing file operands\n");
		return EXIT_FAILURE;
	}
	else if (argc < 2)
	{
		fprintf(stderr, "%s: missing file operands\n", argv[0]);
		return EXIT_FAILURE;
	}
	else if (argc < 3)
	{
		fprintf(stderr, "%s: missing file operand after \"%s\"\n", argv[0], argv[1]);
		return EXIT_FAILURE;
	}

	if (renameat2(AT_FDCWD, argv[1], AT_FDCWD, argv[2], RENAME_EXCHANGE) < 0)
	{
		perror("renameat2");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
