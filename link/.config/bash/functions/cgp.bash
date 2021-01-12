# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

#alias cgp='cd && clean code && get code && put code ; cd - > /dev/null'
function cgp
{
	pushd . &> /dev/null

	cd || return

	clean code || return

	get code || return

	put code || return

	#cd - > /dev/null || return

	# shellcheck disable=SC2164
	popd &> /dev/null
}

