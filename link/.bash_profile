# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash disable=SC1090,SC1091

ulimit -c unlimited

# Prepend user path
PATH="$HOME/.local/bin:$PATH"

source "${XDG_CONFIG_HOME:-$HOME/.config}"/bash/xdg-envvars.bash || return

source "$XDG_CONFIG_HOME"/bash/envvars.bash || return

source "$XDG_CONFIG_HOME"/bash/private.bash || return

source ~/.bashrc
