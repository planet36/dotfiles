// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

#pragma once

#include <stdint.h>
#include <sys/time.h>

char* escape_char(int ch);
unsigned int strtou(const char* s);
int pscanf(const char *path, const char *fmt, ...);
double timespec_to_double(const struct timespec *ts);
struct timeval milliseconds_to_timeval(unsigned int milliseconds);
