// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include <err.h>
#include <fcntl.h> /* Definition of AT_* constants */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
		errx(EXIT_FAILURE, "missing file operands");

	if (argc == 2)
		errx(EXIT_FAILURE, "missing file operand after \"%s\"", argv[1]);

	if (renameat2(AT_FDCWD, argv[1], AT_FDCWD, argv[2], RENAME_EXCHANGE) < 0)
		err(EXIT_FAILURE, "renameat2");

	return EXIT_SUCCESS;
}
