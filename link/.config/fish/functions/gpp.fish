# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function gpp --wraps g++ --description 'g++ wrapper that uses $CPPFLAGS and $CXXFLAGS'
    command g++ $CPPFLAGS $CXXFLAGS $argv
end
