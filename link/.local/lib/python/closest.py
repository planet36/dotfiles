# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=missing-module-docstring

__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

def closest(x, iterable):
	'''Find the closest value to x in iterable.'''
	return min(iterable, key=lambda y:abs(y - x))
