# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function setup_xdg_vars
{
    # https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html

    : "${XDG_CACHE_HOME:=$HOME/.cache}"
    : "${XDG_CONFIG_DIRS:=/etc/xdg}"
    : "${XDG_CONFIG_HOME:=$HOME/.config}"
    : "${XDG_DATA_DIRS:=/usr/local/share/:/usr/share/}"
    : "${XDG_DATA_HOME:=$HOME/.local/share}"
    : "${XDG_STATE_HOME:=$HOME/.local/state}"

    export XDG_CACHE_HOME
    export XDG_CONFIG_DIRS
    export XDG_CONFIG_HOME
    export XDG_DATA_DIRS
    export XDG_DATA_HOME
    export XDG_STATE_HOME

    mkdir --verbose --parents -- "$XDG_CACHE_HOME"
    mkdir --verbose --parents -- "$XDG_CONFIG_HOME"
    mkdir --verbose --parents -- "$XDG_DATA_HOME"
    mkdir --verbose --parents -- "$XDG_STATE_HOME"

    # XDG environment variables have been set
    # XDG base directories have been created
}

setup_xdg_vars
