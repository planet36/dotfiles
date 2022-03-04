# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# https://askubuntu.com/a/534711
function mount-cdrom --description 'mount /dev/cdrom to /media/$USER/cdrom/'

    if not test -d "/media/$USER/cdrom"
        doas mkdir --verbose --parents -- "/media/$USER/cdrom" || return
    end

    doas mount --read-only -t auto /dev/cdrom -- "/media/$USER/cdrom/"
end
