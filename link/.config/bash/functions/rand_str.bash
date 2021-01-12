# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# Select random characters from the given string.
# Example maze using Unicode box drawing characters U+2571 and U+2572:
# rand_str $'\342\225\261\342\225\262' 2040 | fold -b -w 204 ; echo
# Note: width must be a multiple of 3
function rand_str
{
	# The given string
	local -r S="${1}"

	# If no string was given,
	if [[ -z "${S}" ]]
	then
		return
	fi

	# The length of the given string
	local -r -i L=${#S}

	# The number of characters to randonly select (default is 1)
	local -i N="${2:-1}"

	while ((N-- > 0))
	do
		# Get a random index in the string.
		local -i I=$((RANDOM % L))

		printf -- '%s' "${S:${I}:1}"
	done
}

