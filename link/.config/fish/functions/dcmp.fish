# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# XXX: string replace was fixed on 2020-09-20 -- 3.2.0 should have it
# https://github.com/fish-shell/fish-shell/issues/7343
# https://github.com/fish-shell/fish-shell/commit/7ec57f2c50809000653c2ff51cc481f109e6fd7c

function dcmp --description 'directory comparison' --argument-names A B

    if test (count $argv) -ne 2
        echo 'Usage: '(status function)' DIR1 DIR2' 1>&2
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

    #set A (echo "$A" | sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||' --expression 's|^-|./-|')
    set A (echo "$A" | sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||')

    #set B (echo "$B" | sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||' --expression 's|^-|./-|')
    set B (echo "$B" | sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||')

    # escape non-word chars
    set A_escaped (string escape --style=regex "$A")
    set B_escaped (string escape --style=regex "$B")


    ##### XXX: fixed in fish 3.2
    #diff --brief --recursive \
    #--exclude={.bzr,CVS,.git,.hg,.svn} \
    #-- "$A" "$B" |
    #string replace --regex -- '^Files '"$A_escaped"'(/.+?) and '"$B_escaped"'\1 differ$'  '! {'"$A_escaped"','"$B_escaped"'}$1' |
    #string replace --regex -- '^Only in '"$A_escaped"'(/.+?)?: ([^/]+)$' '- '"$A"'$1/$2' |
    #string replace --regex -- '^Only in '"$B_escaped"'(/.+?)?: ([^/]+)$' '+ '"$B"'$1/$2'


    # PCRE2 prints an error when I try to substitute a back reference to an optional capture group that was not matched.
    # Instead, make an optional non-capturing group and then capture it.

    ##### XXX: use this before fish 3.2
    diff --brief --recursive \
    --exclude={.bzr,CVS,.git,.hg,.svn} \
    -- "$A" "$B" |
    string replace --regex -- '^Files '"$A_escaped"'(/.+?) and '"$B_escaped"'\1 differ$'  '! {'"$A_escaped"','"$B_escaped"'}$1' |
    string replace --regex -- '^Only in '"$A_escaped"'((?:/.+?)?): ([^/]+)$' '- '"$A"'$1/$2' |
    string replace --regex -- '^Only in '"$B_escaped"'((?:/.+?)?): ([^/]+)$' '+ '"$B"'$1/$2'

end
