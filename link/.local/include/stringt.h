// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// safe strncat, strncpy, wcsncat, wcsncpy (without truncation)
/**
\file
\author Steven Ward
\sa https://nrk.neocities.org/articles/not-a-fan-of-strlcpy
*/

#pragma once

#include "likely.h"

#include <stdint.h>
#include <string.h>
#include <wchar.h>

inline static size_t
strtcat_helper(char* restrict dest,
               const char* restrict src,
               size_t dest_sz,
               size_t dest_len)
{
	// includes terminating NUL character
	const size_t src_sz = strlen(src) + 1;

	if (unlikely(dest_len > SIZE_MAX - src_sz))
		// dest_len + src_sz overflows
		return SIZE_MAX;

	if (dest_len + src_sz > dest_sz)
		return dest_len + src_sz - dest_sz;

	(void)memcpy(dest + dest_len, src, src_sz);
	return 0;
}

/// String concatenate without truncation
/**
 * DESCRIPTION
 *   Concatenate \a src to \a dest, including the terminating NUL character.
 *
 * PREREQUISITES
 *   dest must be NUL-terminated.
 *   \a src must be NUL-terminated.
 *   \a dest_sz is the capacity (in characters) of \a dest.
 *
 * CAVEATS
 *   If the strings overlap, the behavior is undefined.
 *   If \a dest_sz is insufficient, the operation will not be performed, and a
 *   positive integer will be returned.
 *
 * RETURN VALUE
 *   0  : Success
 *   >0 : Failure
 *     The operation was not performed because \a dest_sz was insufficient.
 *     The returned value is the number of characters \a dest must be enlarged by
 *     for the operation to be performed.
 */
static size_t
strtcat(char* restrict dest, const char* restrict src, size_t dest_sz)
{
	return strtcat_helper(dest, src, dest_sz, strlen(dest));
}

/// String copy without truncation
/**
 * DESCRIPTION
 *   Copy \a src to \a dest, including the terminating NUL character.
 *
 * PREREQUISITES
 *   \a src must be NUL-terminated.
 *   \a dest_sz is the capacity (in characters) of \a dest.
 *
 * CAVEATS
 *   If the strings overlap, the behavior is undefined.
 *   If \a dest_sz is insufficient, the operation will not be performed, and a
 *   positive integer will be returned.
 *
 * RETURN VALUE
 *   0  : Success
 *   >0 : Failure
 *     The operation was not performed because \a dest_sz was insufficient.
 *     The returned value is the number of characters \a dest must be enlarged by
 *     for the operation to be performed.
 */
static size_t
strtcpy(char* restrict dest, const char* restrict src, size_t dest_sz)
{
	return strtcat_helper(dest, src, dest_sz, 0);
}

inline static size_t
wstrtcat_helper(wchar_t* restrict dest,
                const wchar_t* restrict src,
                size_t dest_sz,
                size_t dest_len)
{
	// includes terminating NUL wide character
	const size_t src_sz = wcslen(src) + 1;

	if (unlikely(dest_len > SIZE_MAX - src_sz))
		// dest_len + src_sz overflows
		return SIZE_MAX;

	if (dest_len + src_sz > dest_sz)
		return dest_len + src_sz - dest_sz;

	(void)wmemcpy(dest + dest_len, src, src_sz);
	return 0;
}

/// Wide string concatenate without truncation
/**
 * DESCRIPTION
 *   Concatenate \a src to \a dest, including the terminating NUL wide character.
 *
 * PREREQUISITES
 *   \a dest must be NUL-terminated.
 *   \a src must be NUL-terminated.
 *   \a dest_sz is the capacity (in wide characters) of \a dest.
 *
 * CAVEATS
 *   If the strings overlap, the behavior is undefined.
 *   If \a dest_sz is insufficient, the operation will not be performed, and a
 *   positive integer will be returned.
 *
 * RETURN VALUE
 *   0  : Success
 *   >0 : Failure
 *     The operation was not performed because \a dest_sz was insufficient.
 *     The returned value is the number of wide characters \a dest must be
 *     enlarged by for the operation to be performed.
 */
static size_t
wstrtcat(wchar_t* restrict dest, const wchar_t* restrict src, size_t dest_sz)
{
	return wstrtcat_helper(dest, src, dest_sz, wcslen(dest));
}

/// Wide string copy without truncation
/**
 * DESCRIPTION
 *   Copy \a src to \a dest, including the terminating NUL wide character.
 *
 * PREREQUISITES
 *   \a src must be NUL-terminated.
 *   \a dest_sz is the capacity (in wide characters) of \a dest.
 *
 * CAVEATS
 *   If the strings overlap, the behavior is undefined.
 *   If \a dest_sz is insufficient, the operation will not be performed, and a
 *   positive integer will be returned.
 *
 * RETURN VALUE
 *   0  : Success
 *   >0 : Failure
 *     The operation was not performed because \a dest_sz was insufficient.
 *     The returned value is the number of wide characters \a dest must be
 *     enlarged by for the operation to be performed.
 */
static size_t
wstrtcpy(wchar_t* restrict dest, const wchar_t* restrict src, size_t dest_sz)
{
	return wstrtcat_helper(dest, src, dest_sz, 0);
}
