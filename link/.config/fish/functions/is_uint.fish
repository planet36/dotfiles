
function is_uint
    # https://stackoverflow.com/a/21505954
    set UINT_REGEX '^(?:[1-9][0-9]*|0)$'
    string match --regex --quiet $UINT_REGEX -- $argv[1]
end

