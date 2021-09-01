# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=missing-function-docstring
# pylint: disable=missing-module-docstring

import decimal

DECIMAL_PLACES = [
		decimal.Decimal(10)**0,
		decimal.Decimal(10)**-1,
		decimal.Decimal(10)**-2,
		decimal.Decimal(10)**-3,
		decimal.Decimal(10)**-4,
		decimal.Decimal(10)**-5,
		decimal.Decimal(10)**-6,
		decimal.Decimal(10)**-7,
		decimal.Decimal(10)**-8,
		decimal.Decimal(10)**-9,
		decimal.Decimal(10)**-10,
		]

def round_half_up(x) -> decimal.Decimal:
	return decimal.Decimal(x).quantize(exp=decimal.Decimal(1), rounding=decimal.ROUND_HALF_UP)

def round_half_up_digits(x, precision: int = 0) -> decimal.Decimal:
	return decimal.Decimal(x).quantize(exp=decimal.Decimal(10)**-precision, rounding=decimal.ROUND_HALF_UP)
