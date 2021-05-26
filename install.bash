#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# Run this script from the target directory.

# shellcheck disable=SC2059

SCRIPT_NAME="$(basename -- "${BASH_SOURCE[0]}")"
SCRIPT_DIR="$(dirname -- "${BASH_SOURCE[0]}")"

SCRIPT_VERSION='2021-05-18'
SCRIPT_AUTHOR='Steven Ward'

VERBOSE=false
RELATIVE=false
COPY_ALL=false
DELETE=false
INSTALL_PROGRAMS=false
DRY_RUN=false

print_version() {

    cat <<EOT
$SCRIPT_NAME $SCRIPT_VERSION
Written by $SCRIPT_AUTHOR
EOT
}

print_help() {

    printf 'Usage: %q [OPTIONS]\n' "${BASH_SOURCE[0]}"
    cat <<EOT

Install dotfiles.  Run this script from the target directory.

Files in the "copy" directory will be copied to the target directory.
Files in the "link" directory will be symbolically linked to the target directory.
In both cases, parent directories are created, preserving directory structure.

OPTIONS

  -V : Print the version information and exit.

  -h : Print this message and exit.

  -v : Print extra output.
       Commands such as cp, ln, mkdir, rm, and rmdir are verbose by default.

  -r : Use a relative path when creating symbolic links.

  -c : Copy all files, even those in the "link" directory.

  -d : Attempt to delete almost everything created by this script.
       Only attempt to delete files and symbolic links that are identical to their source.
       Only attempt to delete empty folders that contained dotfiles.

  -p : In addition to dotfiles, also install the following:
       vim/nvim plugins listed in the file "plugins.vim"
       programs to ~/.local/bin
         - as_bool
         - cmeter
         - cpuavgd
         - dir_is_empty
         - durfmt
         - dwm
         - netrxavgd
         - nettxavgd
         - slstatus
         - st
         - stw
         - swp
       binaries from github listed in the file "get-all-binaries.bash"
       fish plugins
         - fisher
         - getopts
         - z

  -n : Show what would be done without doing anything.

EOT
}

print_warning() {

    printf 'Warning: ' 1>&2
    printf -- "$@" 1>&2
    printf '\n' 1>&2
}

print_error() {

    printf 'Error: ' 1>&2
    printf -- "$@" 1>&2
    printf '\n' 1>&2

    printf 'Try "%q -h" for more information.\n' "$SCRIPT_NAME" 1>&2
    exit 1
}

print_verbose() {

    if $VERBOSE
    then
        printf '# '
        printf -- "$@"
        printf '\n'
    fi
}

copy_dotfiles() {

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

delete_copied_dotfiles() {

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

link_dotfiles() {

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

delete_linked_dotfiles () {

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

setup_xdg_vars() {

    # https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html

    : "${XDG_CACHE_HOME:=$HOME/.cache}"
    : "${XDG_CONFIG_DIRS:=/etc/xdg}"
    : "${XDG_CONFIG_HOME:=$HOME/.config}"
    : "${XDG_DATA_DIRS:=/usr/local/share/:/usr/share/}"
    : "${XDG_DATA_HOME:=$HOME/.local/share}"

    export XDG_CACHE_HOME
    export XDG_CONFIG_DIRS
    export XDG_CONFIG_HOME
    export XDG_DATA_DIRS
    export XDG_DATA_HOME

    mkdir --verbose --parents -- "$XDG_CACHE_HOME"
    mkdir --verbose --parents -- "$XDG_CONFIG_HOME"
    mkdir --verbose --parents -- "$XDG_DATA_HOME"

    # XDG environment variables have been set
    # XDG base directories have been created
}

create_vim_nvim_dirs() {

    if $DRY_RUN
    then
        echo \
        mkdir --verbose --parents -- \
            "$XDG_DATA_HOME"/vim/{autoload,backup,colors,swap,undo}

        echo \
        mkdir --verbose --parents -- \
            "$XDG_DATA_HOME"/nvim/{site/autoload,backup,colors,swap,undo}
    else
        mkdir --verbose --parents -- \
            "$XDG_DATA_HOME"/vim/{autoload,backup,colors,swap,undo} || return

        mkdir --verbose --parents -- \
            "$XDG_DATA_HOME"/nvim/{site/autoload,backup,colors,swap,undo} || return
    fi
}

install_vim_nvim_plugins() {

    if command -v vim > /dev/null
    then
        #vim +PlugUpgrade +PlugInstall +qall
        if $DRY_RUN
        then
            echo \
            vim -c PlugInstall -c qall
        else
            vim -c PlugInstall -c qall || return
        fi
    fi

    if command -v nvim > /dev/null
    then
        #nvim -c PlugUpgrade -c PlugInstall -c qall
        if $DRY_RUN
        then
            echo \
            nvim -c PlugInstall -c qall
        else
            nvim -c PlugInstall -c qall || return
        fi
    fi
}

uninstall_vim_nvim_plugins() {

    if command -v vim > /dev/null && [[ -f "$XDG_CONFIG_HOME"/vim/plugins-empty.vim ]]
    then
        if $DRY_RUN
        then
            # shellcheck disable=SC2016
            echo \
            vim -c ':source $XDG_CONFIG_HOME/vim/plugins-empty.vim' -c PlugClean! -c qall
        else
            # shellcheck disable=SC2016
            vim -c ':source $XDG_CONFIG_HOME/vim/plugins-empty.vim' -c PlugClean! -c qall || return
        fi
    fi

    if command -v nvim > /dev/null && [[ -f "$XDG_CONFIG_HOME"/vim/plugins-empty.vim ]]
    then
        if $DRY_RUN
        then
            # shellcheck disable=SC2016
            echo \
            nvim -c ':source $XDG_CONFIG_HOME/nvim/plugins-empty.vim' -c PlugClean! -c qall
        else
            # shellcheck disable=SC2016
            nvim -c ':source $XDG_CONFIG_HOME/nvim/plugins-empty.vim' -c PlugClean! -c qall || return
        fi
    fi
}

install_local_programs() {

    if $DRY_RUN
    then
        echo \
        make PREFIX="$HOME"/.local -C "$SCRIPT_DIR"/build install
    else
        make PREFIX="$HOME"/.local -C "$SCRIPT_DIR"/build install || return
    fi

    pushd . &> /dev/null

    cd ~/.local/src || return

    if $DRY_RUN
    then
        echo "# clone and build repos"
    else
        bash clone-build-repos.bash || return
    fi

    # https://github.com/koalaman/shellcheck/issues/613
    # shellcheck disable=SC2164
    popd &> /dev/null
}

uninstall_local_programs() {

    if $DRY_RUN
    then
        echo \
        make PREFIX="$HOME"/.local -C "$SCRIPT_DIR"/build uninstall
    else
        make PREFIX="$HOME"/.local -C "$SCRIPT_DIR"/build uninstall || return
    fi

    for LINK in dwm slstatus st stw
    do
        if [[ -L ~/.local/bin/"$LINK" ]]
        then
            if $DRY_RUN
            then
                echo \
                rm --verbose ~/.local/bin/"$LINK"
            else
                rm --verbose ~/.local/bin/"$LINK" || return
            fi
        fi
    done
}

install_github_programs() {

    pushd . &> /dev/null

    cd ~/.local/bin || return

    if $DRY_RUN
    then
        bash get-all-binaries.bash -v -n
    else
        bash get-all-binaries.bash -v    || return
    fi

    # https://github.com/koalaman/shellcheck/issues/613
    # shellcheck disable=SC2164
    popd &> /dev/null
}

uninstall_github_programs() {

    pushd . &> /dev/null

    cd ~/.local/bin || return

    for PROGRAM in $(bash get-all-binaries.bash -n | cut -f1)
    do
        if [[ -f "$PROGRAM" ]]
        then
            if $DRY_RUN
            then
                echo \
                rm --verbose -- "$PROGRAM"
            else
                rm --verbose -- "$PROGRAM" || return
            fi
        fi
    done

    # https://github.com/koalaman/shellcheck/issues/613
    # shellcheck disable=SC2164
    popd &> /dev/null
}


install_fish_plugins() {

    if command -v fish > /dev/null
    then
        if $DRY_RUN
        then
            # https://github.com/jorgebucaran/fisher
            echo  \
            fish -c 'curl -sL https://git.io/fisher | source && fisher install jorgebucaran/fisher'

            # https://github.com/jorgebucaran/getopts.fish
            echo  \
            fish -c 'fisher install jorgebucaran/getopts.fish'

            # https://github.com/jethrokuan/z
            echo  \
            fish -c 'fisher install jethrokuan/z'
        else
            # https://github.com/jorgebucaran/fisher
            fish -c 'curl -sL https://git.io/fisher | source && fisher install jorgebucaran/fisher' || return

            # https://github.com/jorgebucaran/getopts.fish
            fish -c 'fisher install jorgebucaran/getopts.fish' || return

            # https://github.com/jethrokuan/z
            fish -c 'fisher install jethrokuan/z' || return
        fi
    fi
}


uninstall_fish_plugins() {

    if command -v fish > /dev/null
    then
        if $DRY_RUN
        then
            echo  \
            fish -c 'fisher list | fisher remove'
        else
            fish -c 'fisher list | fisher remove' || return
        fi
    fi
}


parse_options() {

    while getopts 'Vhvrcdpn' OPTION
    do
        case "$OPTION" in

        V) print_version ; exit ;;

        h) print_help ; exit ;;

        v) VERBOSE=true ;;

        r) RELATIVE=true ;;

        c) COPY_ALL=true ;;

        d) DELETE=true ;;

        p) INSTALL_PROGRAMS=true ;;

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
    print_verbose 'INSTALL_PROGRAMS=%s' "$INSTALL_PROGRAMS"
    print_verbose 'DRY_RUN=%s' "$DRY_RUN"
}

main() {

    if [[ "$PWD" == "$(realpath -- "$SCRIPT_DIR")"* ]]
    then
        print_error 'May not install dotfiles within itself'
    fi

    REL_DOTFILES_DIR="$(realpath --relative-to "$PWD" -- "$SCRIPT_DIR")"
    print_verbose 'REL_DOTFILES_DIR=%q' "$REL_DOTFILES_DIR"

    setup_xdg_vars || return

    if $DELETE
    then
        # Only delete dotfiles, not unrelated empty dirs, such as XDG base dirs.

        if $INSTALL_PROGRAMS
        then
            uninstall_vim_nvim_plugins || return
            uninstall_local_programs   || return
            uninstall_github_programs  || return
            uninstall_fish_plugins     || return
        fi

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
        mkdir --verbose --parents -- ~/.local/{bin,lib,src} || return
        mkdir --verbose --parents -- ~/Downloads || return

        create_vim_nvim_dirs || return

        copy_dotfiles "$REL_DOTFILES_DIR"/copy || return

        if $COPY_ALL
        then
            copy_dotfiles "$REL_DOTFILES_DIR"/link || return
        else
            link_dotfiles "$REL_DOTFILES_DIR"/link || return
        fi

        if ! $DRY_RUN
        then
            if command -v thefuck > /dev/null
            then
                thefuck --alias > "$XDG_CONFIG_HOME"/fish/functions/fuck.fish || return
            fi
        fi

        if ! $DRY_RUN
        then
            fc-cache || return
        fi

        if ! $DRY_RUN
        then
            python3    -m compileall ~/.local/lib/python/ || return
            python3 -O -m compileall ~/.local/lib/python/ || return
        fi

        if $INSTALL_PROGRAMS
        then
            install_vim_nvim_plugins || return
            install_local_programs   || return
            install_github_programs  || return
            install_fish_plugins     || return
        fi
    fi

    if [[ -f ~/.bash_logout ]]
    then
        mv --verbose -- ~/.bash_logout ~/.bash_logout.~1~
    fi

    if [[ -f ~/.bash_history ]]
    then
        #mv --verbose -- ~/.bash_history "$XDG_DATA_HOME"/bash/history
        mv --verbose -- ~/.bash_history ~/.bash_history.~1~
    fi
}

parse_options "$@"

main
