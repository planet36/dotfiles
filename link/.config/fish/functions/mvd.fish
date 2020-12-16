
function mvd --wraps mv
    mv $argv && cd $argv[-1]
end

