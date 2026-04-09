// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// automatically close file stream, file descriptor
/**
* \file
* \author Steven Ward
* \sa https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-cleanup
* \sa https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-nonnull
*/

#pragma once

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define ACFILEPTR(IDENTIFIER) FILE* IDENTIFIER [[gnu::cleanup(cleanup_close_file_ptr)]]

static void
cleanup_close_file_ptr(FILE** fp_ptr) [[gnu::nonnull]]
{
    if (*fp_ptr != nullptr)
    {
        if (fclose(*fp_ptr) < 0)
        {
            *fp_ptr = nullptr;
            err(EXIT_FAILURE, "fclose");
        }
        *fp_ptr = nullptr;
    }
}

#define ACFD(IDENTIFIER) int IDENTIFIER [[gnu::cleanup(cleanup_close_fd)]]

static inline void
cleanup_close_fd(const int* fd_ptr) [[gnu::nonnull]]
{
    (void)close(*fd_ptr);
}

#if defined(__cplusplus)
} // extern "C"
#endif
