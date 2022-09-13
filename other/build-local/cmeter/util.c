// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

#include <ctype.h>
//#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// https://stackoverflow.com/a/16659263
double
clamp(double x, double min, double max)
{
	double xx = x < min ? min : x;
	return xx > max ? max : xx;
	//return fmin(fmax(x, min), max);
}

// Not re-entrant
char*
escape_char(int ch)
{
	static char buf[32] = {'\0'};
	(void)snprintf(buf, sizeof(buf), isprint(ch) ? "%c" : "%#X", ch);
	return buf;
}
