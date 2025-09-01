// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// aliases for std::chrono built-in types
/**
* \file
* \author Steven Ward
* \sa https://philippegroarke.com/posts/2018/chrono_for_humans/
*/

#pragma once

#include <chrono>

using fnanoseconds  = std::chrono::duration<float, std::chrono::nanoseconds ::period>;
using fmicroseconds = std::chrono::duration<float, std::chrono::microseconds::period>;
using fmilliseconds = std::chrono::duration<float, std::chrono::milliseconds::period>;
using fseconds      = std::chrono::duration<float, std::chrono::seconds     ::period>;
using fminutes      = std::chrono::duration<float, std::chrono::minutes     ::period>;
using fhours        = std::chrono::duration<float, std::chrono::hours       ::period>;
using fdays         = std::chrono::duration<float, std::chrono::days        ::period>;
using fweeks        = std::chrono::duration<float, std::chrono::weeks       ::period>;
using fmonths       = std::chrono::duration<float, std::chrono::months      ::period>;
using fyears        = std::chrono::duration<float, std::chrono::years       ::period>;

using dnanoseconds  = std::chrono::duration<double, std::chrono::nanoseconds ::period>;
using dmicroseconds = std::chrono::duration<double, std::chrono::microseconds::period>;
using dmilliseconds = std::chrono::duration<double, std::chrono::milliseconds::period>;
using dseconds      = std::chrono::duration<double, std::chrono::seconds     ::period>;
using dminutes      = std::chrono::duration<double, std::chrono::minutes     ::period>;
using dhours        = std::chrono::duration<double, std::chrono::hours       ::period>;
using ddays         = std::chrono::duration<double, std::chrono::days        ::period>;
using dweeks        = std::chrono::duration<double, std::chrono::weeks       ::period>;
using dmonths       = std::chrono::duration<double, std::chrono::months      ::period>;
using dyears        = std::chrono::duration<double, std::chrono::years       ::period>;
