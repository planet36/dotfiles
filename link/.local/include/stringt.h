// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

# pragma once

#include <stdint.h>
#include <string.h>
#include <wchar.h>

#include "likely.h"

inline static size_t
_strtcat_helper(char* restrict dest, const char* restrict src, size_t dest_sz, size_t dest_len)
{
	const size_t src_sz = strlen(src) + 1; // includes terminating NUL character

	if (unlikely(dest_len > SIZE_MAX - src_sz))
		// dest_len + src_sz overflows
		return SIZE_MAX;

	if (dest_len + src_sz > dest_sz)
		return dest_len + src_sz - dest_sz;

	(void)memcpy(dest + dest_len, src, src_sz);
	return 0;
}

/** String concatenate without truncation
 *
 * DESCRIPTION
 *   Concatenate src to dest, including the terminating NUL character.
 *
 * PREREQUISITES
 *   dest must be NUL-terminated.
 *   src must be NUL-terminated.
 *   dest_sz is the capacity (in characters) of dest.
 *
 * CAVEATS
 *   If the strings overlap, the behavior is undefined.
 *   If dest_sz is insufficient, the operation will not be performed, and a positive integer will be returned.
 *
 * RETURN VALUE
 *   0  : Success
 *   >0 : Failure
 *     The operation was not performed because dest_sz was insufficient.
 *     The returned value is the number of characters dest must be enlarged by for the operation to be performed.
 */
static size_t
strtcat(char* restrict dest, const char* restrict src, size_t dest_sz)
{
	return _strtcat_helper(dest, src, dest_sz, strlen(dest));
}

/** String copy without truncation
 *
 * DESCRIPTION
 *   Copy src to dest, including the terminating NUL character.
 *
 * PREREQUISITES
 *   src must be NUL-terminated.
 *   dest_sz is the capacity (in characters) of dest.
 *
 * CAVEATS
 *   If the strings overlap, the behavior is undefined.
 *   If dest_sz is insufficient, the operation will not be performed, and a positive integer will be returned.
 *
 * RETURN VALUE
 *   0  : Success
 *   >0 : Failure
 *     The operation was not performed because dest_sz was insufficient.
 *     The returned value is the number of characters dest must be enlarged by for the operation to be performed.
 */
static size_t
strtcpy(char* restrict dest, const char* restrict src, size_t dest_sz)
{
	return _strtcat_helper(dest, src, dest_sz, 0);
}

inline static size_t
_wstrtcat_helper(wchar_t* restrict dest, const wchar_t* restrict src, size_t dest_sz, size_t dest_len)
{
	const size_t src_sz = wcslen(src) + 1; // includes terminating NUL wide character

	if (unlikely(dest_len > SIZE_MAX - src_sz))
		// dest_len + src_sz overflows
		return SIZE_MAX;

	if (dest_len + src_sz > dest_sz)
		return dest_len + src_sz - dest_sz;

	(void)wmemcpy(dest + dest_len, src, src_sz);
	return 0;
}

/** Wide string concatenate without truncation
 *
 * DESCRIPTION
 *   Concatenate src to dest, including the terminating NUL wide character.
 *
 * PREREQUISITES
 *   dest must be NUL-terminated.
 *   src must be NUL-terminated.
 *   dest_sz is the capacity (in wide characters) of dest.
 *
 * CAVEATS
 *   If the strings overlap, the behavior is undefined.
 *   If dest_sz is insufficient, the operation will not be performed, and a positive integer will be returned.
 *
 * RETURN VALUE
 *   0  : Success
 *   >0 : Failure
 *     The operation was not performed because dest_sz was insufficient.
 *     The returned value is the number of wide characters dest must be enlarged by for the operation to be performed.
 */
static size_t
wstrtcat(wchar_t* restrict dest, const wchar_t* restrict src, size_t dest_sz)
{
	return _wstrtcat_helper(dest, src, dest_sz, wcslen(dest));
}

/** Wide string copy without truncation
 *
 * DESCRIPTION
 *   Copy src to dest, including the terminating NUL wide character.
 *
 * PREREQUISITES
 *   src must be NUL-terminated.
 *   dest_sz is the capacity (in wide characters) of dest.
 *
 * CAVEATS
 *   If the strings overlap, the behavior is undefined.
 *   If dest_sz is insufficient, the operation will not be performed, and a positive integer will be returned.
 *
 * RETURN VALUE
 *   0  : Success
 *   >0 : Failure
 *     The operation was not performed because dest_sz was insufficient.
 *     The returned value is the number of wide characters dest must be enlarged by for the operation to be performed.
 */
static size_t
wstrtcpy(wchar_t* restrict dest, const wchar_t* restrict src, size_t dest_sz)
{
	return _wstrtcat_helper(dest, src, dest_sz, 0);
}
