// SPDX-FileCopyrightText: Sebastiano Vigna (vigna@acm.org)
// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: CC0-1.0

/// splitmix64 PRNG
/**
\file
\author Steven Ward
\sa https://prng.di.unimi.it/splitmix64.c
*/

#pragma once

#include "def_urbg_class_details.hpp"

/** This is a fixed-increment version of Java 8's SplittableRandom generator
 * See https://dl.acm.org/doi/10.1145/2714064.2660195 and
 * https://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html
 *
 * It is a very fast generator passing BigCrush, and it can be useful if
 * for some reason you absolutely want 64 bits of state.
 */
struct splitmix64
{
	using state_type = uint64_t;
	using result_type = uint64_t;

DEF_URBG_CLASS_DETAILS(splitmix64)

	result_type next()
	{
		auto z = (s += 0x9e3779b97f4a7c15); // not prime
		z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9; // not prime
		z = (z ^ (z >> 27)) * 0x94d049bb133111eb; // not prime
		return z ^ (z >> 31);
	}
};
