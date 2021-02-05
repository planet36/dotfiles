# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# Find and print characters that are not ASCII characters.
function nonascii_chars
{
    # ASCII characters are in the interval [0, 127].
    # Non-ASCII characters are in the interval [128, 255].
    local -r PATTERN='[23][0-7][0-7]'

    local FILE

    for FILE
    do
        echo "${FILE}"
        od --address-radix=n -c "${FILE}" | grep --extended-regexp --word-regexp --context 2 --color "${PATTERN}"
    done
}

