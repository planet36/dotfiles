# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function clean
{
    find "${@}" \
        \( -type f -or -type l \) \
        \( -name '*~' -or -name '.*~' -o -name core -o -regex '.*/core\.[0-9]+' \) \
        -print0 | xargs --null --no-run-if-empty 'rm' --verbose
}
