// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// An array that contains every \c std::byte value
/**
\file
\author Steven Ward
*/

#pragma once

#include <array>
#include <cstddef>

inline constexpr std::array<std::byte, 256> all_bytes{
    std::byte{0x00},
    std::byte{0x01},
    std::byte{0x02},
    std::byte{0x03},
    std::byte{0x04},
    std::byte{0x05},
    std::byte{0x06},
    std::byte{0x07},
    std::byte{0x08},
    std::byte{0x09},
    std::byte{0x0a},
    std::byte{0x0b},
    std::byte{0x0c},
    std::byte{0x0d},
    std::byte{0x0e},
    std::byte{0x0f},
    std::byte{0x10},
    std::byte{0x11},
    std::byte{0x12},
    std::byte{0x13},
    std::byte{0x14},
    std::byte{0x15},
    std::byte{0x16},
    std::byte{0x17},
    std::byte{0x18},
    std::byte{0x19},
    std::byte{0x1a},
    std::byte{0x1b},
    std::byte{0x1c},
    std::byte{0x1d},
    std::byte{0x1e},
    std::byte{0x1f},
    std::byte{0x20},
    std::byte{0x21},
    std::byte{0x22},
    std::byte{0x23},
    std::byte{0x24},
    std::byte{0x25},
    std::byte{0x26},
    std::byte{0x27},
    std::byte{0x28},
    std::byte{0x29},
    std::byte{0x2a},
    std::byte{0x2b},
    std::byte{0x2c},
    std::byte{0x2d},
    std::byte{0x2e},
    std::byte{0x2f},
    std::byte{0x30},
    std::byte{0x31},
    std::byte{0x32},
    std::byte{0x33},
    std::byte{0x34},
    std::byte{0x35},
    std::byte{0x36},
    std::byte{0x37},
    std::byte{0x38},
    std::byte{0x39},
    std::byte{0x3a},
    std::byte{0x3b},
    std::byte{0x3c},
    std::byte{0x3d},
    std::byte{0x3e},
    std::byte{0x3f},
    std::byte{0x40},
    std::byte{0x41},
    std::byte{0x42},
    std::byte{0x43},
    std::byte{0x44},
    std::byte{0x45},
    std::byte{0x46},
    std::byte{0x47},
    std::byte{0x48},
    std::byte{0x49},
    std::byte{0x4a},
    std::byte{0x4b},
    std::byte{0x4c},
    std::byte{0x4d},
    std::byte{0x4e},
    std::byte{0x4f},
    std::byte{0x50},
    std::byte{0x51},
    std::byte{0x52},
    std::byte{0x53},
    std::byte{0x54},
    std::byte{0x55},
    std::byte{0x56},
    std::byte{0x57},
    std::byte{0x58},
    std::byte{0x59},
    std::byte{0x5a},
    std::byte{0x5b},
    std::byte{0x5c},
    std::byte{0x5d},
    std::byte{0x5e},
    std::byte{0x5f},
    std::byte{0x60},
    std::byte{0x61},
    std::byte{0x62},
    std::byte{0x63},
    std::byte{0x64},
    std::byte{0x65},
    std::byte{0x66},
    std::byte{0x67},
    std::byte{0x68},
    std::byte{0x69},
    std::byte{0x6a},
    std::byte{0x6b},
    std::byte{0x6c},
    std::byte{0x6d},
    std::byte{0x6e},
    std::byte{0x6f},
    std::byte{0x70},
    std::byte{0x71},
    std::byte{0x72},
    std::byte{0x73},
    std::byte{0x74},
    std::byte{0x75},
    std::byte{0x76},
    std::byte{0x77},
    std::byte{0x78},
    std::byte{0x79},
    std::byte{0x7a},
    std::byte{0x7b},
    std::byte{0x7c},
    std::byte{0x7d},
    std::byte{0x7e},
    std::byte{0x7f},
    std::byte{0x80},
    std::byte{0x81},
    std::byte{0x82},
    std::byte{0x83},
    std::byte{0x84},
    std::byte{0x85},
    std::byte{0x86},
    std::byte{0x87},
    std::byte{0x88},
    std::byte{0x89},
    std::byte{0x8a},
    std::byte{0x8b},
    std::byte{0x8c},
    std::byte{0x8d},
    std::byte{0x8e},
    std::byte{0x8f},
    std::byte{0x90},
    std::byte{0x91},
    std::byte{0x92},
    std::byte{0x93},
    std::byte{0x94},
    std::byte{0x95},
    std::byte{0x96},
    std::byte{0x97},
    std::byte{0x98},
    std::byte{0x99},
    std::byte{0x9a},
    std::byte{0x9b},
    std::byte{0x9c},
    std::byte{0x9d},
    std::byte{0x9e},
    std::byte{0x9f},
    std::byte{0xa0},
    std::byte{0xa1},
    std::byte{0xa2},
    std::byte{0xa3},
    std::byte{0xa4},
    std::byte{0xa5},
    std::byte{0xa6},
    std::byte{0xa7},
    std::byte{0xa8},
    std::byte{0xa9},
    std::byte{0xaa},
    std::byte{0xab},
    std::byte{0xac},
    std::byte{0xad},
    std::byte{0xae},
    std::byte{0xaf},
    std::byte{0xb0},
    std::byte{0xb1},
    std::byte{0xb2},
    std::byte{0xb3},
    std::byte{0xb4},
    std::byte{0xb5},
    std::byte{0xb6},
    std::byte{0xb7},
    std::byte{0xb8},
    std::byte{0xb9},
    std::byte{0xba},
    std::byte{0xbb},
    std::byte{0xbc},
    std::byte{0xbd},
    std::byte{0xbe},
    std::byte{0xbf},
    std::byte{0xc0},
    std::byte{0xc1},
    std::byte{0xc2},
    std::byte{0xc3},
    std::byte{0xc4},
    std::byte{0xc5},
    std::byte{0xc6},
    std::byte{0xc7},
    std::byte{0xc8},
    std::byte{0xc9},
    std::byte{0xca},
    std::byte{0xcb},
    std::byte{0xcc},
    std::byte{0xcd},
    std::byte{0xce},
    std::byte{0xcf},
    std::byte{0xd0},
    std::byte{0xd1},
    std::byte{0xd2},
    std::byte{0xd3},
    std::byte{0xd4},
    std::byte{0xd5},
    std::byte{0xd6},
    std::byte{0xd7},
    std::byte{0xd8},
    std::byte{0xd9},
    std::byte{0xda},
    std::byte{0xdb},
    std::byte{0xdc},
    std::byte{0xdd},
    std::byte{0xde},
    std::byte{0xdf},
    std::byte{0xe0},
    std::byte{0xe1},
    std::byte{0xe2},
    std::byte{0xe3},
    std::byte{0xe4},
    std::byte{0xe5},
    std::byte{0xe6},
    std::byte{0xe7},
    std::byte{0xe8},
    std::byte{0xe9},
    std::byte{0xea},
    std::byte{0xeb},
    std::byte{0xec},
    std::byte{0xed},
    std::byte{0xee},
    std::byte{0xef},
    std::byte{0xf0},
    std::byte{0xf1},
    std::byte{0xf2},
    std::byte{0xf3},
    std::byte{0xf4},
    std::byte{0xf5},
    std::byte{0xf6},
    std::byte{0xf7},
    std::byte{0xf8},
    std::byte{0xf9},
    std::byte{0xfa},
    std::byte{0xfb},
    std::byte{0xfc},
    std::byte{0xfd},
    std::byte{0xfe},
    std::byte{0xff},
};
