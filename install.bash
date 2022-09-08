#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# Run this script from the target directory.

# shellcheck disable=SC2059

SCRIPT_NAME="$(basename -- "${BASH_SOURCE[0]}")"
SCRIPT_DIR="$(dirname -- "${BASH_SOURCE[0]}")"

SCRIPT_VERSION='2022-09-08'
SCRIPT_AUTHOR='Steven Ward'
SCRIPT_LICENSE='OSL-3.0'

VERBOSE=false
RELATIVE=false
COPY_ALL=false
DELETE=false
DRY_RUN=false

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
    printf 'Usage: %q [OPTIONS]\n' "${BASH_SOURCE[0]}"
    cat <<EOT

Install dotfiles.  Run this script from the target directory.

Files in the "copy" directory will be copied to the target directory.
Files in the "link" directory will be symbolically linked to the target directory.
In both cases, parent directories are created, preserving directory structure.

OPTIONS

  -V : Print the version information, then exit.

  -h : Print this message, then exit.

  -v : Print extra output.
       Commands such as cp, ln, mkdir, rm, and rmdir are verbose by default.

  -r : Use a relative path when creating symbolic links.

  -c : Copy all files, even those in the "link" directory.

  -d : Attempt to delete almost everything created by this script.
       Only attempt to delete files and symbolic links that are identical to their source.
       Only attempt to delete empty folders that contained dotfiles.

  -n : Show what would be done without doing anything.

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
    if $VERBOSE
    then
        printf '# '
        printf -- "$@"
        printf '\n'
    fi
}

function copy_dotfiles
{
    SRC_DIR="$1"
    print_verbose 'SRC_DIR=%q' "$SRC_DIR"

    if [[ ! -d "$SRC_DIR" ]]
    then
        print_error 'Directory does not exist: %q' "$SRC_DIR"
    fi

    # https://mywiki.wooledge.org/BashFAQ/001#Input_source_selection
    find "$SRC_DIR" -type f -printf '%P\0' | while IFS= read -r -d '' FILE
    do
        print_verbose 'FILE=%q' "$FILE"

        DST_DIR=$(dirname -- "$FILE")
        print_verbose 'DST_DIR=%q' "$DST_DIR"

        if [[ -f "$FILE" ]]
        then
            print_verbose 'Destination file exists'

            if cmp --quiet -- "$FILE" "$SRC_DIR/$FILE"
            then
                print_verbose 'Destination and source files are the same'
                continue
            fi

            if [[ ! -s "$SRC_DIR/$FILE" ]]
            then
                print_verbose 'Source file is empty'
                continue
            fi

            if [[ "$FILE" -nt "$SRC_DIR/$FILE" ]]
            then
                print_verbose 'Destination file is newer than source file'
                continue
            fi
        fi

        if [[ "$DST_DIR" != . ]]
        then
            if $DRY_RUN
            then
                if [[ ! -d "$DST_DIR" ]]
                then
                    echo \
                    mkdir --verbose --parents -- "$DST_DIR"
                fi
            else
                if [[ ! -d "$DST_DIR" ]]
                then
                    mkdir --verbose --parents -- "$DST_DIR" || return
                fi
            fi
        fi

        if $DRY_RUN
        then
            echo \
            cp --preserve --verbose --backup=numbered --target-directory "$DST_DIR" -- "$SRC_DIR/$FILE"
        else
            cp --preserve --verbose --backup=numbered --target-directory "$DST_DIR" -- "$SRC_DIR/$FILE" || return
        fi
    done
}

function delete_copied_dotfiles
{
    SRC_DIR="$1"
    print_verbose 'SRC_DIR=%q' "$SRC_DIR"

    if [[ ! -d "$SRC_DIR" ]]
    then
        print_error 'Directory does not exist: %q' "$SRC_DIR"
    fi

    # https://mywiki.wooledge.org/BashFAQ/001#Input_source_selection
    find "$SRC_DIR" -type f -printf '%P\0' | while IFS= read -r -d '' FILE
    do
        print_verbose 'FILE=%q' "$FILE"

        DST_DIR=$(dirname -- "$FILE")
        print_verbose 'DST_DIR=%q' "$DST_DIR"

        if [[ ! -f "$FILE" ]]
        then
            print_verbose 'Destination does not file exist'
            continue
        fi

        if ! cmp --quiet -- "$FILE" "$SRC_DIR/$FILE"
        then
            print_verbose 'Destination and source files are not the same'
            continue
        fi

        if $DRY_RUN
        then
            echo \
            rm --verbose -- "$FILE"
        else
            rm --verbose -- "$FILE" || return
        fi

        if [[ "$DST_DIR" != . ]]
        then
            if $DRY_RUN
            then
                echo \
                rmdir --verbose --parents --ignore-fail-on-non-empty -- "$DST_DIR"
            else
                rmdir --verbose --parents --ignore-fail-on-non-empty -- "$DST_DIR" || return
            fi
        fi
    done
}

function link_dotfiles
{
    SRC_DIR="$1"
    print_verbose 'SRC_DIR=%q' "$SRC_DIR"

    if [[ ! -d "$SRC_DIR" ]]
    then
        print_error 'Directory does not exist: %q' "$SRC_DIR"
    fi

    # https://mywiki.wooledge.org/BashFAQ/001#Input_source_selection
    find "$SRC_DIR" -type f -printf '%P\0' | while IFS= read -r -d '' FILE
    do
        print_verbose 'FILE=%q' "$FILE"

        DST_DIR=$(dirname -- "$FILE")
        print_verbose 'DST_DIR=%q' "$DST_DIR"

        if [[ -h "$FILE" ]]
        then
            print_verbose 'Destination link exists'

            if [[ "$(realpath -- "$FILE")" == "$(realpath -- "$SRC_DIR/$FILE")" ]]
            then
                print_verbose 'Destination link target is the same as the source file'
                continue
            fi
        fi

        if [[ "$DST_DIR" != . ]]
        then
            if $DRY_RUN
            then
                if [[ ! -d "$DST_DIR" ]]
                then
                    echo \
                    mkdir --verbose --parents -- "$DST_DIR"
                fi
            else
                if [[ ! -d "$DST_DIR" ]]
                then
                    mkdir --verbose --parents -- "$DST_DIR" || return
                fi
            fi
        fi

        if $RELATIVE
        then
            if $DRY_RUN
            then
                echo \
                ln --symbolic --verbose --backup=numbered --target-directory "$DST_DIR" --relative -- "$SRC_DIR/$FILE"
            else
                ln --symbolic --verbose --backup=numbered --target-directory "$DST_DIR" --relative -- "$SRC_DIR/$FILE" || return
            fi
        else
            if $DRY_RUN
            then
                echo \
                ln --symbolic --verbose --backup=numbered --target-directory "$DST_DIR" -- "$(realpath -- "$SRC_DIR/$FILE")"
            else
                ln --symbolic --verbose --backup=numbered --target-directory "$DST_DIR" -- "$(realpath -- "$SRC_DIR/$FILE")" || return
            fi
        fi
    done
}

function delete_linked_dotfiles
{
    SRC_DIR="$1"
    print_verbose 'SRC_DIR=%q' "$SRC_DIR"

    if [[ ! -d "$SRC_DIR" ]]
    then
        print_error 'Directory does not exist: %q' "$SRC_DIR"
    fi

    # https://mywiki.wooledge.org/BashFAQ/001#Input_source_selection
    find "$SRC_DIR" -type f -printf '%P\0' | while IFS= read -r -d '' FILE
    do
        print_verbose 'FILE=%q' "$FILE"

        DST_DIR=$(dirname -- "$FILE")
        print_verbose 'DST_DIR=%q' "$DST_DIR"

        if [[ ! -h "$FILE" ]]
        then
            print_verbose 'Destination link does not exist'
            continue
        fi

        if [[ "$(realpath -- "$FILE")" != "$(realpath -- "$SRC_DIR/$FILE")" ]]
        then
            print_verbose 'Destination link target is not the same as the source file'
            continue
        fi

        if $DRY_RUN
        then
            echo \
            rm --verbose -- "$FILE"
        else
            rm --verbose -- "$FILE" || return
        fi

        if [[ "$DST_DIR" != . ]]
        then
            if $DRY_RUN
            then
                echo \
                rmdir --verbose --parents --ignore-fail-on-non-empty -- "$DST_DIR"
            else
                rmdir --verbose --parents --ignore-fail-on-non-empty -- "$DST_DIR" || return
            fi
        fi
    done
}

function parse_options
{
    while getopts 'Vhvrcdn' OPTION
    do
        case "$OPTION" in

        V) print_version ; exit ;;

        h) print_help ; exit ;;

        v) VERBOSE=true ;;

        r) RELATIVE=true ;;

        c) COPY_ALL=true ;;

        d) DELETE=true ;;

        n) DRY_RUN=true ;;

        *)
            # Note: $OPTION is '?'
            #print_error "Option is unknown."
            exit 1
            ;;

        esac
    done

    shift $((OPTIND - 1))

    print_verbose 'RELATIVE=%s' "$RELATIVE"
    print_verbose 'COPY_ALL=%s' "$COPY_ALL"
    print_verbose 'DELETE=%s' "$DELETE"
    print_verbose 'DRY_RUN=%s' "$DRY_RUN"
}

function main
{
    if [[ "$PWD" == "$(realpath -- "$SCRIPT_DIR")"* ]]
    then
        print_error 'May not install dotfiles within itself'
    fi

    REL_DOTFILES_DIR="$(realpath --relative-to "$PWD" -- "$SCRIPT_DIR")"
    print_verbose 'REL_DOTFILES_DIR=%q' "$REL_DOTFILES_DIR"

    # shellcheck disable=SC1091
    source "$SCRIPT_DIR"/link/.config/bash/xdg-envvars.bash || return

    if $DELETE
    then
        # Only delete dotfiles, not unrelated empty dirs, such as XDG base dirs.

        delete_copied_dotfiles "$REL_DOTFILES_DIR"/copy || return

        if $COPY_ALL
        then
            delete_copied_dotfiles "$REL_DOTFILES_DIR"/link || return
        else
            delete_linked_dotfiles "$REL_DOTFILES_DIR"/link || return
        fi

        if ! $DRY_RUN
        then
            fc-cache || return
        fi
    else
        copy_dotfiles "$REL_DOTFILES_DIR"/copy || return

        if $COPY_ALL
        then
            copy_dotfiles "$REL_DOTFILES_DIR"/link || return
        else
            link_dotfiles "$REL_DOTFILES_DIR"/link || return
        fi

        if ! $DRY_RUN
        then
            fc-cache || return
        fi

        if ! $DRY_RUN
        then
            python3     -m compileall ~/.local/lib/python/ || return
            python3 -O  -m compileall ~/.local/lib/python/ || return
            python3 -OO -m compileall ~/.local/lib/python/ || return
        fi
    fi
}

parse_options "$@"

main
