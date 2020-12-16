# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=C0103
# pylint: disable=C0114
# pylint: disable=C0301
# pylint: disable=R1705
# pylint: disable=W0311

import re

__version__ = '2020-12-02'

# http://www.regular-expressions.info/unicode.html
# http://unicode.org/reports/tr18/#Categories
# http://unicode.org/reports/tr44/#GC_Values_Table


def str_to_int(s):
	'''Convert the string to an int if possible.'''
	# See 'isdecimal-isdigit-isnumeric.py' for why isdecimal is used.

	# Strings that are True for isdigit() and isnumeric() aren't always convertible to int.
	if s.isdecimal():
		return (int(s), s)
	else:
		return s


def split_ints(s, pattern):
	'''Split the string about groups of decimal characters.'''
	#return [str_to_int(c) for c in regex.split(pattern, s)]
	#return [str_to_int(c) for c in pattern.split(s)]
	return tuple(str_to_int(c) for c in pattern.split(s))

# http://nedbatchelder.com/blog/200712/human_sorting.html
# Sort the given list in the way that humans expect.
# Turn a string into a list of string and number chunks.

capture_many_decimal_pattern = re.compile(r'(\d+)')

key = lambda s: (split_ints(s.strip().casefold(), capture_many_decimal_pattern), s)
