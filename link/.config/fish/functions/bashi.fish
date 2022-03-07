# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function bashi --wraps bash --description 'bash that uses config.bash'
    command bash -i --rcfile "$XDG_CONFIG_HOME"/bash/config.bash $argv
end
