// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

#include <stdlib.h>
#include <string.h>

// Evaluate the given string as a boolean
int main(int argc, char* argv[])
{
	int result = EXIT_SUCCESS;

	if (argc >= 2)
	{
		char* s = strim(argv[1]);

		strtolower(s);

		// https://docs.python.org/3/library/configparser.html#configparser.ConfigParser.getboolean
		// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Boolean
		if (*s == '\0') // empty
		{
			result = EXIT_FAILURE;
		}
		else if (
			strcmp(s, "1") == 0 ||
			strcmp(s, "yes") == 0 ||
			strcmp(s, "y") == 0 ||
			strcmp(s, "true") == 0 ||
			strcmp(s, "on") == 0)
		{
			result = EXIT_SUCCESS;
		}
		else if (
			strcmp(s, "0") == 0 ||
			strcmp(s, "no") == 0 ||
			strcmp(s, "n") == 0 ||
			strcmp(s, "false") == 0 ||
			strcmp(s, "off") == 0)
		{
			result = EXIT_FAILURE;
		}
		else if (
			strcmp(s, "null") == 0 ||
			strcmp(s, "nil") == 0 ||
			strcmp(s, "none") == 0 ||
			strcmp(s, "nan") == 0 ||
			strcmp(s, "undefined") == 0 ||
			strcmp(s, "-0") == 0)
		{
			result = EXIT_FAILURE;
		}
	} // else: vacuous truth

	return result;
}
