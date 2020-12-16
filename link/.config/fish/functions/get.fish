
function get

    if test (count $argv) -eq 0
        echo 'Error: Must give at least one folder name' 1>&2
        echo 'Usage: '(status function)' DIR...' 1>&2
        return 1
    end

    for DIR in $argv
        set SRC "$MY_WEBSITE:$DIR/"
        set DST "$HOME/$DIR"
        #rsync $RSYNC_ARGS -e ssh "$SRC" "$DST"
        rsync (string split -- ' ' $RSYNC_ARGS) -e ssh "$SRC" "$DST"
        echo
    end
end

