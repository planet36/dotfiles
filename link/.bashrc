# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash disable=SC1090,SC1091

# https://unix.stackexchange.com/a/26782
# If not running interactively, don't do anything
[[ $- != *i* ]] && return

# https://wiki.archlinux.org/title/Fish#Modify_.bashrc_to_drop_into_fish
if [[ -z "$BASH_EXECUTION_STRING" ]] && command -v fish > /dev/null
then
    exec fish
fi

if [[ -r "$XDG_CONFIG_HOME"/bash/config.bash ]]
then
    source "$XDG_CONFIG_HOME"/bash/config.bash
fi
