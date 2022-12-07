# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=invalid-name
# pylint: disable=missing-module-docstring

__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

from decimal import Decimal

def remove_exponent(d: Decimal) -> Decimal:
    '''
    Copied from <https://docs.python.org/3/library/decimal.html#decimal-faq>.
    '''
    return d.quantize(Decimal(1)) if d == d.to_integral_value() else d.normalize()
