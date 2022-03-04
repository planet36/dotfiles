# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash disable=SC1090,SC1091

# https://unix.stackexchange.com/a/26782
# If not running interactively, don't do anything
[[ $- != *i* ]] && return

if [[ -f "$XDG_CONFIG_HOME"/bash/config.bash ]]
then
    source "$XDG_CONFIG_HOME"/bash/config.bash
fi
