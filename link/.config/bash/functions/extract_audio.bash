# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function extract_audio
{
    local INFILE

    for INFILE
    do
        if [[ ! -f "${INFILE}" ]]
        then
            printf 'Error: %q is not a file.\n' "${INFILE}" 1>&2
            return 1
        fi

        local AUDIO_FORMAT
        AUDIO_FORMAT="$(ffmpeg -i "${INFILE}" 2>&1 | sed -r -n -e 's/^.*Audio: ([^,]+)?.*$/\1/p')" || return

        local INFILE_BASE="${INFILE%.*}"

        local OUTFILE="${INFILE_BASE}.${AUDIO_FORMAT}"

        # -vn (output) Disable video recording.
        ffmpeg -i "${INFILE}" -vn -acodec copy "${OUTFILE}" || return

        touch --reference "${INFILE}" -- "${OUTFILE}" || return
    done
}

