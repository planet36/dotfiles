// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

# pragma once

// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005fexpect
#define likely(expr) __builtin_expect(!!(expr), 1)
#define unlikely(expr) __builtin_expect(!!(expr), 0)
