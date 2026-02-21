# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# pylint: disable=invalid-name
# pylint: disable=missing-function-docstring
# pylint: disable=missing-module-docstring

__author__ = 'Steven Ward'
__license__ = 'MPL-2.0'

from decimal import Decimal as D, ROUND_HALF_UP

# https://docs.python.org/3/library/decimal.html#decimal.Decimal.to_integral_value
def round_half_up(x) -> D:
    return D(x).to_integral_value(rounding=ROUND_HALF_UP)

# https://docs.python.org/3/library/decimal.html#decimal.Decimal.quantize
def round_half_up_digits(x, precision: int = 0) -> D:
    return D(x).quantize(exp=D(10)**-precision, rounding=ROUND_HALF_UP)
