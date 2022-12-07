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

def closest(x, iterable):
    '''Find the closest value to x in iterable.'''
    return min(iterable, key=lambda y:abs(y - x))
