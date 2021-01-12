# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function hex2rgb
{
	local -r MSG_FMT='%d %d %d'
	local RGB
	local R
	local G
	local B

	while read -r RGB ; do

		if [[ "${RGB:0:1}" == '#' ]]
		then
			# remove leading '#'
			RGB="${RGB:1}"
		fi

		if (( ${#RGB} < 3 ))
		then
			# pad with 0 to make the length 3
			printf -v RGB '%s%0*d' "${RGB}" $((3-${#RGB})) 0
		elif (( ${#RGB} > 3 )) && (( ${#RGB} < 6 ))
		then
			# pad with 0 to make the length 6
			printf -v RGB '%s%0*d' "${RGB}" $((6-${#RGB})) 0
		elif (( ${#RGB} > 6 ))
		then
			# trim to 6 characters
			RGB="${RGB:0:6}"
		fi

		if (( ${#RGB} == 3 ))
		then
			# hex digits should repeat
			R="0x${RGB:0:1}${RGB:0:1}"
			G="0x${RGB:1:1}${RGB:1:1}"
			B="0x${RGB:2:1}${RGB:2:1}"
		elif (( ${#RGB} == 6 ))
		then
			R="0x${RGB:0:2}"
			G="0x${RGB:2:2}"
			B="0x${RGB:4:2}"
		else
			continue
		fi

		printf "${MSG_FMT}" "${R}" "${G}" "${B}"
		printf '\n'

		RGB=''
		R=''
		G=''
		B=''
	done
}

