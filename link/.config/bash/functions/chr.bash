# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# https://mywiki.wooledge.org/BashFAQ/071
# converts decimal value to its ASCII character representation
function chr
{
    local val
    ((${1} < 256)) || return 1
    printf -v val '%03o' "${1}"
    printf '%b' "\\${val}"
}
