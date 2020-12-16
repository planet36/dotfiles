
function is_int
    # https://stackoverflow.com/a/21505954
    set INT_REGEX '^(?:[+-]?[1-9][0-9]*|0)$'
    string match --regex --quiet $INT_REGEX -- $argv[1]
end

