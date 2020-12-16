# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash

# shellcheck disable=SC2059
# SC2059: Don't use variables in the printf format string. Use printf "..%s.." "$foo".


# sed -r -n -e 's/^btime ([0-9]+)$/\1/p' /proc/stat
# sed '/^btime /!d; s///;q' /proc/stat
function boottime
{
	date --date=@"$(awk '/^btime/{print $2}' /proc/stat)" +'%a, %F %T'
}


#alias cgp='cd && clean code && get code && put code ; cd - > /dev/null'
function cgp
{
	cd || return
	clean code || return
	get code || return
	put code || return
	cd - > /dev/null
}


# http://mywiki.wooledge.org/BashFAQ/071
# converts decimal value to its ASCII character representation
function chr
{
	local val
	((${1} < 256)) || return 1
	printf -v val '%03o' "${1}"
	printf '%b' "\\${val}"
}


# http://mywiki.wooledge.org/BashFAQ/071
# converts decimal value to its ASCII character representation
function chr2
{
	local val
	printf -v val '%x' "${1}"
	printf '%b' "\\u${val}"
}


function clean
{
	find "${@}" \( -type f -or -type l \) \( -name '*~' -or -name '.*~' \) -print0 | xargs --null --no-run-if-empty 'rm' --verbose
}

function clean1
{
	clean "${@}" -maxdepth 1
}

function clean2
{
	clean "${@}" -mindepth 2
}


function date_range
{
	local D1
	local D2

	D1=$(date --date="${1}" +'%F') || return
	D2=$(date --date="${2}" +'%F') || return

	local -a SORTED_DATES

	mapfile -t SORTED_DATES < <(printf '%q\n%q\n' "${D1}" "${D2}" | sort)

	D1="${SORTED_DATES[0]}"
	D2="${SORTED_DATES[1]}"

	while true
	do
		printf '%q\n' "${D1}"

		[[ "${D1}" == "${D2}" ]] && break

		D1=$(date --date="${D1} +1 day" +'%F')
	done
}


# days between dates
function dbd
{
	local D1
	local D2

	if (( $# == 1 ))
	then
		D1=$(date               +'%F') || return
		D2=$(date --date="${1}" +'%F') || return
	elif (( $# == 2 ))
	then
		D1=$(date --date="${1}" +'%F') || return
		D2=$(date --date="${2}" +'%F') || return
	else
		printf 'Error: Must give 1 or 2 dates\n' 1>&2
		printf 'Usage: %q DATE1 [DATE2]\n' "${FUNCNAME[0]}" 1>&2
		printf 'If 1 date is given, the other defaults to today.\n' 1>&2
		return 1
	fi

	D1=$(date --date="${D1}" +'%s') || return
	D2=$(date --date="${D2}" +'%s') || return

	local -r SECONDS_PER_DAY=86400

	echo $(( (D2 - D1) / SECONDS_PER_DAY ))

	local SECONDS_PER_HALF_DAY=$((SECONDS_PER_DAY/2))

	if ((D1 > D2))
	then
		SECONDS_PER_HALF_DAY=$((-HALF_DAY))
	fi

	echo $(( ((D2 - D1) + SECONDS_PER_HALF_DAY) / SECONDS_PER_DAY ))
}


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


function del
{
	export SIMPLE_BACKUP_SUFFIX=$(date -u +.%Y%m%dT%H%M%SS%3N)

	#mv --verbose --backup=simple --suffix=.$(date -u +"%Y%m%dT%H%M%SS%3N") --target-directory "$TRASH_DIR"
	mv --verbose --backup=simple --target-directory "$TRASH_DIR" "${@}"
}


# to print dots:
# yes '. ' | head -n 1000 | tr -d '\n' | fold


function extract_audio
{
	local INFILE

	for INFILE
	do
		if [[ ! -f "${INFILE}" ]]
		then
			printf 'Error: %q is not a file.\n' "${INFILE}" 1>&2
			return 1
		fi

		local AUDIO_FORMAT
		AUDIO_FORMAT="$(ffmpeg -i "${INFILE}" 2>&1 | sed -r -n -e 's/^.*Audio: ([^,]+)?.*$/\1/p')" || return

		local INFILE_BASE="${INFILE%.*}"

		local OUTFILE="${INFILE_BASE}.${AUDIO_FORMAT}"

		# -vn (output) Disable video recording.
		ffmpeg -i "${INFILE}" -vn -acodec copy "${OUTFILE}" || return

		touch --reference "${INFILE}" -- "${OUTFILE}" || return
	done
}


##### TODO: test this
function fix_resolution
{
	local OUTPUT
	#local MODE
	OUTPUT=$(xrandr | awk '$2 == "connected"{print $1; exit}')
	#xrandr --output VGA-1 --mode 1920x1200
	xrandr --output "${OUTPUT}" --auto
}

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


function get-code
{
	wget -- "${CODE_ARCHIVE_URL}/code-latest.tar.xz"
}


# get tar member
# tar -x -v -f AVCATT_ONESAF_cm.20200109.0.tgz -C ~/tmp AVCATT_ONESAF_cm.20200109.0/PAIR


# Example: git-diff-summary v180000.20181004
function git-diff-summary
{

	if (( $# < 1 ))
	then
		printf 'Error: Must give "commit1"\n' 1>&2
		return 1
	fi

	local -r COMMIT1="${1}"

	local -r COMMIT2="${2:-HEAD}"

	printf 'h2. Commit messages for files that changed between %s and %s\n\n' "${COMMIT1}" "${COMMIT2}"

	local FILE
	for FILE in $(git diff --name-only "${COMMIT1}" "${COMMIT2}")
	do
		printf '*%q*\n' "${FILE}"
		if [[ ! -f "${FILE}" ]]
		then
			printf "Error: %q does not exist\n" "${FILE}"
			return 1
		fi
		printf '{noformat}\n'

		#git log --format='%s' ${COMMIT1}.."${COMMIT2}" -- "${FILE}" || return
		git log --decorate --color=never "${COMMIT1}".."${COMMIT2}" -- "${FILE}" | grep '^    ' || return

		printf '{noformat}\n'
		printf '\n'
	done
}


function install_yay
{
	cd ~/.local/src/

	if [ ! -d yay-bin ] ; then
		git clone https://aur.archlinux.org/yay-bin.git
		cd yay-bin
	else
		cd yay-bin
		git pull --ff-only || return
	fi

	# Must enter sudo password
	makepkg --install --syncdeps --noconfirm --needed || return
	# Do not run yay as root

	cd - > /dev/null
}


function intersect
{
	if (( $# != 2 ))
	then
		printf 'Error: Must give 2 paths\n' 1>&2
		printf 'Usage: %q FILE1 FILE2\n' "${FUNCNAME[0]}" 1>&2
		printf 'Print the intersection of FILE1 and FILE2.\n' 1>&2
		return 1
	fi

	local FILE1="${1}"
	local FILE2="${2}"

	if [[ ! -f "${FILE1}" ]]
	then
		printf 'Error: %q is not a file.\n' "${FILE1}" 1>&2
		return 1
	fi

	if [[ ! -f "${FILE2}" ]]
	then
		printf 'Error: %q is not a file.\n' "${FILE2}" 1>&2
		return 1
	fi

	sort <(sort --uniq -- "${FILE1}") <(sort --uniq -- "${FILE2}") | uniq --repeated
}


function is_prime
{
	factor -- "${1}" | grep --perl-regexp --count '^([[:digit:]]+): \1$'
}


# Determine if the tar file would create files outside of a root folder without the basename of itself.
function messy_tar_file
{
	if (( $# != 1 ))
	then
		printf 'Error: Must give 1 file.\n' 1>&2
		return 1
	fi

	local FILE="${1}"
	local BASENAME

	BASENAME=$(basename -- "${FILE}" | cut --delimiter='.' --fields=1) || return

	tar --list --file "${FILE}" | awk --assign basename="${BASENAME}" 'NR==1 {
	# Store the first record.
	first_rec=$0

	# The base name of the file (without extension) must equal the first record.
	if (first_rec != basename "/") {
		exit 1
	}

	# It must not begin with "/".  In this case, the tar file was created with the --absolute-names (-P) option.
	# It must not have intermediate directories.
	# It must end with "/".

	if (first_rec !~ /^[^\/]+\/$/) {
		exit 1
	}
}

# Every record must begin with the first record.
match($0, first_rec) != 1 {
	exit 1
}'

}


##### TODO: either make this distro agnostic or remove it
# list old linux kernels
function lsoldkernels
{
	local KERNEL_RELEASE
	KERNEL_RELEASE=$(uname -r | sed -r 's/-\w+$//') || return
	#KERNEL_RELEASE="${KERNEL_RELEASE%-generic}"

	dpkg --get-selections 'linux-*' |
	grep --perl-regexp -- '^linux-(headers|image|image-extra)-[0-9\.\-]+' |
	grep -v -- 'deinstall$' |
	cut --fields 1 |
	grep -v -- "${KERNEL_RELEASE}"

	#dpkg --get-selections 'linux-*' | grep --perl-regexp '^linux-(headers|image|image-extra)-[0-9\.\-]+(-generic)?\s+install$' | cut --fields 1

	#sudo apt-get purge $(dpkg --get-selections 'linux-*' | grep --perl-regexp '^linux-(headers|image|image-extra)-[0-9\.\-]+')
}


##### TODO: convert these to functions

# https://askubuntu.com/a/534711
alias mount-cdrom='sudo mkdir --verbose --parents "/media/${USER}/cdrom" && sudo mount --read-only -t auto /dev/cdrom "/media/${USER}/cdrom/"'

alias mount-dvd='sudo mkdir --verbose --parents "/media/${USER}/dvd" && sudo mount --read-only -t auto /dev/dvd "/media/${USER}/dvd/"'



# Find and print characters that are not ASCII characters.
function nonascii_chars
{
	# ASCII characters are in the interval [0, 127].
	# Non-ASCII characters are in the interval [128, 255].
	local -r PATTERN='[23][0-7][0-7]'

	local FILE

	for FILE
	do
		echo "${FILE}"
		od --address-radix=n -c "${FILE}" | grep --extended-regexp --word-regexp --context 2 --color "${PATTERN}"
	done
}


# Find and print characters that are not space characters but are control characters.
function nonspace_cntrl_chars
{
	# space characters are:
	# space, form-feed ('\f'), newline ('\n'), carriage return ('\r'),
	# horizontal tab ('\t'), and vertical tab ('\v').
	local -r PATTERN='\\0|00[1-6]|\\a|\\b|01[67]|0[23][0-7]|177'

	local FILE

	for FILE
	do
		echo "${FILE}"
		od --address-radix=n -c "${FILE}" | grep --extended-regexp --word-regexp --context 2 --color "${PATTERN}"
	done
}


# http://mywiki.wooledge.org/BashFAQ/071
# converts ASCII character to its decimal value
function ord
{
	LC_CTYPE=C printf '%d' "'${1}"
}


function program_exists
{
	command -v "${@}" > /dev/null
}


function psgrep
{
	if [[ -z "${1}" ]]
	then
		return 1
	fi

	local -a PROCESSES
	mapfile -t PROCESSES < <(pgrep -- "${1}")

	((${#PROCESSES[@]} == 0)) && return

	ps --sort pid --pid "${PROCESSES[@]}"
}


function put
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
		local SRC="$HOME/$DIR/"
		local DST="$MY_WEBSITE:$DIR"
		# shellcheck disable=SC2086
		rsync $RSYNC_ARGS -e ssh "$SRC" "$DST"
		echo
	done
}


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


# How to replace text using grep and perl...
# rg -l -P -- 'OLD' | xargs perl -p -i.bak -e 's|OLD|NEW|g;'
# rg -l -P -- 'OLD' | xargs perl -p -i~ -e 's|OLD|NEW|g;'


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


function rtrim
{
	# \s matches newline
	#perl -p -i~ -e 's/\s+$//' -- "${@}"
	perl -p -i~ -e 's/[ \t]+$//' -- "${@}"
}


# wrapper for scrypt
function sc
{
	local -r SCRYPT_EXT='scrypt'
	local -r VERBOSE=false

	local INFILE

	for INFILE
	do
		if [[ ! -f "${INFILE}" ]]
		then
			printf 'Error: %q is not a file.\n' "${INFILE}" 1>&2
			return 1
		fi

		local INFILE_BASE="${INFILE%.*}"
		local INFILE_EXT="${INFILE##*.}"
		local ENC_OR_DEC
		local OUTFILE

		if [[ "${INFILE_EXT}" == "${SCRYPT_EXT}" ]]
		then
			# decrypt
			ENC_OR_DEC='dec'
			OUTFILE="${INFILE_BASE}"
		else
			# encrypt
			ENC_OR_DEC='enc'
			OUTFILE="${INFILE}.${SCRYPT_EXT}"
		fi

		if ${VERBOSE}
		then
			printf "# INFILE=%q\n" "${INFILE}"
			printf "# INFILE_BASE=%q\n" "${INFILE_BASE}"
			printf "# INFILE_EXT=%q\n" "${INFILE_EXT}"
			printf "# ENC_OR_DEC=%q\n" "${ENC_OR_DEC}"
			printf "# OUTFILE=%q\n" "${OUTFILE}"
		fi

		if [[ -e "${OUTFILE}" ]]
		then
			printf 'Warning: %q already exists.\n' "${OUTFILE}" 1>&2
			continue
		fi

		nice -n 19 scrypt "${ENC_OR_DEC}" -- "${INFILE}" "${OUTFILE}" || return

		touch --reference "${INFILE}" -- "${OUTFILE}" || return
	done
}


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


# Tar the given path(s)
function t
{
	(
	# Change the priority of the subshell.
	renice --priority 19 --pid $BASHPID > /dev/null

	declare -r SCRIPT_NAME="${FUNCNAME[0]}"

	declare -r SCRIPT_VERSION='2019-09-19'

	declare -r SCRIPT_AUTHOR='Steven Ward'

	VERBOSE=false

	INCLUDE_DATETIME=false

	BASENAME=''

	FORCE=false

	EXTRA_INFO_FILES=false

	PRESERVE_TIMESTAMP=false

	SUFFIX=''

	declare -a TAR_OPTIONS


	function print_version
	{
		cat <<EOT
${SCRIPT_NAME} ${SCRIPT_VERSION}
Written by ${SCRIPT_AUTHOR}
EOT
	}

	function print_help
	{
		cat <<EOT
Usage: ${SCRIPT_NAME} [OPTIONS] PATHNAME...

Tar PATHNAME.  Create a tar file with the same name as PATHNAME but with the appropriate extension appended.

OPTIONS
  -V : Print the version information and exit.

  -h : Print this message and exit.

  -v : Print extra output.

  -b BASENAME : In the output file name, prepend BASENAME.

  -d : Include the current date-time in the output file name.

  -f : Force overwriting of the output file.

  -i : Create files for each PATHNAME from the output of the sha512sum and stat commands.

  -p : Preserve the timestamp of PATHNAME in the output file.

  -s SUFFIX : In the outfile file name, append SUFFIX after ".tar".
    The invocation of tar uses the --auto-compress option.
    From the tar manual: <https://www.gnu.org/software/tar/manual/html_node/gzip.html#auto_002dcompress>
        Select a compression program to use by the archive file name suffix. The following suffixes are recognized:
        Suffix  Compression program
        .gz     gzip
        .tgz    gzip
        .taz    gzip
        .Z      compress
        .taZ    compress
        .bz2    bzip2
        .tz2    bzip2
        .tbz2   bzip2
        .tbz    bzip2
        .lz     lzip
        .lzma   lzma
        .tlz    lzma
        .lzo    lzop
        .xz     xz
    Note: It's unnecessary to use the suffixes that begin with ".t" because the ".tar" extension is always present in the output file name.

  -t TAR_OPTION : Pass TAR_OPTION to the tar command.

EOT
	}

	function print_warning
	{
		printf 'Warning: ' 1>&2
		printf -- "${@}" 1>&2
		printf '\n' 1>&2
	}

	function print_error
	{
		printf 'Error: ' 1>&2
		printf -- "${@}" 1>&2
		printf '\n' 1>&2

		printf 'Try "%q -h" for more information.\n' "${SCRIPT_NAME}" 1>&2
		exit 1
	}

	function print_verbose
	{
		${VERBOSE} && { printf -- "${@}" ; printf '\n' ; }
	}


	while getopts "Vhvb:dfips:t:" option
	do
		case "${option}" in

			V) # version
				print_version
				exit
			;;

			h) # help
				print_help
				exit
			;;

			v) # verbose
				VERBOSE=true
			;;

			b) # basename
				BASENAME=$(basename -- "${OPTARG}")
			;;

			d) # include date-time
				INCLUDE_DATETIME=true
			;;

			f) # force
				FORCE=true
			;;

			i) # extra info files
				EXTRA_INFO_FILES=true
			;;

			p)
				PRESERVE_TIMESTAMP=true
			;;

			s) # suffix
				SUFFIX="${OPTARG}"

				# If the suffix is not empty, and it does not begin with ".",
				if [[ -n "${SUFFIX}" &&  ${SUFFIX:0:1} != . ]]
				then
					# Prefix the suffix with ".".
					SUFFIX=".${SUFFIX}"
				fi
			;;

			t) # tar option
				#echo "OPTARG: ${OPTARG}"
				TAR_OPTIONS+=("${OPTARG}")
				#echo "TAR_OPTIONS=(${TAR_OPTIONS[@]})"
				#printf -- "TAR_OPTIONS=(${TAR_OPTIONS[@]})\n"
			;;

			*)
				# Note: ${option} is '?'
				print_error "Option is unknown."
			;;

		esac
	done

	shift $((OPTIND - 1)) || exit

	print_verbose 'INCLUDE_DATETIME=%s' "${INCLUDE_DATETIME}"

	print_verbose 'FORCE=%s' "${FORCE}"

	print_verbose 'EXTRA_INFO_FILES=%s' "${EXTRA_INFO_FILES}"

	print_verbose 'PRESERVE_TIMESTAMP=%s' "${PRESERVE_TIMESTAMP}"

	print_verbose 'SUFFIX=%s' "${SUFFIX}"

	print_verbose 'TAR_OPTIONS=(%s)' "${TAR_OPTIONS[*]}"


	for INFILE
	do
		if [[ ! -e "${INFILE}" ]]
		then
			print_error '%q does not exist.' "${INFILE}"
		fi

		# Remove duplicate leading slashes
		# Remove trailing slashes
		# Prefix leading '-' with './' (is this necessary?)
		#INFILE=$(sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||' --expression 's|^-|./-|' <<< "${INFILE}")
		INFILE=$(sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||' <<< "${INFILE}")
		print_verbose 'INFILE=%q' "${INFILE}"

		# The output file will be in the cwd.

		if [[ -z "${BASENAME}" ]]
		then
			OUTFILE=$(basename -- "${INFILE}")
		else
			OUTFILE="${BASENAME}"
		fi
		print_verbose 'OUTFILE=%q' "${OUTFILE}"

		if ${INCLUDE_DATETIME}
		then
			OUTFILE+=.$(date -u +'%Y%m%dT%H%M%SS%3N')
			print_verbose 'OUTFILE=%q' "${OUTFILE}"
		fi

		if ${EXTRA_INFO_FILES}
		then
			if [[ -f "${INFILE}" ]]
			then
				print_verbose 'sha512sum -- %q > %q.sha512sum' "${INFILE}" "${OUTFILE}"
				sha512sum -- "${INFILE}" > "${OUTFILE}".sha512sum || exit

				stat -- "${INFILE}" > "${OUTFILE}".stat || exit
			fi
		fi

		OUTFILE+=".tar"
		print_verbose 'OUTFILE=%q' "${OUTFILE}"

		if [[ -n "${SUFFIX}" ]]
		then
			OUTFILE+="${SUFFIX}"
			print_verbose 'OUTFILE=%q' "${OUTFILE}"
		fi

		if [[ -e "${OUTFILE}" ]] && ! ${FORCE}
		then
			print_error '%q already exists.' "${OUTFILE}"
			return 1
			#continue
		fi

		if [[ -L "${INFILE}" ]]
		then
			# Get the link target.
			INFILE=$(readlink -- "${INFILE}")
			print_verbose 'INFILE=%q' "${INFILE}"
		fi

		#printf 'Tarring %q to %q\n' "${INFILE}" "${OUTFILE}"
		printf '# %q => %q\n' "${INFILE}" "${OUTFILE}"

		# If there is a slash in the input file/folder name,
		if [[ "${INFILE}" =~ / ]]
		then
			DIRNAME=$(dirname -- "${INFILE}")

			BASENAME_2=$(basename -- "${INFILE}")
			print_verbose 'BASENAME_2=%q' "${BASENAME_2}"

			tar --create --auto-compress --file="${OUTFILE}" "${TAR_OPTIONS[@]}" --directory "${DIRNAME}" -- "${BASENAME_2}" || exit
		else
			tar --create --auto-compress --file="${OUTFILE}" "${TAR_OPTIONS[@]}" -- "${INFILE}" || exit
		fi

		if ${PRESERVE_TIMESTAMP}
		then
			# Preserve the timestamp.
			touch --reference="${INFILE}" -- "${OUTFILE}" || exit
		fi
	done
	)
}


function trash
{
	printf 'Num. items removed: '
	#time nice -n 19 find "$TRASH_DIR" -mindepth 1 -print -delete | wc --lines
	time find "$TRASH_DIR" -mindepth 1 -print -delete | wc --lines
}


# Untar the given file(s)
function untar
{
	(
	# Change the priority of the subshell.
	renice --priority 19 --pid $BASHPID > /dev/null

	declare -r SCRIPT_NAME="${FUNCNAME[0]}"

	declare -r SCRIPT_VERSION='2019-09-19'

	VERBOSE=false

	KEEP=false

	declare -a TAR_OPTIONS


	function print_version
	{
		cat <<EOT
${SCRIPT_NAME} ${SCRIPT_VERSION}
Written by Steven Ward
EOT
	}

	function print_help
	{
		cat <<EOT
Usage: ${SCRIPT_NAME} [OPTIONS] FILE...

Untar FILE.

OPTIONS
  -V : Print the version information and exit.

  -h : Print this message and exit.

  -v : Print extra output.

  -k : Keep the input file.

  -t TAR_OPTION : Pass TAR_OPTION to the tar command.

EOT
	}

	function print_warning
	{
		printf 'Warning: ' 1>&2
		printf -- "${@}" 1>&2
		printf '\n' 1>&2
	}

	function print_error
	{
		printf 'Error: ' 1>&2
		printf -- "${@}" 1>&2
		printf '\n' 1>&2

		printf 'Try "%q -h" for more information.\n' "${SCRIPT_NAME}" 1>&2
		exit 1
	}

	function print_verbose
	{
		${VERBOSE} && { printf -- "${@}" ; printf '\n' ; }
	}


	while getopts "Vhvkt:" option
	do
		case "${option}" in

			V) # version
				print_version
				exit
			;;

			h) # help
				print_help
				exit
			;;

			v) # verbose
				VERBOSE=true
			;;

			k) # keep
				KEEP=true
			;;

			t) # tar option
				#echo "OPTARG: ${OPTARG}"
				TAR_OPTIONS+=("${OPTARG}")
				#echo "TAR_OPTIONS=(${TAR_OPTIONS[@]})"
				#printf -- "TAR_OPTIONS=(${TAR_OPTIONS[@]})\n"
			;;

			*)
				# Note: ${option} is '?'
				print_error 'Option is unknown.'
			;;

		esac
	done

	shift $((OPTIND - 1)) || exit

	print_verbose 'KEEP=%s' "${KEEP}"

	print_verbose 'TAR_OPTIONS=(%s)' "${TAR_OPTIONS[*]}"


	for INFILE
	do
		if [[ ! -e "${INFILE}" ]]
		then
			print_error '%q does not exist.' "${INFILE}"
		fi

		print_verbose 'Untarring %q' "${INFILE}"

		tar --extract --keep-old-files --one-top-level --file "${INFILE}" "${TAR_OPTIONS[@]}" || exit

		if ! ${KEEP}
		then
			del -- "${INFILE}" || exit
		fi
	done
	)
}


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


function version
{
	echo

	ls -l /etc/*-release

	echo

	cat /etc/*-release

	echo

	cat <<EOT
kernel name:           $(uname --kernel-name)
network node hostname: $(uname --nodename)
kernel release:        $(uname --kernel-release)
kernel version:        $(uname --kernel-version)
machine hardware name: $(uname --machine)
processor type:        $(uname --processor)
hardware platform:     $(uname --hardware-platform)
operating system:      $(uname --operating-system)
EOT

	echo

	uname --all
}


function vim
{
	MYVIMRC='$XDG_CONFIG_HOME/vim/init.vim' VIMINIT='source $MYVIMRC' command vim "${@}"
}


# https://github.com/chubin/wttr.in/blob/master/share/help.txt
# https://wttr.in/:bash.function
function wttr
{
	local request="wttr.in/${1}"
	[ "$(tput cols)" -lt 125 ] && request+='?n'
	curl -H "Accept-Language: ${LANG%_*}" --compressed "$request"
}

