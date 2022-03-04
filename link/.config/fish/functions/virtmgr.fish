# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function virtmgr --wraps virt-manager
    # On a system where root can't open X,
    # use the user's .Xauthority file
    XAUTHORITY=$HOME/.Xauthority doas virt-manager $argv
end
