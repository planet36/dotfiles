# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash disable=SC1090

umask 022

ulimit -c unlimited

# {{{ prepend user path

if [[ -d "$HOME/.local/bin" ]]
then
    PATH="$HOME/.local/bin:$PATH"
fi

# }}}

# {{{ XDG vars

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
}

setup_xdg_vars

# }}}

# {{{ env vars

export CC=gcc
export CXX=g++

if command -p -v nvim > /dev/null
then
    export EDITOR=nvim
    export VISUAL=nvim
elif command -p -v vim > /dev/null
then
    export EDITOR=vim
    export VISUAL=vim
fi

export FZF_DEFAULT_OPTS='--multi --inline-info --ansi --tabstop=4 --color=bg+:25,fg+:220,gutter:-1 --preview-window=right'

if command -v highlight > /dev/null
then
    #FZF_DEFAULT_OPTS+=' --preview "highlight -- {} | head -n $FZF_PREVIEW_LINES"'
    # --line-range option added in highlight 3.43 (2018-04-30)
    # shellcheck disable=SC2016
    FZF_DEFAULT_OPTS+=' --preview "highlight --line-range=1-$FZF_PREVIEW_LINES -- {}"'
else
    # shellcheck disable=SC2016
    FZF_DEFAULT_OPTS+=' --preview "head -n $FZF_PREVIEW_LINES -- {}"'
fi

export GIT_EDITOR="$EDITOR"

export HIGHLIGHT_OPTIONS='--force -t 4 --out-format=ansi'

export IPYTHONDIR="$XDG_DATA_HOME"/ipython

#export LANG=en_US.UTF-8
#export LC_ALL=en_US.UTF-8

#export LESS='--RAW-CONTROL-CHARS --quit-if-one-screen --no-init'
export LESS='--RAW-CONTROL-CHARS --no-init'
export LESSHISTFILE=/dev/null

# Inhibit these dbind warnings: Couldn't register with accessibility bus
# https://wiki.archlinux.de/title/GNOME#Tipps_und_Tricks
# https://askubuntu.com/a/318997
# This affects meld.
export NO_AT_BRIDGE=1

# https://www.reddit.com/r/linux/comments/12wxsl/whats_in_your_bashrc/c6z0y5g/
#export JAVA_HOME="$(readlink -f -- "$(which javac)" | sed 's|bin/javac||')"

export PS_FORMAT='pid,nice,pri,user,stime,etime,sz,pmem,pcpu,command'

export PYLINTHOME="$XDG_CACHE_HOME"/pylint.d

# https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPATH
export PYTHONPATH="$HOME"/.local/lib/python

# https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPYCACHEPREFIX
export PYTHONPYCACHEPREFIX="$XDG_CACHE_HOME"/__pycache__

export RSYNC_ARGS='-v -c -u -p -t -r -z -h'
#-v, --verbose               increase verbosity
#-c, --checksum              always checksum
#-u, --update                update only (don't overwrite newer files)
#-p, --perms                 preserve permissions
#-t, --times                 preserve times
#-n, --dry-run               show what would have been transferred
#-r, --recursive             recurse into directories
#-z, --compress              compress file data during the transfer
#-C, --cvs-exclude           auto ignore files in the same way CVS does
#-h, --human-readable        output numbers in a human-readable format
#    --progress              show progress during transfer
#-i, --itemize-changes       output a change-summary for all updates
#    --password-file=FILE    read daemon-access password from FILE

# /usr/bin/time format similar to bash's time
export TIME="real\t%E\nuser\t%U\nsys\t%S\n"

export TRASH_DIR="$XDG_DATA_HOME"/Trash
if [[ ! -d "$TRASH_DIR" ]]
then
    mkdir --verbose --mode=0700 -- "$TRASH_DIR"
fi

export TZ=':America/New_York'

#export VCS_REPOS_MATCH='( -type d -and ( -name CVS -or -name .svn -or -name .git -or -name .hg ) )'
#export VCS_REPOS_PRUNE="( $VCS_REPOS_MATCH -prune , -not $VCS_REPOS_MATCH )"

if [[ ! -d "$XDG_CACHE_HOME"/xorg ]]
then
    mkdir --verbose --parents -- "$XDG_CACHE_HOME"/xorg
fi
export XAUTHORITY="$XDG_CACHE_HOME"/xorg/Xauthority

# }}}

# {{{ compile options

# Too many benign warnings:
# -Wpadded
# -Wfloat-equal
export GCC_COMMON_OPTIONS='-O2 -pipe -Wall -Wextra -Wpedantic -Wfatal-errors -Wcast-align -Wcast-qual -Wduplicated-branches -Wduplicated-cond -Wformat-overflow=2 -Wformat=2 -Wlogical-op -Wmissing-include-dirs -Wshadow -Wswitch-default -Wswitch-enum -Wuninitialized -Wunsafe-loop-optimizations'
# https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
GCC_COMMON_OPTIONS+=' -D_FORTIFY_SOURCE=2'
# https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html
GCC_COMMON_OPTIONS+=' -fstack-protector'
# https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
GCC_COMMON_OPTIONS+=' -D_GNU_SOURCE'

export EXTRACXXFLAGS='-fchar8_t -fcoroutines -fdiagnostics-show-template-tree -Wctor-dtor-privacy -Wextra-semi -Wmismatched-tags -Wmultiple-inheritance -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-tags -Wsign-promo -Wstrict-null-sentinel -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wuseless-cast -Wzero-as-null-pointer-constant'

# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
#OPTIMIZE_OPTIONS='-O3 -march=native -fassociative-math -fno-math-errno -freciprocal-math -fno-signed-zeros -fno-trapping-math'
# Using -fsigned-zeros disables associative-math
#OPTIMIZE_OPTIONS='-O3 -march=native -fno-math-errno -freciprocal-math -fno-trapping-math'
export OPTIMIZE_OPTIONS='-O3 -flto -march=native'

export DEBUG_OPTIONS='-Og -ggdb3'
# https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html
DEBUG_OPTIONS+=' -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG -D_GLIBCXX_SANITIZE_VECTOR'

export PERF_TEST_OPTIONS="$OPTIMIZE_OPTIONS -fno-allocation-dce -fno-dce -fno-dse -fno-gcse -fno-split-paths -fno-tree-builtin-call-dce -fno-tree-copy-prop -fno-tree-dce -fno-tree-dse -fno-tree-fre -fno-tree-partial-pre -fno-tree-pre"

export PROFILE_OPTIONS="$PERF_TEST_OPTIONS -pg"

export CFLAGS="$GCC_COMMON_OPTIONS -std=c2x"
export CXXFLAGS="$GCC_COMMON_OPTIONS -std=c++20 $EXTRACXXFLAGS"

# }}}

if [[ -r ~/.bashrc ]]
then
    source ~/.bashrc
fi
