
# https://askubuntu.com/a/534711
function mount-cdrom --description 'mount /dev/cdrom to /media/$USER/cdrom/'

    if not test -d "/media/$USER/cdrom"
        sudo mkdir --verbose --parents -- "/media/$USER/cdrom" || return
    end

    sudo mount --read-only -t auto /dev/cdrom -- "/media/$USER/cdrom/"
end

