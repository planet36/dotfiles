# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function clean
{
    find "${@}" \( -type f -or -type l \) \( -name '*~' -or -name '.*~' \) -print0 | xargs --null --no-run-if-empty 'rm' --verbose
}
