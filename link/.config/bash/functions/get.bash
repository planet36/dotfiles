# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function get
{
	if (( $# == 0 ))
	then
		printf 'Error: Must give at least one folder name\n' 1>&2
		printf 'Usage: %q DIR...\n' "${FUNCNAME[0]}" 1>&2
		return 1
	fi

	local DIR

	for DIR
	do
		local SRC="$MY_WEBSITE:$DIR/"
		local DST="$HOME/$DIR"
		# shellcheck disable=SC2086
		rsync $RSYNC_ARGS -e ssh "$SRC" "$DST"
		echo
	done
}

