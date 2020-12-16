
function wd --description 'Print $PWD with $HOME replaced by ~'
    string replace -r '^'"$HOME" '~' "$PWD"
end

