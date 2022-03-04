# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# https://askubuntu.com/a/534711

function mount_dvd
{
    doas mkdir --verbose --parents "/media/${USER}/dvd" && doas mount --read-only -t auto /dev/dvd "/media/${USER}/dvd/"
}
