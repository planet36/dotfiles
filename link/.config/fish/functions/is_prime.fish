# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function is_prime --argument-names NUM --description 'Determine if a number is prime'
    #set PRIME_REGEX '^([0-9]+): \1$'
    #factor -- $NUM | string match --regex --quiet $PRIME_REGEX
    openssl prime -- $NUM | grep -F -q 'is prime'
end
