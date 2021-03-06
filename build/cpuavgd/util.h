// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

// https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html
// automatically close file stream
#define ACFILE(varname) __attribute__((cleanup(cleanup_close_file))) FILE* varname = NULL

char* escape_char(int ch);
unsigned int strtou(const char* s);
void cleanup_close_file(FILE** fpp);
int pscanf(const char *path, const char *fmt, ...);
double timespec_to_double(const struct timespec *ts);
struct timeval milliseconds_to_timeval(unsigned int milliseconds);
int calc_idle(uintmax_t *idle, uintmax_t *sum);
