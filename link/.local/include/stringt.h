// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// string copy & concatenate, and report truncation
/**
* \file
* \author Steven Ward
* \sa https://nrk.neocities.org/articles/not-a-fan-of-strlcpy
* Inspired by https://software.codidact.com/posts/285946
*/

#pragma once

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/// String copy, report truncation
/**
* DESCRIPTION
*   Copy \a src to \a dst, including the terminating NUL character.
*   If \a src cannot be copied completely to \a dst (i.e. truncation happens)
*   and \a trunc_at is not \c nullptr, then \a *trunc_at will point to the
*   first character in \a src that was not copied to \a dst.
*
* PREREQUISITES
*   \a buf_last points to the last character in the buffer containing \a dst.
*   \a src is NUL-terminated.
*
* CAVEATS
*   If memory areas \a dst and \a src overlap, the results are undefined.
*
* RETURN VALUE
*   Return a pointer to the new terminating NUL character of \a dst.
*
* SEE ALSO
*   \c memccpy(3)
*/
[[nodiscard]] static char*
strtcpy(char* dst, char* buf_last, const char* src, const char** trunc_at)
    [[gnu::returns_nonnull]]
{
    //[[assume(dst != nullptr)]];
    //[[assume(src != nullptr)]];
    //[[assume(buf_last != nullptr)]];
    //[[assume(dst <= buf_last)]];

    const size_t gap = (size_t)(buf_last - dst + 1); // includes the terminating NUL character

    char* after_nul = (char*)memccpy(dst, src, '\0', gap);

    if (after_nul != nullptr)
        return after_nul - 1;

    // truncation happened: NUL character not found within gap characters
    // in src

    if (trunc_at != nullptr)
        *trunc_at = &src[gap - 1];

    *buf_last = '\0';
    return buf_last;
}

/// String concatenate, report truncation
/**
* See docs of \c strtcpy for details.
*
* PREREQUISITES
*   \a dst is NUL-terminated.
*/
[[nodiscard]] static char*
strtcat(char* dst, char* buf_last, const char* src, const char** trunc_at)
    [[gnu::returns_nonnull]]
{
    dst += strlen(dst);
    return strtcpy(dst, buf_last, src, trunc_at);
}

#ifdef __cplusplus
} // extern "C"
#endif
