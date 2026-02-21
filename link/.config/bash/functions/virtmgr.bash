# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function virtmgr
{
    # On a system where root can't open X,
    # use the user's .Xauthority file
    XAUTHORITY=$HOME/.Xauthority doas virt-manager "${@}"
}
