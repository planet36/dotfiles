
function get-code --wraps wget
    command wget $argv "$CODE_ARCHIVE_URL"/code-latest.tar.xz
end

