// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// automatically close file stream
/**
\file
\author Steven Ward
\sa https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html
*/

#pragma once

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ACFILEPTR __attribute__((cleanup(cleanup_close_file_ptr))) FILE*

// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-nonnull-function-attribute
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

#define ACFD __attribute__((cleanup(cleanup_close_fd))) int

// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-nonnull-function-attribute
static inline void
cleanup_close_fd(const int* fd_ptr) [[gnu::nonnull]]
{
    (void)close(*fd_ptr);
}

#ifdef __cplusplus
} // extern "C"
#endif
