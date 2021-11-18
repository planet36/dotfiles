# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=missing-module-docstring

from itertools import zip_longest

# identical to
# https://more-itertools.readthedocs.io/en/stable/api.html#more_itertools.grouper
# copied from
# https://docs.python.org/3/library/itertools.html#itertools-recipes
def grouper(iterable, n, fillvalue=None):
	"Collect data into non-overlapping fixed-length chunks or blocks"
	# grouper('ABCDEFG', 3, 'x') --> ABC DEF Gxx
	args = [iter(iterable)] * n
	return zip_longest(*args, fillvalue=fillvalue)
