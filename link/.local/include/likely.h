// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Macros wrapping __builtin_expect
/**
\file
\author Steven Ward
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005fexpect
// https://llvm.org/docs/BranchWeightMetadata.html#built-in-expect-instructions
#define likely(expr)   __builtin_expect(!!(expr), 1)
#define unlikely(expr) __builtin_expect(!!(expr), 0)

#ifdef __cplusplus
} // extern "C"
#endif
