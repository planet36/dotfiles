# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function rtrim
{
    # \s matches newline
    #perl -p -i~ -e 's/\s+$//' -- "${@}"
    perl -p -i~ -e 's/[ \t]+$//' -- "${@}"
}
