# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function sc --wraps scrypt --description 'wrapper for scrypt'

    for INFILE in $argv

        if not test -f "$INFILE"
            echo "Error: No such file: $INFILE" 1>&2
            return 1
        end

        if string match --quiet --regex '\.sc$' "$INFILE"
            set ENC_OR_DEC dec
            # Remove ".sc" extension
            set OUTFILE $(string sub --length $(math $(string length "$INFILE") - $(string length ".sc")) "$INFILE") || return
        else
            set ENC_OR_DEC enc
            # Append ".sc" extension
            set OUTFILE "$INFILE".sc
        end

        if test -e "$OUTFILE"
            echo "Error: File already exists: $OUTFILE" 1>&2
            return 1
        end

        #echo "# $INFILE => $OUTFILE"
        printf '# %s => %s\n' "$INFILE" "$OUTFILE"

        scrypt "$ENC_OR_DEC" "$INFILE" "$OUTFILE" || return
    end
end
