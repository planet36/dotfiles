// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// C++ wrappers for fast square root functions
/**
\file
\author Steven Ward
*/

#pragma once

#include "sse_sqrt.h"

namespace sse
{

float
sqrt(float x)
{
	return sse_sqrtf(x);
}

double
sqrt(double x)
{
	return sse_sqrt(x);
}

float
rsqrt(float x)
{
	return sse_rsqrtf(x);
}

}
