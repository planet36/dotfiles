// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// wyhash64
/**
\file
\author Steven Ward
\sa https://github.com/wangyi-fudan/wyhash/blob/master/wyhash.h
\sa https://github.com/rurban/smhasher/blob/master/wyhash.h
*/

#pragma once

#include "mum_mix.hpp"
#include "wyprimes.hpp"

constexpr uint64_t
wyhash64(uint64_t a, uint64_t b)
{
	a ^= _wyp[0];
	b ^= _wyp[1];
	mum(a, b);
	a ^= _wyp[0];
	b ^= _wyp[1];
	mum(a, b);
	return a ^ b;
}
