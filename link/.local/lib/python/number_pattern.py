# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=line-too-long

'''Regular expression patterns for numbers'''

__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

# https://en.cppreference.com/w/cpp/language/integer_literal

int_dec = '[-+]?[0-9]+' # (plain 0 is allowed)
int_oct = '[-+]?0[0-7]*'
int_hex = '[-+]?0[Xx][0-9A-Fa-f]+'
int_bin = '[-+]?0[Bb][01]+'

# https://en.cppreference.com/w/cpp/language/floating_literal

float_dec = r'[-+]?(?:[0-9]+\.?[0-9]*|\.[0-9]+)(?:[Ee][-+]?[0-9]+)?'
float_hex = r'[-+]?0[Xx](?:[0-9A-Fa-f]+\.?[0-9A-Fa-f]*|\.[0-9A-Fa-f]+)(?:[Pp][-+]?[0-9]+)'
# (hex-exponent is mandatory)

# test cases for float patterns:
# https://regex101.com/r/ntU5j7/3
# https://regex101.com/r/2gxcLV/1
