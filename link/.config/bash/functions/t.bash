# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# shellcheck disable=SC2059

# Tar the given path(s)
function t
{
    (
    # Change the priority of the subshell.
    renice --priority 19 --pid $BASHPID > /dev/null

    declare -r SCRIPT_NAME="${FUNCNAME[0]}"
    declare -r SCRIPT_VERSION='2025-02-05'
    declare -r SCRIPT_AUTHOR='Steven Ward'
    declare -r SCRIPT_LICENSE='MPL-2.0'

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
License: $SCRIPT_LICENSE
Written by ${SCRIPT_AUTHOR}
EOT
    }

    function print_help
    {
        cat <<EOT
Usage: ${SCRIPT_NAME} [OPTION]... PATHNAME...

Tar PATHNAME.  Create a tar file with the same name as PATHNAME but with the appropriate extension appended.

OPTIONS
  -V : Print the version information, then exit.

  -h : Print this message, then exit.

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

            tar --create --auto-compress --file="${OUTFILE}" --owner=0 --group=0 "${TAR_OPTIONS[@]}" --directory "${DIRNAME}" -- "${BASENAME_2}" || exit
        else
            tar --create --auto-compress --file="${OUTFILE}" --owner=0 --group=0 "${TAR_OPTIONS[@]}" -- "${INFILE}" || exit
        fi

        if ${PRESERVE_TIMESTAMP}
        then
            # Preserve the timestamp.
            touch --reference="${INFILE}" -- "${OUTFILE}" || exit
        fi
    done
    )
}
