# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# shellcheck disable=SC2059

# Untar the given file(s)
function ut
{
    (
    # Change the priority of the subshell.
    renice --priority 19 --pid $BASHPID > /dev/null

    declare -r SCRIPT_NAME="${FUNCNAME[0]}"
    declare -r SCRIPT_VERSION='2022-09-08'
    declare -r SCRIPT_AUTHOR='Steven Ward'
    declare -r SCRIPT_LICENSE='MPL-2.0'

    VERBOSE=false
    KEEP=false
    declare -a TAR_OPTIONS

    function print_version
    {
        cat <<EOT
$SCRIPT_NAME $SCRIPT_VERSION
License: $SCRIPT_LICENSE
Written by $SCRIPT_AUTHOR
EOT
    }

    function print_help
    {
        cat <<EOT
Usage: $SCRIPT_NAME [OPTION]... FILE...

Untar FILE.

OPTIONS
  -V : Print the version information, then exit.

  -h : Print this message, then exit.

  -v : Print extra output.

  -k : Keep the input file.

  -t TAR_OPTION : Pass TAR_OPTION to the tar command.

EOT
    }

    function print_warning
    {
        printf 'Warning: ' 1>&2
        printf -- "$@" 1>&2
        printf '\n' 1>&2
    }

    function print_error
    {
        printf 'Error: ' 1>&2
        printf -- "$@" 1>&2
        printf '\n' 1>&2

        printf 'Try "%q -h" for more information.\n' "$SCRIPT_NAME" 1>&2
        exit 1
    }

    function print_verbose
    {
        $VERBOSE && { printf -- "$@" ; printf '\n' ; }
    }

    while getopts "Vhvkt:" OPTION
    do
        case "$OPTION" in

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
                #echo "OPTARG: $OPTARG"
                TAR_OPTIONS+=("$OPTARG")
                #echo "TAR_OPTIONS=(${TAR_OPTIONS[@]})"
                #printf -- "TAR_OPTIONS=(${TAR_OPTIONS[@]})\n"
            ;;

            *)
                # Note: $OPTION is '?'
                print_error 'Option is unknown.'
            ;;

        esac
    done

    shift $((OPTIND - 1)) || exit

    print_verbose 'KEEP=%s' "$KEEP"
    print_verbose 'TAR_OPTIONS=(%s)' "${TAR_OPTIONS[*]}"

    for INFILE
    do
        if [[ ! -e "$INFILE" ]]
        then
            print_error '%q does not exist.' "$INFILE"
        fi

        print_verbose 'Untarring %q' "$INFILE"

        tar --extract --keep-old-files --one-top-level --file "$INFILE" "${TAR_OPTIONS[@]}" || exit

        if ! $KEEP
        then
            del -- "$INFILE" || exit
        fi
    done
    )
}
