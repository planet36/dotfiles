# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=C0103
# pylint: disable=C0114
# pylint: disable=W0311

__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

import bisect
import math

# https://docs.python.org/dev/library/bisect.html#searching-sorted-lists

def index(a, x):
	'''Locate the leftmost value exactly equal to x'''
	i = bisect.bisect_left(a, x)
	if i != len(a) and a[i] == x:
		return i
	raise ValueError

def find_lt(a, x):
	'''Find rightmost value less than x'''
	i = bisect.bisect_left(a, x)
	if i:
		return a[i-1]
	raise ValueError

def find_le(a, x):
	'''Find rightmost value less than or equal to x'''
	i = bisect.bisect_right(a, x)
	if i:
		return a[i-1]
	raise ValueError

def find_gt(a, x):
	'''Find leftmost value greater than x'''
	i = bisect.bisect_right(a, x)
	if i != len(a):
		return a[i]
	raise ValueError

def find_ge(a, x):
	'''Find leftmost item greater than or equal to x'''
	i = bisect.bisect_left(a, x)
	if i != len(a):
		return a[i]
	raise ValueError


# https://en.wikipedia.org/wiki/Metric_prefix
# SI
decimal_prefixes = {
	0: {'symbol' : '', 'name' : ''},
	pow(1000, -8): {'symbol' : 'y', 'name' : 'yocto'},
	pow(1000, -7): {'symbol' : 'z', 'name' : 'zepto'},
	pow(1000, -6): {'symbol' : 'a', 'name' : 'atto'},
	pow(1000, -5): {'symbol' : 'f', 'name' : 'femto'},
	pow(1000, -4): {'symbol' : 'p', 'name' : 'pico'},
	pow(1000, -3): {'symbol' : 'n', 'name' : 'nano'},
	pow(1000, -2): {'symbol' : 'u', 'name' : 'micro'},
	pow(1000, -1): {'symbol' : 'm', 'name' : 'milli'},
	pow(1000, 0): {'symbol' : '', 'name' : ''},
	pow(1000, 1): {'symbol' : 'k', 'name' : 'kilo'},
	pow(1000, 2): {'symbol' : 'M', 'name' : 'mega'},
	pow(1000, 3): {'symbol' : 'G', 'name' : 'giga'},
	pow(1000, 4): {'symbol' : 'T', 'name' : 'tera'},
	pow(1000, 5): {'symbol' : 'P', 'name' : 'peta'},
	pow(1000, 6): {'symbol' : 'E', 'name' : 'exa'},
	pow(1000, 7): {'symbol' : 'Z', 'name' : 'zetta'},
	pow(1000, 8): {'symbol' : 'Y', 'name' : 'yotta'},
}

decimal_prefixes_keys = sorted(decimal_prefixes.keys())


# https://en.wikipedia.org/wiki/Binary_prefix
# IEC
binary_prefixes = {
	0: {'symbol' : '', 'name' : ''},
	pow(1024, 0): {'symbol' : '', 'name' : ''},
	pow(1024, 1): {'symbol' : 'Ki', 'name' : 'kibi'},
	pow(1024, 2): {'symbol' : 'Mi', 'name' : 'mebi'},
	pow(1024, 3): {'symbol' : 'Gi', 'name' : 'gibi'},
	pow(1024, 4): {'symbol' : 'Ti', 'name' : 'tebi'},
	pow(1024, 5): {'symbol' : 'Pi', 'name' : 'pebi'},
	pow(1024, 6): {'symbol' : 'Ei', 'name' : 'exbi'},
	pow(1024, 7): {'symbol' : 'Zi', 'name' : 'zebi'},
	pow(1024, 8): {'symbol' : 'Yi', 'name' : 'yobi'},
}

binary_prefixes_keys = sorted(binary_prefixes.keys())


def get_decimal_prefix(x) -> tuple:
	'''Get the adjusted value and decimal prefix.'''

	if math.isfinite(x):
		# x is neither an infinity nor a NaN.
		key = find_le(decimal_prefixes_keys, abs(x))
	else:
		key = 0

	return (x / key if key != 0 else x, decimal_prefixes[key])


def get_binary_prefix(x) -> tuple:
	'''Get the adjusted value and binary prefix.'''

	if math.isfinite(x):
		# x is neither an infinity nor a NaN.
		key = find_le(binary_prefixes_keys, abs(x))
	else:
		key = 0

	return (x / key if key != 0 else x, binary_prefixes[key])
