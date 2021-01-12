# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# http://mywiki.wooledge.org/BashFAQ/071
# converts decimal value to its ASCII character representation
function chr2
{
	local val
	printf -v val '%x' "${1}"
	printf '%b' "\\u${val}"
}

