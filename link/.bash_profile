# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash disable=SC1090,SC1091

ulimit -c unlimited
#ulimit -s 16384

# Prepend user path
PATH="$HOME/.local/bin:$PATH"

source "${XDG_CONFIG_HOME:-$HOME/.config}"/bash/xdg-envvars.bash
source "$XDG_CONFIG_HOME"/bash/envvars.bash
source "$XDG_CONFIG_HOME"/bash/private.bash
source ~/.bashrc
