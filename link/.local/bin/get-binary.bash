#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# Run this script from the target directory.

##### XXX: maybe don't rely on set -e
# https://mywiki.wooledge.org/BashFAQ/105
set -e

SCRIPT_NAME="$(basename -- "${BASH_SOURCE[0]}")"
#SCRIPT_DIR="$(dirname -- "${BASH_SOURCE[0]}")"

SCRIPT_VERSION='2022-09-08'
SCRIPT_AUTHOR='Steven Ward'
SCRIPT_LICENSE='OSL-3.0'

VERBOSE=false

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
    printf 'Usage: %q [OPTION]... BINARY USER_REPO PART_RELEASE_FILE\n' "$SCRIPT_NAME"
    cat <<EOT

Get the program from github.  Run this script from the target directory.

OPTIONS

  -V : Print the version information, then exit.

  -h : Print this message, then exit.

  -v : Print extra output.

EOT
}

function print_warning
{
    printf 'Warning: ' 1>&2
    # shellcheck disable=SC2059
    printf -- "$@" 1>&2
    printf '\n' 1>&2
}

function print_error
{
    printf 'Error: ' 1>&2
    # shellcheck disable=SC2059
    printf -- "$@" 1>&2
    printf '\n' 1>&2

    printf 'Try "%q -h" for more information.\n' "$SCRIPT_NAME" 1>&2
    exit 1
}

function print_verbose
{
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

    v) VERBOSE=true ;;

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
BINARY="$1"
print_verbose 'BINARY=%q' "$BINARY"

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

if [[ -z "$PART_RELEASE_FILE" ]]
then
    URL_LATEST_RELEASE_DOWNLOAD="$(curl -s "$URL_LATEST_RELEASE_API_PAGE" | jq --arg BINARY "$BINARY" -r '.assets[] | select(.name==$BINARY).browser_download_url')"
else
    # https://gist.github.com/lukechilds/a83e1d7127b78fef38c2914c4ececc3c#gistcomment-2652792
    URL_LATEST_RELEASE_DOWNLOAD="$(curl -s "$URL_LATEST_RELEASE_API_PAGE" | jq --arg PART_RELEASE_FILE "$PART_RELEASE_FILE" -r '.assets[] | select(.name | contains($PART_RELEASE_FILE)).browser_download_url')"
fi
print_verbose 'URL_LATEST_RELEASE_DOWNLOAD=%q' "$URL_LATEST_RELEASE_DOWNLOAD"

RELEASE_FILE="$(basename -- "$URL_LATEST_RELEASE_DOWNLOAD")"
print_verbose 'RELEASE_FILE=%q' "$RELEASE_FILE"

curl -L -o "$RELEASE_FILE" -- "$URL_LATEST_RELEASE_DOWNLOAD"

if tar -tf "$RELEASE_FILE" &> /dev/null
then # it's a tar file

    TAR_MEMBER="$(tar --list -f "$RELEASE_FILE" | grep -E -- "^(.+/)?$BINARY\$")"
    print_verbose 'TAR_MEMBER=%q' "$TAR_MEMBER"

    # Only extract the desired file
    tar --verbose -xf "$RELEASE_FILE" "$TAR_MEMBER"

    rm --verbose -- "$RELEASE_FILE"

    TOP_FOLDER="$(dirname -- "$TAR_MEMBER")"
    print_verbose 'TOP_FOLDER=%q' "$TOP_FOLDER"

    if [ "$TOP_FOLDER" != . ]
    then
        mv --verbose -- "$TAR_MEMBER" .

        rmdir --verbose --parents -- "$TOP_FOLDER"
    fi
else # it's not a tar file

    if [ "$RELEASE_FILE" != "$BINARY" ]
    then
        mv --verbose -- "$RELEASE_FILE" "$BINARY"
    fi

    chmod --verbose --changes a+x -- "$BINARY"
fi
