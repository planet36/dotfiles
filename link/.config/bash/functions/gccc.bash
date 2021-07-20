# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function gccc
{
    # shellcheck disable=SC2086
    command gcc $CPPFLAGS $CFLAGS "${@}"
}
