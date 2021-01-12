# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function is_prime
{
	factor -- "${1}" | grep --perl-regexp --count '^([[:digit:]]+): \1$'
}

