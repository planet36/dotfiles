# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=missing-function-docstring
# pylint: disable=missing-module-docstring

import decimal

# https://docs.python.org/3/library/decimal.html#decimal.Decimal.to_integral_value
def round_half_up(x) -> decimal.Decimal:
	return decimal.Decimal(x).to_integral_value(rounding=decimal.ROUND_HALF_UP)

# https://docs.python.org/3/library/decimal.html#decimal.Decimal.quantize
def round_half_up_digits(x, precision: int = 0) -> decimal.Decimal:
	return decimal.Decimal(x).quantize(exp=decimal.Decimal(10)**-precision,
	                                   rounding=decimal.ROUND_HALF_UP)
