#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# Run this script from the target directory.

##### XXX: maybe don't rely on set -e
# https://mywiki.wooledge.org/BashFAQ/105
set -e

SCRIPT_NAME="$(basename -- "${BASH_SOURCE[0]}")"
#SCRIPT_DIR="$(dirname -- "${BASH_SOURCE[0]}")"

SCRIPT_VERSION='2021-01-06'
SCRIPT_AUTHOR='Steven Ward'

VERBOSE=false
VERBOSE_OPTION=''

print_version() {

    cat <<EOT
$SCRIPT_NAME $SCRIPT_VERSION
Written by $SCRIPT_AUTHOR
EOT
}

print_help() {

    printf 'Usage: %q [OPTIONS] PROGRAM USER_REPO PART_RELEASE_FILE\n' "$SCRIPT_NAME"
    cat <<EOT

Get the program from github.  Run this script from the target directory.

OPTIONS

  -V : Print the version information and exit.

  -h : Print this message and exit.

  -v : Print extra output.

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

while getopts 'Vhv' OPTION
do
    case "$OPTION" in

    V) print_version ; exit ;;

    h) print_help ; exit ;;

    v) VERBOSE=true ; VERBOSE_OPTION='--verbose' ;;

    *)
        # Note: $OPTION is '?'
        #print_error "Option is unknown."
        exit 1
        ;;

    esac
done

shift $((OPTIND - 1))

if [ "$#" -ne 3 ]
then
    print_error 'Must give 3 args'
fi

# name of the executable
PROGRAM="$1"
print_verbose 'PROGRAM=%q' "$PROGRAM"

# github user and repo name separated by slash
USER_REPO="$2"
print_verbose 'USER_REPO=%q' "$USER_REPO"

# minimal distinct part of the release file name
PART_RELEASE_FILE="$3"
print_verbose 'PART_RELEASE_FILE=%q' "$PART_RELEASE_FILE"

URL_LATEST_RELEASE_API_PAGE="https://api.github.com/repos/$USER_REPO/releases/latest"
print_verbose 'URL_LATEST_RELEASE_API_PAGE=%q' "$URL_LATEST_RELEASE_API_PAGE"
# latest tag:
# curl -s "$URL_LATEST_RELEASE_API_PAGE" | jq -r .tag_name

# https://gist.github.com/lukechilds/a83e1d7127b78fef38c2914c4ececc3c#gistcomment-2652792
URL_LATEST_RELEASE_DOWNLOAD="$(curl -s "$URL_LATEST_RELEASE_API_PAGE" | jq --arg PART_RELEASE_FILE "$PART_RELEASE_FILE" -r '.assets[] | select(.name | contains($PART_RELEASE_FILE)).browser_download_url')"
print_verbose 'URL_LATEST_RELEASE_DOWNLOAD=%q' "$URL_LATEST_RELEASE_DOWNLOAD"

RELEASE_FILE="$(basename -- "$URL_LATEST_RELEASE_DOWNLOAD")"
print_verbose 'RELEASE_FILE=%q' "$RELEASE_FILE"

print_verbose '(download release file)'
curl -s -L -o "$RELEASE_FILE" -- "$URL_LATEST_RELEASE_DOWNLOAD"

if tar -tf "$RELEASE_FILE" &> /dev/null
then # it's a tar file

    TAR_MEMBER="$(tar --list -f "$RELEASE_FILE" | grep -E -- "^(.+/)?$PROGRAM\$")"
    print_verbose 'TAR_MEMBER=%q' "$TAR_MEMBER"

    # Only extract the desired file
    # shellcheck disable=SC2086
    tar $VERBOSE_OPTION -xf "$RELEASE_FILE" "$TAR_MEMBER"

    # shellcheck disable=SC2086
    rm $VERBOSE_OPTION -- "$RELEASE_FILE"

    TOP_FOLDER="$(dirname -- "$TAR_MEMBER")"
    print_verbose 'TOP_FOLDER=%q' "$TOP_FOLDER"

    if [ "$TOP_FOLDER" != . ]
    then
        # shellcheck disable=SC2086
        mv $VERBOSE_OPTION -- "$TAR_MEMBER" .

        # shellcheck disable=SC2086
        rm $VERBOSE_OPTION -r -- "$TOP_FOLDER"
    fi
else # it's not a tar file

    if [ "$RELEASE_FILE" != "$PROGRAM" ]
    then
        # shellcheck disable=SC2086
        mv $VERBOSE_OPTION -- "$RELEASE_FILE" "$PROGRAM"
    fi

    # shellcheck disable=SC2086
    chmod $VERBOSE_OPTION a+x -- "$PROGRAM"
fi
