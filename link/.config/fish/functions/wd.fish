# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function wd --description 'Print $PWD with $HOME replaced by ~'
    string replace -r '^'"$HOME" '~' "$PWD"
end
