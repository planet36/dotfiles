# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# Find and print characters that are not space characters but are control characters.
function nonspace_cntrl_chars
{
    # space characters are:
    # space, form-feed ('\f'), newline ('\n'), carriage return ('\r'),
    # horizontal tab ('\t'), and vertical tab ('\v').
    local -r PATTERN='\\0|00[1-6]|\\a|\\b|01[67]|0[23][0-7]|177'

    local FILE

    for FILE
    do
        echo "${FILE}"
        od --address-radix=n -c "${FILE}" | grep --extended-regexp --word-regexp --context 2 --color "${PATTERN}"
    done
}

