# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function is_int --argument-names NUM --description 'Determine if a number is an integer'
    # https://stackoverflow.com/a/21505954
    set INT_REGEX '^(?:[+-]?[1-9][0-9]*|0)$'
    string match --regex --quiet $INT_REGEX -- $NUM
end
