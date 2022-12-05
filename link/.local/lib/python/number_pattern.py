# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=line-too-long

'''Regular expression patterns for numbers'''

__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

# https://en.cppreference.com/w/cpp/language/integer_literal

INT_DEC = '[-+]?[0-9]+' # (plain 0 is allowed)
INT_OCT = '[-+]?0[0-7]*'
INT_HEX = '[-+]?0[Xx][0-9A-Fa-f]+'
INT_BIN = '[-+]?0[Bb][01]+'

UINT_DEC = '[0-9]+' # (plain 0 is allowed)
UINT_OCT = '0[0-7]*'
UINT_HEX = '0[Xx][0-9A-Fa-f]+'
UINT_BIN = '0[Bb][01]+'

# https://en.cppreference.com/w/cpp/language/floating_literal

FLOAT = r'[-+]?(?:[0-9]+\.?[0-9]*|\.[0-9]+)(?:[Ee][-+]?[0-9]+)?'
FLOAT_HEX = r'[-+]?0[Xx](?:[0-9A-Fa-f]+\.?[0-9A-Fa-f]*|\.[0-9A-Fa-f]+)(?:[Pp][-+]?[0-9]+)'
# (hex-exponent is mandatory)

# test cases for float patterns:
# https://regex101.com/r/ntU5j7/3
# https://regex101.com/r/2gxcLV/1
