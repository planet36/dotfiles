#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# Run this script from the target directory.

SCRIPT_NAME="$(basename -- "${BASH_SOURCE[0]}")"
SCRIPT_DIR="$(dirname -- "${BASH_SOURCE[0]}")"

SCRIPT_VERSION='2021-01-07'
SCRIPT_AUTHOR='Steven Ward'

VERBOSE=false
DRY_RUN=false
LIST_PROGRAMS=false
VERBOSE_OPTION=''

print_version() {

    cat <<EOT
$SCRIPT_NAME $SCRIPT_VERSION
Written by $SCRIPT_AUTHOR
EOT
}

print_help() {

    printf 'Usage: %q [OPTIONS]\n' "${BASH_SOURCE[0]}"
    cat <<EOT

Get programs from github.  Run this script from the target directory.

OPTIONS

  -V : Print the version information and exit.

  -h : Print this message and exit.

  -v : Print extra output.

  -n : Show what would be done without doing anything.

  -l : List programs and exit.

EOT
}

print_warning() {

    printf 'Warning: ' 1>&2
    # shellcheck disable=SC2059
    printf -- "$@" 1>&2
    printf '\n' 1>&2
}

print_error() {

    printf 'Error: ' 1>&2
    # shellcheck disable=SC2059
    printf -- "$@" 1>&2
    printf '\n' 1>&2

    printf 'Try "%q -h" for more information.\n' "$SCRIPT_NAME" 1>&2
    exit 1
}

print_verbose() {

    if $VERBOSE
    then
        printf '# '
        # shellcheck disable=SC2059
        printf -- "$@"
        printf '\n'
    fi
}

while getopts 'Vhvnl' OPTION
do
    case "$OPTION" in

    V) print_version ; exit ;;

    h) print_help ; exit ;;

    v) VERBOSE=true ; VERBOSE_OPTION='-v' ;;

    n) DRY_RUN=true ;;

    l) LIST_PROGRAMS=true ;;

    *)
        # Note: $OPTION is '?'
        #print_error "Option is unknown."
        exit 1
        ;;

    esac
done

shift $((OPTIND - 1))

print_verbose 'DRY_RUN=%s' "$DRY_RUN"

declare -a PROGRAMS
PROGRAMS=(
    'btm'
    'delta'
    'gotop'
    'lsd'
    'yay'
    #'zoxide'
)

declare -A PROGRAM_TO_USER_REPO
PROGRAM_TO_USER_REPO=(
    ['btm']='ClementTsang/bottom'
    ['delta']='dandavison/delta'
    ['gotop']='xxxserxxx/gotop'
    ['lsd']='Peltoche/lsd'
    ['yay']='Jguer/yay'
    #['zoxide']='ajeetdsouza/zoxide'
)

declare -A PROGRAM_TO_PART_RELEASE_FILE
PROGRAM_TO_PART_RELEASE_FILE=(
    ['btm']='x86_64-unknown-linux-gnu'
    ['delta']='x86_64-unknown-linux-gnu'
    ['gotop']='linux_amd64'
    ['lsd']='x86_64-unknown-linux-gnu'
    ['yay']='x86_64'
    #['zoxide']='x86_64-unknown-linux-gnu'
)

if ${LIST_PROGRAMS}
then
    for PROGRAM in "${PROGRAMS[@]}"
    do
        USER_REPO="${PROGRAM_TO_USER_REPO[${PROGRAM}]}"
        PART_RELEASE_FILE="${PROGRAM_TO_PART_RELEASE_FILE[${PROGRAM}]}"
        printf '%q\t%q\t%q\n' "$PROGRAM" "$USER_REPO" "$PART_RELEASE_FILE"
    done
    exit
fi

for PROGRAM in "${PROGRAMS[@]}"
do
    print_verbose 'PROGRAM=%q' "$PROGRAM"

    USER_REPO="${PROGRAM_TO_USER_REPO[${PROGRAM}]}"
    print_verbose 'USER_REPO=%q' "$USER_REPO"

    PART_RELEASE_FILE="${PROGRAM_TO_PART_RELEASE_FILE[${PROGRAM}]}"
    print_verbose 'PART_RELEASE_FILE=%q' "$PART_RELEASE_FILE"

    if $DRY_RUN
    then
        # shellcheck disable=SC2086
        echo \
        bash "${SCRIPT_DIR}"/get-program.bash ${VERBOSE_OPTION} "${PROGRAM}" "${USER_REPO}" "${PART_RELEASE_FILE}"
    else
        # shellcheck disable=SC2086
        bash "${SCRIPT_DIR}"/get-program.bash ${VERBOSE_OPTION} "${PROGRAM}" "${USER_REPO}" "${PART_RELEASE_FILE}"
    fi
done
