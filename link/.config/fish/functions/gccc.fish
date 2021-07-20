# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function gccc --wraps gcc --description 'gcc wrapper that uses $CPPFLAGS and $CFLAGS'
    command gcc $CPPFLAGS $CFLAGS $argv
end
