# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# http://mywiki.wooledge.org/BashFAQ/071
# converts ASCII character to its decimal value
function ord
{
	LC_CTYPE=C printf '%d' "'${1}"
}

