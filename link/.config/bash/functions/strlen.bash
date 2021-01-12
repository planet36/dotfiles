# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function strlen
{
	local STR

	if (( $# == 0 ))
	then
		# read from stdin

		while read -r STR
		do
			printf '%d\t%s\n' "${#STR}" "${STR}"
		done
	else
		# read from input files

		for x
		do
			while read -r STR
			do
				printf '%d\t%s\n' "${#STR}" "${STR}"
			done 0< "${x}"
		done
	fi
}

