# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# pylint: disable=invalid-name
# pylint: disable=missing-module-docstring

__author__ = 'Steven Ward'
__license__ = 'MPL-2.0'

# https://rosettacode.org/wiki/Gray_code#Python

def bin_to_gray(n : int) -> int:
    '''Convert binary integer to gray code.'''
    return n ^ (n >> 1)


def gray_to_bin(n : int) -> int:
    '''Convert gray code to binary integer.'''
    mask = n
    while (mask := mask >> 1):
        n ^= mask
    return n
