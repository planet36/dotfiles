// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#include "util.h"

//#include <math.h>

// https://stackoverflow.com/a/16659263
double
clamp(double x, double min, double max)
{
	double xx = x < min ? min : x;
	return xx > max ? max : xx;
	//return fmin(fmax(x, min), max);
}
