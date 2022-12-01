# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=bad-indentation
# pylint: disable=fixme
# pylint: disable=invalid-name
# pylint: disable=missing-module-docstring
# pylint: disable=pointless-string-statement
# pylint: disable=trailing-newlines

__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

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
