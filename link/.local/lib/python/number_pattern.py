# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# pylint: disable=invalid-name

'''Regular expression patterns for numbers'''

__author__ = 'Steven Ward'
__license__ = 'MPL-2.0'

SIGN_OPT = '[-+]?'
HEX_PREFIX = '0[Xx]'

FRACTIONAL_CONSTANT = r'(?:[0-9]+\.?[0-9]*|\.[0-9]+)'
EXPONENT_PART = '(?:[Ee]' + SIGN_OPT + '[0-9]+)'
EXPONENT_PART_OPT = EXPONENT_PART + '?'

HEX_FRACTIONAL_CONSTANT = r'(?:[0-9A-Fa-f]+\.?[0-9A-Fa-f]*|\.[0-9A-Fa-f]+)'
BIN_EXPONENT_PART = '(?:[Pp]' + SIGN_OPT + '[0-9]+)'

# https://en.cppreference.com/w/cpp/language/integer_literal
# https://eel.is/c++draft/lex.icon#nt:integer-literal

INT_DEC = SIGN_OPT + '[0-9]+' # (plain 0 is allowed)
INT_OCT = SIGN_OPT + '0[0-7]*'
INT_HEX = SIGN_OPT + HEX_PREFIX + '[0-9A-Fa-f]+'
INT_BIN = SIGN_OPT + '0[Bb][01]+'

UINT_DEC = '[0-9]+' # (plain 0 is allowed)
UINT_OCT = '0[0-7]*'
UINT_HEX = HEX_PREFIX + '[0-9A-Fa-f]+'
UINT_BIN = '0[Bb][01]+'

# https://en.cppreference.com/w/cpp/language/floating_literal
# https://eel.is/c++draft/lex.fcon#nt:decimal-floating-point-literal
# https://eel.is/c++draft/lex.fcon#nt:hexadecimal-floating-point-literal

FLOAT_FIXED = SIGN_OPT + FRACTIONAL_CONSTANT
FLOAT_SCIENTIFIC = SIGN_OPT + FRACTIONAL_CONSTANT + EXPONENT_PART
FLOAT = SIGN_OPT + FRACTIONAL_CONSTANT + EXPONENT_PART_OPT
FLOAT_HEX = SIGN_OPT + HEX_PREFIX + HEX_FRACTIONAL_CONSTANT + BIN_EXPONENT_PART
# (hex-exponent-part is mandatory)

# test cases for float patterns:
# https://regex101.com/r/ntU5j7/3
# https://regex101.com/r/2gxcLV/1
