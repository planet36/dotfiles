// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// square root functions that call inline SSE assembly code
/**
\file
\author Steven Ward
\sa https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html#Extended-Asm
\sa https://gcc.gnu.org/onlinedocs/gcc/Modifiers.html#Modifiers
\sa https://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html#Machine-Constraints
\sa https://en.cppreference.com/w/cpp/language/asm
\sa https://en.cppreference.com/w/c/language/asm
\sa https://www.felixcloutier.com/x86/sqrtsd
\sa https://www.felixcloutier.com/x86/sqrtss
\sa https://www.felixcloutier.com/x86/rsqrtss
\sa https://board.flatassembler.net/topic.php?p=209795
\sa https://stackoverflow.com/a/1528751
\sa https://gcc.gnu.org/onlinedocs/gcc/Alternate-Keywords.html#Alternate-Keywords
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

inline double
sse_sqrt(double x)
{
	__asm__ volatile ("sqrtsd %0, %0" : "+x" (x));
	return x;
}

inline float
sse_sqrtf(float x)
{
	__asm__ volatile ("sqrtss %0, %0" : "+x" (x));
	return x;
}

inline float
sse_rsqrtf(float x)
{
	__asm__ volatile ("rsqrtss %0, %0" : "+x" (x));
	return x;
}

#ifdef __cplusplus
} // extern "C"
#endif
