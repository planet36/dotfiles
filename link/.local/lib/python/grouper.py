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
def grouper(iterable, n, *, incomplete='fill', fillvalue=None):
    "Collect data into non-overlapping fixed-length chunks or blocks"
    # grouper('ABCDEFG', 3, fillvalue='x') --> ABC DEF Gxx
    # grouper('ABCDEFG', 3, incomplete='strict') --> ABC DEF ValueError
    # grouper('ABCDEFG', 3, incomplete='ignore') --> ABC DEF
    args = [iter(iterable)] * n
    if incomplete == 'fill':
        return zip_longest(*args, fillvalue=fillvalue)
    if incomplete == 'strict':
        return zip(*args, strict=True)
    if incomplete == 'ignore':
        return zip(*args)
    else:
        raise ValueError('Expected fill, strict, or ignore')
