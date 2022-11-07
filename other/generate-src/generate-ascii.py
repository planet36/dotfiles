# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=line-too-long

"""
Usage:
python3 generate-ascii.py > ascii.hpp
"""

import collections
import datetime as dt
import os.path
import platform

import ascii_const

now = dt.datetime.now(dt.timezone.utc)
author = 'Steven Ward'
this_license = 'OSL-3.0'
brief_description = 'ascii strings'
generated_by_file_name = os.path.basename(__file__)
generated_datetime = now.isoformat(timespec='seconds')
system_info = platform.platform()

print(fr'''// SPDX-FileCopyrightText: {author}
// SPDX-License-Identifier: {this_license}

/// {brief_description}
/**
\file
\author {author}
\sa https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap07.html#tag_07_03_01
\sa https://en.cppreference.com/w/cpp/string/byte
\sa https://docs.python.org/3/library/string.html
*/

// Generated by "{generated_by_file_name}" on {generated_datetime}
// system information: {system_info}

#pragma once

#include <array>
#include <string>
#include <string_view>
''')

'''
Translation table to be used in str.translate().
https://docs.python.org/3/library/stdtypes.html#str.maketrans
https://docs.python.org/3/library/stdtypes.html#str.translate
https://en.cppreference.com/w/c/language/escape
https://en.cppreference.com/w/cpp/language/escape
https://eel.is/c++draft/lex.ccon#:simple-escape-sequence-char
'''
c_esc_seq_hex_trans_table = str.maketrans({
	0x00: r'\x00',
	0x01: r'\x01',
	0x02: r'\x02',
	0x03: r'\x03',
	0x04: r'\x04',
	0x05: r'\x05',
	0x06: r'\x06',
	0x07: r'\a'  ,
	0x08: r'\b'  ,
	0x09: r'\t'  ,
	0x0A: r'\n'  ,
	0x0B: r'\v'  ,
	0x0C: r'\f'  ,
	0x0D: r'\r'  ,
	0x0E: r'\x0E',
	0x0F: r'\x0F',
	0x10: r'\x10',
	0x11: r'\x11',
	0x12: r'\x12',
	0x13: r'\x13',
	0x14: r'\x14',
	0x15: r'\x15',
	0x16: r'\x16',
	0x17: r'\x17',
	0x18: r'\x18',
	0x19: r'\x19',
	0x1A: r'\x1A',
	0x1B: r'\x1B',
	0x1C: r'\x1C',
	0x1D: r'\x1D',
	0x1E: r'\x1E',
	0x1F: r'\x1F',
	0x20: r' '   ,
	0x21: r'!'   ,
	0x22: r'\"'  ,
	0x23: r'#'   ,
	0x24: r'$'   ,
	0x25: r'%'   ,
	0x26: r'&'   ,
	0x27: r'\''  ,
	0x28: r'('   ,
	0x29: r')'   ,
	0x2A: r'*'   ,
	0x2B: r'+'   ,
	0x2C: r','   ,
	0x2D: r'-'   ,
	0x2E: r'.'   ,
	0x2F: r'/'   ,
	0x30: r'0'   ,
	0x31: r'1'   ,
	0x32: r'2'   ,
	0x33: r'3'   ,
	0x34: r'4'   ,
	0x35: r'5'   ,
	0x36: r'6'   ,
	0x37: r'7'   ,
	0x38: r'8'   ,
	0x39: r'9'   ,
	0x3A: r':'   ,
	0x3B: r';'   ,
	0x3C: r'<'   ,
	0x3D: r'='   ,
	0x3E: r'>'   ,
	0x3F: r'?'   ,
	0x40: r'@'   ,
	0x41: r'A'   ,
	0x42: r'B'   ,
	0x43: r'C'   ,
	0x44: r'D'   ,
	0x45: r'E'   ,
	0x46: r'F'   ,
	0x47: r'G'   ,
	0x48: r'H'   ,
	0x49: r'I'   ,
	0x4A: r'J'   ,
	0x4B: r'K'   ,
	0x4C: r'L'   ,
	0x4D: r'M'   ,
	0x4E: r'N'   ,
	0x4F: r'O'   ,
	0x50: r'P'   ,
	0x51: r'Q'   ,
	0x52: r'R'   ,
	0x53: r'S'   ,
	0x54: r'T'   ,
	0x55: r'U'   ,
	0x56: r'V'   ,
	0x57: r'W'   ,
	0x58: r'X'   ,
	0x59: r'Y'   ,
	0x5A: r'Z'   ,
	0x5B: r'['   ,
	0x5C: r'\\'  ,
	0x5D: r']'   ,
	0x5E: r'^'   ,
	0x5F: r'_'   ,
	0x60: r'`'   ,
	0x61: r'a'   ,
	0x62: r'b'   ,
	0x63: r'c'   ,
	0x64: r'd'   ,
	0x65: r'e'   ,
	0x66: r'f'   ,
	0x67: r'g'   ,
	0x68: r'h'   ,
	0x69: r'i'   ,
	0x6A: r'j'   ,
	0x6B: r'k'   ,
	0x6C: r'l'   ,
	0x6D: r'm'   ,
	0x6E: r'n'   ,
	0x6F: r'o'   ,
	0x70: r'p'   ,
	0x71: r'q'   ,
	0x72: r'r'   ,
	0x73: r's'   ,
	0x74: r't'   ,
	0x75: r'u'   ,
	0x76: r'v'   ,
	0x77: r'w'   ,
	0x78: r'x'   ,
	0x79: r'y'   ,
	0x7A: r'z'   ,
	0x7B: r'{'   ,
	0x7C: r'|'   ,
	0x7D: r'}'   ,
	0x7E: r'~'   ,
	0x7F: r'\x7F',
})

var_name_to_var_value = collections.OrderedDict()

var_name_to_var_value['ascii_all'             ] = ascii_const.ascii_all
var_name_to_var_value['ascii_uppercase'       ] = ascii_const.ascii_uppercase
var_name_to_var_value['ascii_lowercase'       ] = ascii_const.ascii_lowercase
var_name_to_var_value['ascii_alphabetical'    ] = ascii_const.ascii_alphabetical
var_name_to_var_value['ascii_decimal'         ] = ascii_const.ascii_decimal
var_name_to_var_value['ascii_alphanumeric'    ] = ascii_const.ascii_alphanumeric
var_name_to_var_value['ascii_word'            ] = ascii_const.ascii_word
var_name_to_var_value['ascii_hexadecimal'     ] = ascii_const.ascii_hexadecimal
var_name_to_var_value['ascii_octal'           ] = ascii_const.ascii_octal
var_name_to_var_value['ascii_binary'          ] = ascii_const.ascii_binary
var_name_to_var_value['ascii_whitespace'      ] = ascii_const.ascii_whitespace
var_name_to_var_value['ascii_blank'           ] = ascii_const.ascii_blank
var_name_to_var_value['ascii_visible'         ] = ascii_const.ascii_visible
var_name_to_var_value['ascii_printable'       ] = ascii_const.ascii_printable
var_name_to_var_value['ascii_control'         ] = ascii_const.ascii_control
var_name_to_var_value['ascii_punctuation'     ] = ascii_const.ascii_punctuation
var_name_to_var_value['ascii_non_uppercase'   ] = ascii_const.ascii_not_uppercase
var_name_to_var_value['ascii_non_lowercase'   ] = ascii_const.ascii_not_lowercase
var_name_to_var_value['ascii_non_alphabetical'] = ascii_const.ascii_not_alphabetical
var_name_to_var_value['ascii_non_decimal'     ] = ascii_const.ascii_not_decimal
var_name_to_var_value['ascii_non_alphanumeric'] = ascii_const.ascii_not_alphanumeric
var_name_to_var_value['ascii_non_word'        ] = ascii_const.ascii_not_word
var_name_to_var_value['ascii_non_hexadecimal' ] = ascii_const.ascii_not_hexadecimal
var_name_to_var_value['ascii_non_octal'       ] = ascii_const.ascii_not_octal
var_name_to_var_value['ascii_non_binary'      ] = ascii_const.ascii_not_binary
var_name_to_var_value['ascii_non_whitespace'  ] = ascii_const.ascii_not_whitespace
var_name_to_var_value['ascii_non_blank'       ] = ascii_const.ascii_not_blank
var_name_to_var_value['ascii_non_visible'     ] = ascii_const.ascii_not_visible
var_name_to_var_value['ascii_non_printable'   ] = ascii_const.ascii_not_printable
var_name_to_var_value['ascii_non_control'     ] = ascii_const.ascii_not_control
var_name_to_var_value['ascii_non_punctuation' ] = ascii_const.ascii_not_punctuation

max_name_len = max(len(name) for name in var_name_to_var_value.keys())

for (name, value) in var_name_to_var_value.items():
	cpp_name_sv = name + "_sv"
	value_translated = value.translate(c_esc_seq_hex_trans_table)
	print(f'inline constexpr std::string_view {cpp_name_sv:{max_name_len+3}} {{"{value_translated}", {len(value)}}};')
print()

for name in var_name_to_var_value.keys():
	cpp_name_sv = name + "_sv"
	cpp_name_s = name + "_s"
	print(f'const std::string {cpp_name_s:{max_name_len+2}} {{{cpp_name_sv:{max_name_len+3}}}};')
print()

print(fr'''/**
\sa https://en.cppreference.com/w/c/language/escape
\sa https://en.cppreference.com/w/cpp/language/escape
\sa https://eel.is/c++draft/lex.ccon#:simple-escape-sequence-char
*/
inline constexpr std::array<std::string_view, {len(ascii_const.ascii_all)}>
c_simple_esc_seq_hex{{''')
for c in ascii_const.ascii_all:
	s = 'R"(' + c.translate(c_esc_seq_hex_trans_table) + ')"'
	print(f'\t{s:9},')
print("};")
