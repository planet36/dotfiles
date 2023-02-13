// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Copied from
// https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/tools/lib/string.c#n118
// https://elixir.bootlin.com/linux/latest/source/tools/lib/string.c#L118

/**
 * skip_spaces - Removes leading whitespace from @str.
 * @str: The string to be stripped.
 *
 * Returns a pointer to the first non-whitespace character in @str.
 */
char*
skip_spaces(const char* str)
{
	while (isspace(*str))
	{
		++str;
	}
	return (char*)str;
}

/**
 * strim - Removes leading and trailing whitespace from @s.
 * @s: The string to be stripped.
 *
 * Note that the first trailing whitespace is replaced with a %NUL-terminator
 * in the given string @s. Returns a pointer to the first non-whitespace
 * character in @s.
 */
char*
strim(char* s)
{
	size_t size;
	char* end;

	size = strlen(s);
	if (!size)
		return s;

	end = s + size - 1;
	while (end >= s && isspace(*end))
	{
		end--;
	}
	*(end + 1) = '\0';

	return skip_spaces(s);
}

void
strtolower(char* s)
{
	for (; *s; ++s) { *s = (char)tolower(*s); }
}

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
