# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# pylint: disable=invalid-name
# pylint: disable=missing-module-docstring

__author__ = 'Steven Ward'
__license__ = 'MPL-2.0'

def closest(x, iterable):
    '''Find the closest value to x in iterable.'''
    return min(iterable, key=lambda y:abs(y - x))
