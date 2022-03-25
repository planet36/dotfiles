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

simple_esc_seq_dict = {
    ord('\a'): r'\\a', # alert
    ord('\b'): r'\\b', # backspace
    ord('\t'): r'\\t', # horizontal tab
    ord('\n'): r'\\n', # new line
    ord('\v'): r'\\v', # vertical tab
    ord('\f'): r'\\f', # form feed
    ord('\r'): r'\\r', # carriage return
}

for i in range(128):
    if i in simple_esc_seq_dict:
        print(f'"{simple_esc_seq_dict[i]}",')
    elif not isprint(i):
        print(fr'"\\{i:03o}",')
    else:
        print('"",')
\endcode
*/
inline constexpr std::array<std::string_view, 128> ascii_cntrl_simple_esc_seq_oct{
	"\\000", //   0
	"\\001", //   1
	"\\002", //   2
	"\\003", //   3
	"\\004", //   4
	"\\005", //   5
	"\\006", //   6
	"\\a"  , //   7
	"\\b"  , //   8
	"\\t"  , //   9
	"\\n"  , //  10
	"\\v"  , //  11
	"\\f"  , //  12
	"\\r"  , //  13
	"\\016", //  14
	"\\017", //  15
	"\\020", //  16
	"\\021", //  17
	"\\022", //  18
	"\\023", //  19
	"\\024", //  20
	"\\025", //  21
	"\\026", //  22
	"\\027", //  23
	"\\030", //  24
	"\\031", //  25
	"\\032", //  26
	"\\033", //  27
	"\\034", //  28
	"\\035", //  29
	"\\036", //  30
	"\\037", //  31
	""     , //  32
	""     , //  33
	""     , //  34
	""     , //  35
	""     , //  36
	""     , //  37
	""     , //  38
	""     , //  39
	""     , //  40
	""     , //  41
	""     , //  42
	""     , //  43
	""     , //  44
	""     , //  45
	""     , //  46
	""     , //  47
	""     , //  48
	""     , //  49
	""     , //  50
	""     , //  51
	""     , //  52
	""     , //  53
	""     , //  54
	""     , //  55
	""     , //  56
	""     , //  57
	""     , //  58
	""     , //  59
	""     , //  60
	""     , //  61
	""     , //  62
	""     , //  63
	""     , //  64
	""     , //  65
	""     , //  66
	""     , //  67
	""     , //  68
	""     , //  69
	""     , //  70
	""     , //  71
	""     , //  72
	""     , //  73
	""     , //  74
	""     , //  75
	""     , //  76
	""     , //  77
	""     , //  78
	""     , //  79
	""     , //  80
	""     , //  81
	""     , //  82
	""     , //  83
	""     , //  84
	""     , //  85
	""     , //  86
	""     , //  87
	""     , //  88
	""     , //  89
	""     , //  90
	""     , //  91
	""     , //  92
	""     , //  93
	""     , //  94
	""     , //  95
	""     , //  96
	""     , //  97
	""     , //  98
	""     , //  99
	""     , // 100
	""     , // 101
	""     , // 102
	""     , // 103
	""     , // 104
	""     , // 105
	""     , // 106
	""     , // 107
	""     , // 108
	""     , // 109
	""     , // 110
	""     , // 111
	""     , // 112
	""     , // 113
	""     , // 114
	""     , // 115
	""     , // 116
	""     , // 117
	""     , // 118
	""     , // 119
	""     , // 120
	""     , // 121
	""     , // 122
	""     , // 123
	""     , // 124
	""     , // 125
	""     , // 126
	"\\177", // 127
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

simple_esc_seq_dict = {
    ord('\a'): r'\\a', # alert
    ord('\b'): r'\\b', # backspace
    ord('\t'): r'\\t', # horizontal tab
    ord('\n'): r'\\n', # new line
    ord('\v'): r'\\v', # vertical tab
    ord('\f'): r'\\f', # form feed
    ord('\r'): r'\\r', # carriage return
}

for i in range(128):
    if i in simple_esc_seq_dict:
        print(f'"{simple_esc_seq_dict[i]}",')
    elif not isprint(i):
        print(fr'"\\x{i:02x}",')
    else:
        print('"",')
\endcode
*/
inline constexpr std::array<std::string_view, 128> ascii_cntrl_simple_esc_seq_hex{
	"\\x00", //   0
	"\\x01", //   1
	"\\x02", //   2
	"\\x03", //   3
	"\\x04", //   4
	"\\x05", //   5
	"\\x06", //   6
	"\\a"  , //   7
	"\\b"  , //   8
	"\\t"  , //   9
	"\\n"  , //  10
	"\\v"  , //  11
	"\\f"  , //  12
	"\\r"  , //  13
	"\\x0e", //  14
	"\\x0f", //  15
	"\\x10", //  16
	"\\x11", //  17
	"\\x12", //  18
	"\\x13", //  19
	"\\x14", //  20
	"\\x15", //  21
	"\\x16", //  22
	"\\x17", //  23
	"\\x18", //  24
	"\\x19", //  25
	"\\x1a", //  26
	"\\x1b", //  27
	"\\x1c", //  28
	"\\x1d", //  29
	"\\x1e", //  30
	"\\x1f", //  31
	""     , //  32
	""     , //  33
	""     , //  34
	""     , //  35
	""     , //  36
	""     , //  37
	""     , //  38
	""     , //  39
	""     , //  40
	""     , //  41
	""     , //  42
	""     , //  43
	""     , //  44
	""     , //  45
	""     , //  46
	""     , //  47
	""     , //  48
	""     , //  49
	""     , //  50
	""     , //  51
	""     , //  52
	""     , //  53
	""     , //  54
	""     , //  55
	""     , //  56
	""     , //  57
	""     , //  58
	""     , //  59
	""     , //  60
	""     , //  61
	""     , //  62
	""     , //  63
	""     , //  64
	""     , //  65
	""     , //  66
	""     , //  67
	""     , //  68
	""     , //  69
	""     , //  70
	""     , //  71
	""     , //  72
	""     , //  73
	""     , //  74
	""     , //  75
	""     , //  76
	""     , //  77
	""     , //  78
	""     , //  79
	""     , //  80
	""     , //  81
	""     , //  82
	""     , //  83
	""     , //  84
	""     , //  85
	""     , //  86
	""     , //  87
	""     , //  88
	""     , //  89
	""     , //  90
	""     , //  91
	""     , //  92
	""     , //  93
	""     , //  94
	""     , //  95
	""     , //  96
	""     , //  97
	""     , //  98
	""     , //  99
	""     , // 100
	""     , // 101
	""     , // 102
	""     , // 103
	""     , // 104
	""     , // 105
	""     , // 106
	""     , // 107
	""     , // 108
	""     , // 109
	""     , // 110
	""     , // 111
	""     , // 112
	""     , // 113
	""     , // 114
	""     , // 115
	""     , // 116
	""     , // 117
	""     , // 118
	""     , // 119
	""     , // 120
	""     , // 121
	""     , // 122
	""     , // 123
	""     , // 124
	""     , // 125
	""     , // 126
	"\\x7f", // 127
};
