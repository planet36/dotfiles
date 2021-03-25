# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function get-code --wraps wget
    command wget $argv "$CODE_ARCHIVE_URL"/code-latest.tar.xz
end
