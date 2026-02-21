// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// wyhash32, wyhash64 functions
/**
* \file
* \author Steven Ward
* \sa https://github.com/wangyi-fudan/wyhash/blob/master/wyhash.h
* \sa https://github.com/wangyi-fudan/wyhash/blob/master/wyhash32.h
* \sa https://github.com/rurban/smhasher/blob/master/wyhash.h
* \sa https://github.com/rurban/smhasher/blob/master/wyhash32.h
*/

#pragma once

#include "mum.hpp"
#include "wyprimes.hpp"

constexpr uint32_t
wyhash32(uint32_t a, uint32_t b)
{
    // https://github.com/wangyi-fudan/wyhash/blob/master/wyhash32.h#L13
    constexpr uint32_t p0 = 0x53c5ca59; // prime (popcount = 16)
    constexpr uint32_t p1 = 0x74743c1b; // prime (popcount = 16)
    a ^= p0;
    b ^= p1;
    mul(a, b);
    a ^= p0;
    b ^= p1;
    mul(a, b);
    return a ^ b;
}

constexpr uint64_t
wyhash64(uint64_t a, uint64_t b)
{
    a ^= _wyp[0];
    b ^= _wyp[1];
    mul(a, b);
    a ^= _wyp[0];
    b ^= _wyp[1];
    mul(a, b);
    return a ^ b;
}
