// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// wyhash primes
/**
\file
\author Steven Ward
\sa https://github.com/rurban/smhasher/blob/master/wyhash.h#L159
*/

#pragma once

#include <cstdint>

namespace
{
constexpr uint64_t _wyp[4] = {
	0xa0761d6478bd642f, // prime (popcount = 32)
	0xe7037ed1a0b428db, // prime (popcount = 32)
	0x8ebc6af09c88c6e3, // prime (popcount = 32)
	0x589965cc75374cc3, // prime (popcount = 32)
};
}
