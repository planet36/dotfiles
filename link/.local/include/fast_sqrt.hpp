// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// C++ wrappers for fast square root functions
/**
\file
\author Steven Ward
*/

#pragma once

#include "fast_sqrt.h"

namespace fast
{

float sqrt(float x)
{
	return fast_sqrtf(x);
}

double sqrt(double x)
{
	return fast_sqrt(x);
}

float rsqrt(float x)
{
	return fast_rsqrtf(x);
}

double rsqrt(double x)
{
	return 1 / fast_sqrt(x);
}

}
