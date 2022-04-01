# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function t --description 'tar a folder'

    for INDIR in $argv

        if not test -d "$INDIR"
            echo "Error: No such directory: $INDIR" 1>&2
            return 1
        end

        # Remove duplicate leading slashes
        # Remove trailing slashes
        # Prefix leading '-' with './' (is this necessary?)
        #set INDIR $(echo "$INDIR" | sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||' --expression 's|^-|./-|')
        set INDIR $(echo "$INDIR" | sed --regexp-extended --expression 's|^/{2,}|/|' --expression 's|/+$||')

        set OUTFILE $(basename -- "$INDIR").tar

        if test -e "$OUTFILE"
            echo "Error: File already exists: $OUTFILE" 1>&2
            return 1
        end

        if test -L "$INDIR"
            # Get the link target.
            set INDIR $(realpath -- "$INDIR")
        end

        #echo "# $INDIR => $OUTFILE"
        printf '# %s => %s\n' "$INDIR" "$OUTFILE"

        if string match --quiet -- '*/*' "$INDIR"

            set DIRNAME $(dirname -- "$INDIR")
            set BASENAME $(basename -- "$INDIR")

            tar --create --file="$OUTFILE" --directory "$DIRNAME" -- "$BASENAME" || return
        else
            tar --create --file="$OUTFILE" -- "$INDIR" || return
        end
    end
end
