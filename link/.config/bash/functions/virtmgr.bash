# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function virtmgr
{
    # On a system where root can't open X,
    # use the user's .Xauthority file
    XAUTHORITY=$HOME/.Xauthority sudo virt-manager "${@}"
}

