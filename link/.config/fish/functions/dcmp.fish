# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function dcmp --description 'directory comparison' --argument-names A B

    if test $(count $argv) -ne 2
        echo 'Usage: '$(status function)' DIR1 DIR2' 1>&2
        echo 'Find added/removed/modified files between DIR1 and DIR2.' 1>&2
        return 1
    end

    if not test -d "$A"
        echo "Error: No such directory: $A" 1>&2
        return 1
    end

    if not test -d "$B"
        echo "Error: No such directory: $B" 1>&2
        return 1
    end

    # Remove duplicate leading slashes
    # Remove trailing slashes
    # Prefix leading '-' with './' (is this necessary?)

    #set A $(echo "$A" | sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||' --expression 's|^-|./-|')
    set A $(echo "$A" | sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||')

    #set B $(echo "$B" | sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||' --expression 's|^-|./-|')
    set B $(echo "$B" | sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||')

    # escape non-word chars
    set A_escaped $(string escape --style=regex "$A")
    set B_escaped $(string escape --style=regex "$B")


    command diff --brief --recursive \
    --exclude={.bzr,CVS,.git,.hg,.svn} \
    -- "$A" "$B" |
    string replace --regex -- '^Files '"$A_escaped"'(/.+?) and '"$B_escaped"'\1 differ$'  '! {'"$A_escaped"','"$B_escaped"'}$1' |
    string replace --regex -- '^Only in '"$A_escaped"'(/.+?)?: ([^/]+)$' '- '"$A"'$1/$2' |
    string replace --regex -- '^Only in '"$B_escaped"'(/.+?)?: ([^/]+)$' '+ '"$B"'$1/$2'

end
