// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// convert string to integer
/**
\file
\author Steven Ward
*/

#pragma once

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static int8_t
strtoi8(const char* s)
{
    const intmax_t i = strtoimax(s, nullptr, 0);
    return i < INT8_MIN ? INT8_MIN : (i > INT8_MAX ? INT8_MAX : (int8_t)i);
}

static int16_t
strtoi16(const char* s)
{
    const intmax_t i = strtoimax(s, nullptr, 0);
    return i < INT16_MIN ? INT16_MIN : (i > INT16_MAX ? INT16_MAX : (int16_t)i);
}

static int32_t
strtoi32(const char* s)
{
    const intmax_t i = strtoimax(s, nullptr, 0);
    return i < INT32_MIN ? INT32_MIN : (i > INT32_MAX ? INT32_MAX : (int32_t)i);
}

static int64_t
strtoi64(const char* s)
{
    const intmax_t i = strtoimax(s, nullptr, 0);
    return i < INT64_MIN ? INT64_MIN : (i > INT64_MAX ? INT64_MAX : (int64_t)i);
}

static uint8_t
strtou8(const char* s)
{
    const uintmax_t i = strtoumax(s, nullptr, 0);
    return i > UINT8_MAX ? UINT8_MAX : (uint8_t)i;
}

static uint16_t
strtou16(const char* s)
{
    const uintmax_t i = strtoumax(s, nullptr, 0);
    return i > UINT16_MAX ? UINT16_MAX : (uint16_t)i;
}

static uint32_t
strtou32(const char* s)
{
    const uintmax_t i = strtoumax(s, nullptr, 0);
    return i > UINT32_MAX ? UINT32_MAX : (uint32_t)i;
}

static uint64_t
strtou64(const char* s)
{
    const uintmax_t i = strtoumax(s, nullptr, 0);
    return i > UINT64_MAX ? UINT64_MAX : (uint64_t)i;
}

#ifdef __cplusplus
} // extern "C"
#endif
