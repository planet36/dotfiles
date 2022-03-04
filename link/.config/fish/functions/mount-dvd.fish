# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# https://askubuntu.com/a/534711
function mount-dvd --description 'mount /dev/dvd to /media/$USER/dvd/'

    if not test -d "/media/$USER/dvd"
        doas mkdir --verbose --parents -- "/media/$USER/dvd" || return
    end

    doas mount --read-only -t auto /dev/dvd -- "/media/$USER/dvd/"
end
