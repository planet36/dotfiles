# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

##### TODO: either make this distro agnostic or remove it
# list old linux kernels
function lsoldkernels
{
    local KERNEL_RELEASE
    KERNEL_RELEASE=$(uname -r | sed -r 's/-\w+$//') || return
    #KERNEL_RELEASE="${KERNEL_RELEASE%-generic}"

    dpkg --get-selections 'linux-*' |
    grep --perl-regexp -- '^linux-(headers|image|image-extra)-[0-9\.\-]+' |
    grep -v -- 'deinstall$' |
    cut --fields 1 |
    grep -v -- "${KERNEL_RELEASE}"

    #dpkg --get-selections 'linux-*' | grep --perl-regexp '^linux-(headers|image|image-extra)-[0-9\.\-]+(-generic)?\s+install$' | cut --fields 1

    #sudo apt-get purge $(dpkg --get-selections 'linux-*' | grep --perl-regexp '^linux-(headers|image|image-extra)-[0-9\.\-]+')
}
