# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=line-too-long

'''Regular expression patterns for numbers'''

__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

import re

# https://en.cppreference.com/w/cpp/language/integer_literal

int_dec = re.compile('[-+]?[0-9]+', re.ASCII)  # (plain 0 is allowed)
int_oct = re.compile('[-+]?0[0-7]*', re.ASCII)
int_hex = re.compile('[-+]?0[Xx][0-9A-Fa-f]+', re.ASCII)
int_bin = re.compile('[-+]?0[Bb][01]+', re.ASCII)

# https://en.cppreference.com/w/cpp/language/floating_literal

float_dec = re.compile(r'[-+]?(?:[0-9]+\.?[0-9]*|\.[0-9]+)(?:[Ee][-+]?[0-9]+)?', re.ASCII)
float_hex = re.compile(r'[-+]?0[Xx](?:[0-9A-Fa-f]+\.?[0-9A-Fa-f]*|\.[0-9A-Fa-f]+)(?:[Pp][-+]?[0-9]+)', re.ASCII)
# (hex-exponent is mandatory)

# test cases for float patterns:
# https://regex101.com/r/ntU5j7/3
# https://regex101.com/r/2gxcLV/1
