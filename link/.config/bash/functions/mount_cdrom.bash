# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# https://askubuntu.com/a/534711

function mount_cdrom
{
    doas mkdir --verbose --parents "/media/${USER}/cdrom" && doas mount --read-only -t auto /dev/cdrom "/media/${USER}/cdrom/"
}
