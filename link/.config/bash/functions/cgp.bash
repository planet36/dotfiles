# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

#alias cgp='cd && clean code && get code && put code ; cd - > /dev/null'
function cgp
{
	cd || return
	clean code || return
	get code || return
	put code || return
	cd - > /dev/null
}

