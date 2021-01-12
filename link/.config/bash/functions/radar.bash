# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# XXX: radar.weather.gov was redesigned and launched on 2020-12-17
# These URLs are gone.
function radar
{
	(
	# Change the priority of the subshell.
	renice --priority 19 --pid $BASHPID > /dev/null

	local -r URL="https://radar.weather.gov/lite/N0R/MLB_loop.gif"
	local OUTFILE
	OUTFILE="$XDG_CACHE_HOME/$(basename -- "$URL")" || return

	if [[ ! -f "${OUTFILE}" ]]
	then
		curl --silent --output "${OUTFILE}"                          -- "${URL}" || return
	else
		curl --silent --output "${OUTFILE}" --time-cond "${OUTFILE}" -- "${URL}" || return
	fi

	sxiv -a -- "${OUTFILE}"
	)
}

