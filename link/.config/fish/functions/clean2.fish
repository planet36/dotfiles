
function clean2 --description 'remove files ending with "~", only beneath the current directory'
    clean $argv -mindepth 2
end

