# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function dcmp
{
	if (( $# != 2 ))
	then
		printf 'Usage: %q DIR1 DIR2\n' "${FUNCNAME[0]}" 1>&2
		printf 'Find added/removed/modified files between DIR1 and DIR2.\n' 1>&2
		return
	fi

	local A="${1}"
	local B="${2}"

	if [[ ! -d "${A}" ]]
	then
		printf 'Error: %q is not a directory.\n' "${A}" 1>&2
		return 1
	fi

	if [[ ! -d "${B}" ]]
	then
		printf 'Error: %q is not a directory.\n' "${B}" 1>&2
		return 1
	fi

	# Remove duplicate leading slashes
	# Remove trailing slashes
	# Prefix leading '-' with './' (is this necessary?)
	A=$(sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||' --expression 's|^-|./-|' <<< "${A}")
	B=$(sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||' --expression 's|^-|./-|' <<< "${B}")

	# escape non-word chars
	local -r A_escaped=$(sed --regexp-extended --expression 's/(\W)/\\\1/g' <<< "${A}")
	local -r B_escaped=$(sed --regexp-extended --expression 's/(\W)/\\\1/g' <<< "${B}")

	local -r -a DIFF_OPTIONS_EXCLUDE=('--exclude='{.bzr,CVS,.git,.hg,.svn})

	local -r PATTERN1="Files ${A_escaped}(.*?)(/[^/]+) and ${B_escaped}\\1\\2 differ"
	local -r PATTERN2="Only in ${A_escaped}(/.+?)?: ([^/]+)"
	local -r PATTERN3="Only in ${B_escaped}(/.+?)?: ([^/]+)"

	local -r REPLACEMENT1="! {${A}\\1,${B}\\1}\\2"
	local -r REPLACEMENT2="- ${A}\\1/\\2"
	local -r REPLACEMENT3="+ ${B}\\1/\\2"

	local -r DELIMITER=$'\x1F'
	# x1F is unit separator

	diff --brief --recursive \
	"${DIFF_OPTIONS_EXCLUDE[@]}" \
	-- "${A}" "${B}" |
	sed --regexp-extended \
	--expression "s${DELIMITER}${PATTERN1}${DELIMITER}${REPLACEMENT1}${DELIMITER}" \
	--expression "s${DELIMITER}${PATTERN2}${DELIMITER}${REPLACEMENT2}${DELIMITER}" \
	--expression "s${DELIMITER}${PATTERN3}${DELIMITER}${REPLACEMENT3}${DELIMITER}"
}

