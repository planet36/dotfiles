// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Macro to create low-pass bitmask
/**
\file
\author Steven Ward
*/

#pragma once

#define UINT_SET_BITS(N) ((1ULL << (N)) - 1ULL)
