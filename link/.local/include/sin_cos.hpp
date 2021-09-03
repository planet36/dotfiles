// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// sin_cos functions that use references instead of pointers
/**
\file
\author Steven Ward
\sa https://www.gnu.org/software/libc/manual/html_node/Trig-Functions.html#index-sincos
*/

#pragma once

#include <cmath>
#include <concepts>

#if defined(sincosf) && defined(sincos) && defined(sincosl)

void sin_cos(const float x_rad, float& s, float& c) { ::sincosf(x_rad, &s, &c); }
void sin_cos(const double x_rad, double& s, double& c) { ::sincos(x_rad, &s, &c); }
void sin_cos(const long double x_rad, long double& s, long double& c) { ::sincosl(x_rad, &s, &c); }

#else

template <std::floating_point T>
void sin_cos(const T x_rad, T& s, T& c) { s = std::sin(x_rad); c = std::cos(x_rad); }

#endif
