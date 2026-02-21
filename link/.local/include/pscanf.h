// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Scan the contents of a path
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/c/io/fscanf
*/

#pragma once

#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Adapted from my slstatus
// https://github.com/planet36/slstatus/blob/main/util.c

static int
pscanf(const char* path, const char* fmt, ...)
{
    FILE* fp;
    va_list ap;
    int n;

    fp = fopen(path, "r");
    if (fp == nullptr)
    {
        warn("fopen '%s'", path);
        return -1;
    }
    va_start(ap, fmt);
    n = vfscanf(fp, fmt, ap);
    va_end(ap);
    if (fclose(fp) < 0)
    {
        err(EXIT_FAILURE, "fclose");
    }

    return (n == EOF) ? -1 : n;
}

#ifdef __cplusplus
} // extern "C"
#endif
