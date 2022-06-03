# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash disable=SC1090,SC1091

ulimit -c unlimited

# Prepend user path
PATH="$HOME/.local/bin:$PATH"

source "${XDG_CONFIG_HOME:-$HOME/.config}"/bash/xdg-envvars.bash || return

if [[ -r "$XDG_CONFIG_HOME"/bash/envvars.bash ]]
then
    source "$XDG_CONFIG_HOME"/bash/envvars.bash || return
fi

if [[ -r "$XDG_CONFIG_HOME"/bash/private.bash ]]
then
    source "$XDG_CONFIG_HOME"/bash/private.bash || return
fi

if [[ -r ~/.bashrc ]]
then
    source ~/.bashrc
fi
