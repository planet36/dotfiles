// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// This file contains the ASCII character set as a \c std::array, \c std::string, and \c std::string_view.
/**
\file
\author Steven Ward
*/

#pragma once

#include <array>
#include <string>
#include <string_view>

inline constexpr std::array<char, 128> ascii_array {
	'\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F',
	'\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F',
	'\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27', '\x28', '\x29', '\x2A', '\x2B', '\x2C', '\x2D', '\x2E', '\x2F',
	'\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37', '\x38', '\x39', '\x3A', '\x3B', '\x3C', '\x3D', '\x3E', '\x3F',
	'\x40', '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47', '\x48', '\x49', '\x4A', '\x4B', '\x4C', '\x4D', '\x4E', '\x4F',
	'\x50', '\x51', '\x52', '\x53', '\x54', '\x55', '\x56', '\x57', '\x58', '\x59', '\x5A', '\x5B', '\x5C', '\x5D', '\x5E', '\x5F',
	'\x60', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67', '\x68', '\x69', '\x6A', '\x6B', '\x6C', '\x6D', '\x6E', '\x6F',
	'\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77', '\x78', '\x79', '\x7A', '\x7B', '\x7C', '\x7D', '\x7E', '\x7F',
};

inline const std::string ascii_string{ascii_array.cbegin(), ascii_array.cend()};

inline constexpr std::string_view ascii_string_view{ascii_array.cbegin(), ascii_array.cend()};

/**
\sa https://eel.is/c++draft/lex.ccon#:simple-escape-sequence
\sa https://eel.is/c++draft/gram.lex#:simple-escape-sequence
\sa https://en.cppreference.com/w/cpp/string/byte/iscntrl
\sa https://en.cppreference.com/w/cpp/string/byte/isprint
Python snippet to generate the array
\code{.py}
def isprint(i: int):
    return i >= 32 and i < 127

simple_escape_sequence_dict = {
    ord('\a'): r'\\a', # alert
    ord('\b'): r'\\b', # backspace
    ord('\t'): r'\\t', # horizontal tab
    ord('\n'): r'\\n', # new line
    ord('\v'): r'\\v', # vertical tab
    ord('\f'): r'\\f', # form feed
    ord('\r'): r'\\r', # carriage return
}

for i in range(128):
    if i in simple_escape_sequence_dict:
        print(f'"{simple_escape_sequence_dict[i]}",')
    elif not isprint(i):
        print(fr'"\\{i:03o}",')
    else:
        print('"",')
\endcode
*/
inline constexpr std::array<std::string_view, 128> ascii_cntrl_simple_escape_seq_oct{
	"\\000",
	"\\001",
	"\\002",
	"\\003",
	"\\004",
	"\\005",
	"\\006",
	"\\a",
	"\\b",
	"\\t",
	"\\n",
	"\\v",
	"\\f",
	"\\r",
	"\\016",
	"\\017",
	"\\020",
	"\\021",
	"\\022",
	"\\023",
	"\\024",
	"\\025",
	"\\026",
	"\\027",
	"\\030",
	"\\031",
	"\\032",
	"\\033",
	"\\034",
	"\\035",
	"\\036",
	"\\037",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"\\177",
};

/**
\sa https://eel.is/c++draft/lex.ccon#:simple-escape-sequence
\sa https://eel.is/c++draft/gram.lex#:simple-escape-sequence
\sa https://en.cppreference.com/w/cpp/string/byte/iscntrl
\sa https://en.cppreference.com/w/cpp/string/byte/isprint
Python snippet to generate the array
\code{.py}
def isprint(i: int):
    return i >= 32 and i < 127

simple_escape_sequence_dict = {
    ord('\a'): r'\\a', # alert
    ord('\b'): r'\\b', # backspace
    ord('\t'): r'\\t', # horizontal tab
    ord('\n'): r'\\n', # new line
    ord('\v'): r'\\v', # vertical tab
    ord('\f'): r'\\f', # form feed
    ord('\r'): r'\\r', # carriage return
}

for i in range(128):
    if i in simple_escape_sequence_dict:
        print(f'"{simple_escape_sequence_dict[i]}",')
    elif not isprint(i):
        print(fr'"\\x{i:02x}",')
    else:
        print('"",')
\endcode
*/
inline constexpr std::array<std::string_view, 128> ascii_cntrl_simple_escape_seq_hex{
	"\\x00",
	"\\x01",
	"\\x02",
	"\\x03",
	"\\x04",
	"\\x05",
	"\\x06",
	"\\a",
	"\\b",
	"\\t",
	"\\n",
	"\\v",
	"\\f",
	"\\r",
	"\\x0e",
	"\\x0f",
	"\\x10",
	"\\x11",
	"\\x12",
	"\\x13",
	"\\x14",
	"\\x15",
	"\\x16",
	"\\x17",
	"\\x18",
	"\\x19",
	"\\x1a",
	"\\x1b",
	"\\x1c",
	"\\x1d",
	"\\x1e",
	"\\x1f",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"\\x7f",
};
