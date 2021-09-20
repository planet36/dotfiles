# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash disable=SC1090

ulimit -c unlimited

if [[ -f "$XDG_CONFIG_HOME"/bash/envvars.bash ]]
then
    source "$XDG_CONFIG_HOME"/bash/envvars.bash
fi

# {{{ interactive shell

# https://unix.stackexchange.com/a/26782
#if [[ $- == *i* ]]
#then

    # https://wiki.archlinux.org/index.php/Activating_numlock_on_bootup#Extending_getty.40.service
    # https://www.linuxsecrets.com/archlinux-wiki/wiki.archlinux.org/index.php/Activating_Numlock_on_Bootup.html
    # https://forums.gentoo.org/viewtopic-t-1055442-view-previous.html

    # https://mywiki.wooledge.org/BashFAQ/100#Checking_for_substrings
    #TTY_REGEX='^/dev/tty[0-9]+$'
    #if [[ "$(tty)" =~ $TTY_REGEX ]]
    #then
    #    # {{{ turn on numlock
    #    setleds -D +num
    #    # }}}
    #fi

    # {{{ Start X at login
    # https://wiki.archlinux.org/index.php/Xinit#Autostart_X_at_login
    #if command -v systemctl > /dev/null
    #then
    #    #if systemctl -q is-active graphical.target && [[ ! ${DISPLAY} && ${XDG_VTNR} -eq 1 ]]
    #    if [ -z "${DISPLAY}" ] && [ "${XDG_VTNR}" -eq 1 ]
    #    then
    #        #exec startx
    #        :
    #    fi
    #fi
    # }}}

#fi # interactive shell

# }}}

if [[ -r ~/.bashrc ]]
then
    source ~/.bashrc
fi
