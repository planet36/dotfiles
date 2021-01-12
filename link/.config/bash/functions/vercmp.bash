# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# https://www.wikitechy.com/tutorials/linux/how-to-compare-two-strings-in-dot-separated-version-format-in-bash
##### TODO: test this
# return 0 if the first and second strings are equal
# return 1 if first string is the least
# return 2 if second string is the least
function vercmp
{
	#if (($# < 2))
	#then
		#return 2
	#fi

	if [[ "${1}" == "${2}" ]]
	then
		return 0
	fi

	local LEAST
	#LEAST="$(printf '%s\n%s\n' "${1}" "${2}" | sort --version-sort | head -n 1)"
	LEAST="$(printf '%s\0%s\0' "${1}" "${2}" | sort --zero-terminated --version-sort | head --zero-terminated --lines=1)"

	if [[ "${1}" == "${LEAST}" ]]
	then
		return 1
	else
		return 2
	fi
}

