# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function is_uint --argument-names NUM --description 'Determine if a number is an unsigned integer'
    # https://stackoverflow.com/a/21505954
    set UINT_REGEX '^(?:[1-9][0-9]*|0)$'
    string match --regex --quiet $UINT_REGEX -- $NUM
end
