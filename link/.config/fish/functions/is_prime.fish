# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function is_prime --description 'Determine if a number is prime'
    set PRIME_REGEX '^([0-9]+): \1$'
    factor -- $argv[1] | string match --regex --quiet $PRIME_REGEX
end
