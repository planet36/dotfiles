# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# https://askubuntu.com/a/534711

function mount_dvd
{
    sudo mkdir --verbose --parents "/media/${USER}/dvd" && sudo mount --read-only -t auto /dev/dvd "/media/${USER}/dvd/"
}
