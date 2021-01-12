# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function rgb2hex
{
	local -r MSG_FMT='#%02X%02X%02X'
	local -i R=0
	local -i G=0
	local -i B=0

	while read -r R G B ; do
		if ((R < 0))
		then
			R=0
		fi

		if ((G < 0))
		then
			G=0
		fi

		if ((B < 0))
		then
			B=0
		fi


		if ((R > 255))
		then
			R=255
		fi

		if ((G > 255))
		then
			G=255
		fi

		if ((B > 255))
		then
			B=255
		fi

		printf "${MSG_FMT}" "${R}" "${G}" "${B}"
		printf '\n'

		R=0
		G=0
		B=0
	done
}
