
# XXX: radar.weather.gov was redesigned and launched on 2020-12-17
# These URLs are gone.
function radar --description 'download and display a radar animation'

    cd -- "$XDG_CACHE_HOME" || return

    set URL 'https://radar.weather.gov/lite/N0R/MLB_loop.gif'

    set OUTFILE "$XDG_CACHE_HOME"/(basename -- "$URL") || return

    if not test -f "$OUTFILE"
        curl --silent --output "$OUTFILE"                        -- "$URL" || return
    else
        curl --silent --output "$OUTFILE" --time-cond "$OUTFILE" -- "$URL" || return
    end

    sxiv -a -- "$OUTFILE"

    cd -
end

