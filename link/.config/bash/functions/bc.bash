# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function bc
{
    command bc --mathlib --quiet "$XDG_CONFIG_HOME"/bc/config.bc "${@}"
}

