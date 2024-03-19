// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get a view to the object as a span of bytes
/**
\file
\author Steven Ward
*/

#pragma once

#include <cstdint>
#include <memory>
#include <span>

#define AS_BYTE_SPAN(X) \
std::span{static_cast<const uint8_t*>(static_cast<const void*>(std::addressof(X))), sizeof(X)}
