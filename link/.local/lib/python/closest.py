# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# pylint: disable=invalid-name

'''
Find the value in an iterable closest to a given number.
'''

__author__ = 'Steven Ward'
__license__ = 'MPL-2.0'

from collections.abc import Iterable

def closest(x: int | float, iterable: Iterable[int | float]) -> int | float:
    '''Find the closest value to x in iterable.'''
    return min(iterable, key=lambda y:abs(y - x))
