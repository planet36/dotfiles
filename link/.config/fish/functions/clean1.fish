# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function clean1 --description 'remove files ending with "~", only in the current directory'
    clean $argv -maxdepth 1
end
