
function cpd --wraps cp
    cp $argv && cd $argv[-1]
end

