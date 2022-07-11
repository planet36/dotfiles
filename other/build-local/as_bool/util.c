// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

#include <ctype.h>
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
		++str;
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
		end--;
	*(end + 1) = '\0';

	return skip_spaces(s);
}

void
strtolower(char* s)
{
	for (; *s; ++s) { *s = tolower(*s); }
}
