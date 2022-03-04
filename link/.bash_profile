# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash disable=SC1090

ulimit -c unlimited

if [[ -f "$XDG_CONFIG_HOME"/bash/envvars.bash ]]
then
    source "$XDG_CONFIG_HOME"/bash/envvars.bash
fi

if [[ -f "$XDG_CONFIG_HOME"/bash/envvars-private.bash ]]
then
    source "$XDG_CONFIG_HOME"/bash/envvars-private.bash
fi

if [[ -r ~/.bashrc ]]
then
    source ~/.bashrc
fi
