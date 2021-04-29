// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

#include <limits.h>
#include <stdlib.h>

unsigned short strtous(const char* s)
{
	unsigned long i = strtoul(s, NULL, 0);

	if (i > USHRT_MAX) i = USHRT_MAX;

	return (unsigned short)i;
}

// https://stackoverflow.com/a/16659263
double clamp(double x, double min, double max)
{
	double xx = x < min ? min : x;
	return xx > max ? max : xx;
	//return fmin(fmax(x, min), max);
}
