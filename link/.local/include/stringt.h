// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// string copy & concatenate, and report truncation
/**
* \file
* \author Steven Ward
* \sa https://nrk.neocities.org/articles/not-a-fan-of-strlcpy
* Inspired by https://software.codidact.com/posts/285946
* \sa https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-returns_005fnonnull
*/

#pragma once

#include <string.h>

#if defined(__cplusplus)
extern "C" {
#endif

/// String copy, report truncation
/**
* DESCRIPTION
*   Copy \a src to \a dst, including the terminating NUL character.
*   If \a src cannot be copied completely to \a dst (i.e., truncation happens),
*   \a trunc_at is not \c nullptr, and \a *trunc_at is \c nullptr, then
*   \a *trunc_at will point to the first character in \a src that was not
*   copied to \a dst.  Otherwise, \a *trunc_at is left unchanged.
*
*   In a chain of calls that share \a trunc_at, \a *trunc_at therefore records
*   the first truncation.  A later call cannot move it to a string that was
*   never copied at all.
*
* PREREQUISITES
*   \a buf_last points to the last character in the buffer containing \a dst.
*   \a src is NUL-terminated.
*   If \a trunc_at is not \c nullptr, \a *trunc_at is \c nullptr before the
*   first call of a chain.
*
* CAVEATS
*   If memory areas \a dst and \a src overlap, the results are undefined.
*
* RETURN VALUE
*   Return a pointer to the new terminating NUL character of \a dst.
*   That pointer is \a buf_last both when \a src exactly fills the buffer and
*   when truncation happens, so only \a *trunc_at tells the two apart.  With a
*   \c nullptr \a trunc_at, truncation cannot be detected.
*
* SEE ALSO
*   \c memccpy(3)
*/
[[nodiscard, gnu::returns_nonnull]] static inline char*
strtcpy(char* dst, char* buf_last, const char* src, const char** trunc_at)
{
    //[[assume(dst != nullptr)]];
    //[[assume(src != nullptr)]];
    //[[assume(buf_last != nullptr)]];
    //[[assume(dst <= buf_last)]];

    const size_t gap = (size_t)(buf_last - dst + 1); // includes the terminating NUL character

    char* after_nul = (char*)memccpy(dst, src, '\0', gap);

    if (after_nul != nullptr)
        return after_nul - 1;

    // No NUL character was found within gap characters in src, so
    // truncation happened.

    // src holds at least gap characters here, but the clang analyzer does not model memccpy,
    // so it assumes src can be shorter.
    if (trunc_at != nullptr && *trunc_at == nullptr)
        *trunc_at = &src[gap - 1]; // NOLINT(clang-analyzer-security.ArrayBound)

    *buf_last = '\0';
    return buf_last;
}

/// String concatenate, report truncation
/**
* See docs of \c strtcpy for details.
*
* CAVEATS
*   If \a dst has no NUL character at or before \a buf_last, then nothing is
*   copied, and \a *buf_last is set to NUL.  Truncation is reported as though
*   no character of \a src fit, so under the rules of \c strtcpy, \a *trunc_at
*   will point to \a src if it was \c nullptr.
*/
[[nodiscard, gnu::returns_nonnull]] static inline char*
strtcat(char* dst, char* buf_last, const char* src, const char** trunc_at)
{
    const size_t gap = (size_t)(buf_last - dst + 1);

    // An unbounded search could find a NUL character past buf_last, and the gap that strtcpy
    // computes from there would wrap to a huge size.
    char* nul = (char*)memchr(dst, '\0', gap);

    if (nul == nullptr)
    {
        if (trunc_at != nullptr && *trunc_at == nullptr)
            *trunc_at = src;

        *buf_last = '\0';
        return buf_last;
    }

    return strtcpy(nul, buf_last, src, trunc_at);
}

#if defined(__cplusplus)
} // extern "C"
#endif
