# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function gpp
{
    # shellcheck disable=SC2086
    command g++ $CPPFLAGS $CXXFLAGS "${@}" -lfmt
}
