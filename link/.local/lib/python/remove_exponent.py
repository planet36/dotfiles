# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=missing-function-docstring
# pylint: disable=missing-module-docstring

__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

from decimal import Decimal

# copied from
# https://docs.python.org/3/library/decimal.html#decimal-faq
def remove_exponent(d: Decimal) -> Decimal:
	return d.quantize(Decimal(1)) if d == d.to_integral_value() else d.normalize()
