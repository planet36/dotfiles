// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Stringize a macro argument
/**
\file
\author Steven Ward
\sa https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html
\sa https://en.wikipedia.org/wiki/C_preprocessor#Token_stringification
*/

#pragma once

#define XSTR(s) STR(s)
#define STR(s) #s
