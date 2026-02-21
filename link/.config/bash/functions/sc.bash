# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# wrapper for scrypt
function sc
{
    local -r SCRYPT_EXT='scrypt'
    local -r VERBOSE=false

    local INFILE

    for INFILE
    do
        if [[ ! -f "${INFILE}" ]]
        then
            printf 'Error: %q is not a file.\n' "${INFILE}" 1>&2
            return 1
        fi

        local INFILE_BASE="${INFILE%.*}"
        local INFILE_EXT="${INFILE##*.}"
        local ENC_OR_DEC
        local OUTFILE

        if [[ "${INFILE_EXT}" == "${SCRYPT_EXT}" ]]
        then
            # decrypt
            ENC_OR_DEC='dec'
            OUTFILE="${INFILE_BASE}"
        else
            # encrypt
            ENC_OR_DEC='enc'
            OUTFILE="${INFILE}.${SCRYPT_EXT}"
        fi

        if ${VERBOSE}
        then
            printf "# INFILE=%q\n" "${INFILE}"
            printf "# INFILE_BASE=%q\n" "${INFILE_BASE}"
            printf "# INFILE_EXT=%q\n" "${INFILE_EXT}"
            printf "# ENC_OR_DEC=%q\n" "${ENC_OR_DEC}"
            printf "# OUTFILE=%q\n" "${OUTFILE}"
        fi

        if [[ -e "${OUTFILE}" ]]
        then
            printf 'Warning: %q already exists.\n' "${OUTFILE}" 1>&2
            continue
        fi

        nice -n 19 scrypt "${ENC_OR_DEC}" -- "${INFILE}" "${OUTFILE}" || return

        touch --reference "${INFILE}" -- "${OUTFILE}" || return
    done
}
