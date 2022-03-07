# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function dots
    yes '. ' | head -n 1000 | tr -d '\n' | fold ; printf '\n'
end
