// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// sincos functions for floating point args
/**
\file
\author Steven Ward
\sa https://www.gnu.org/software/libc/manual/html_node/Trig-Functions.html#index-sincos
*/

#pragma once

#include <cmath>
#include <type_traits>

#if defined(sincos)

void sincos(const float x_rad, float& s, float& c) { ::sincosf(x_rad, &s, &c); }
void sincos(const double x_rad, double& s, double& c) { ::sincos(x_rad, &s, &c); }
void sincos(const long double x_rad, long double& s, long double& c) { ::sincosl(x_rad, &s, &c); }

#else

template <typename T>
requires std::is_floating_point_v<T>
void sincos(const T x_rad, T& s, T& c) { s = std::sin(x_rad); c = std::cos(x_rad); }

#endif
