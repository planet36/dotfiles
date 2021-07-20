# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function version
{
    echo

    ls -l /etc/*-release

    echo

    cat /etc/*-release

    echo

    cat <<EOT
kernel name:           $(uname --kernel-name)
network node hostname: $(uname --nodename)
kernel release:        $(uname --kernel-release)
kernel version:        $(uname --kernel-version)
machine hardware name: $(uname --machine)
processor type:        $(uname --processor)
hardware platform:     $(uname --hardware-platform)
operating system:      $(uname --operating-system)
EOT

    echo

    uname --all
}
