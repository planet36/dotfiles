# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# https://askubuntu.com/a/534711

function mount_cdrom
{
	sudo mkdir --verbose --parents "/media/${USER}/cdrom" && sudo mount --read-only -t auto /dev/cdrom "/media/${USER}/cdrom/"
}

