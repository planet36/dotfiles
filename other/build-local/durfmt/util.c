// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

#include <ctype.h>
#include <stdio.h>

// Not re-entrant
char*
escape_char(int ch)
{
	static char buf[32] = {'\0'};
	(void)snprintf(buf, sizeof(buf), isprint(ch) ? "%c" : "%#X", ch);
	return buf;
}
