# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash disable=SC1090,SC1091

# https://unix.stackexchange.com/a/26782
# If not running interactively, don't do anything
[[ $- != *i* ]] && return

# {{{ Start X at login
# https://wiki.archlinux.org/index.php/Xinit#Autostart_X_at_login
if command -v systemctl > /dev/null
then
    #if systemctl -q is-active graphical.target && [[ ! ${DISPLAY} && ${XDG_VTNR} -eq 1 ]]
    if [ -z "${DISPLAY}" ] && [ "${XDG_VTNR}" -eq 1 ]
    then
        #exec startx
        :
    fi
fi
# }}}

# {{{ bash history

# https://www.gnu.org/software/bash/manual/html_node/Bash-Variables.html#index-HISTCONTROL
HISTCONTROL=ignoreboth:erasedups

if [[ ! -d "$XDG_DATA_HOME"/bash ]]
then
    mkdir --verbose --parents -- "$XDG_DATA_HOME"/bash
fi
HISTFILE="$XDG_DATA_HOME"/bash/history
HISTFILESIZE=9999
HISTSIZE=9999
HISTTIMEFORMAT='%F %T %z : '

# }}}

# {{{ set readline key bindings

# https://www.gnu.org/software/bash/manual/html_node/Readline-Init-File-Syntax.html
bind 'set bell-style none'
bind 'set colored-completion-prefix on'
bind 'set colored-stats on'
bind 'set completion-ignore-case on'
bind 'set completion-map-case on'
# Fix Del key in st
# https://git.suckless.org/st/file/FAQ.html
bind 'set enable-keypad on'
bind 'set mark-symlinked-directories on'
bind 'set show-all-if-ambiguous on'
bind 'set skip-completed-text on'

# https://unix.stackexchange.com/a/147572
bind Space:magic-space

# }}}

# {{{ set shell options

# https://www.gnu.org/software/bash/manual/html_node/The-Shopt-Builtin.html
# https://wiki.bash-hackers.org/internals/shell_options
# https://unix.stackexchange.com/a/353407

shopt -s autocd
# When changing directory small typos can be ignored by bash
# for example, cd /vr/lgo/apaache would find /var/log/apache
shopt -s cdspell
shopt -s cmdhist
((BASH_VERSINFO[0] >= 4 && BASH_VERSINFO[1] >= 3)) && shopt -s direxpand
((BASH_VERSINFO[0] >= 4)) && shopt -s dirspell
shopt -s dotglob
#shopt -s extglob
#shopt -s failglob
shopt -s histappend
shopt -s hostcomplete
shopt -s lithist
shopt -s nocaseglob

# https://www.gnu.org/software/bash/manual/html_node/Bash-Variables.html#index-GLOBIGNORE
GLOBIGNORE=.:..

# }}}

# {{{ change terminal line settings

# disable sending of start/stop characters
#stty -ixoff

# disable XON/XOFF flow control
#stty -ixon

# https://stackoverflow.com/a/19248775
# disable control backslash (^\) as quit
#stty quit undef

# }}}

# https://wiki.archlinux.org/index.php/Activating_numlock_on_bootup#Extending_getty.40.service
# https://www.linuxsecrets.com/archlinux-wiki/wiki.archlinux.org/index.php/Activating_Numlock_on_Bootup.html
# https://forums.gentoo.org/viewtopic-t-1055442-view-previous.html

# https://mywiki.wooledge.org/BashFAQ/100#Checking_for_substrings
TTY_REGEX='^/dev/tty[0-9]+$'
if [[ "$(tty)" =~ $TTY_REGEX ]]
then
    # {{{ turn on numlock
    setleds -D +num
    # }}}

    # {{{ set console font
    if command -v setfont > /dev/null
    then
        # To print the character set of the active font: showconsolefont

        # Fonts are in:
        # /usr/share/kbd/consolefonts (arch)
        # /lib/kbd/consolefonts (fedora)

        setfont Lat2-Terminus16
    fi
    # }}}
fi

# }}}

#[[ -f /etc/profile.d/grc.bashrc ]] && source /etc/profile.d/grc.bashrc

# {{{ ls colors

#eval $(dircolors -b)
#source <(dircolors -b)

#if [[ "${TERM}" == linux ]]
#then
#    # change dir color
#    export LS_COLORS="${LS_COLORS}:di=0;33"
#fi

# }}}

# {{{ pager colors

# https://unix.stackexchange.com/a/147

# man 5 terminfo
# http://man7.org/linux/man-pages/man5/terminfo.5.html

# man terminfo | grep -A 1 -E '\<(mb|md|me|so|se|us|ue|mr|mh|ZN|ZV|ZO|ZW)\>'

# enter_blink_mode            blink     mb     turn on blinking
# enter_bold_mode             bold      md     turn on bold (extra bright) mode
# enter_dim_mode              dim       mh     turn on half-bright mode
# enter_reverse_mode          rev       mr     turn on reverse video mode
# enter_standout_mode         smso      so     begin standout mode
# enter_subscript_mode        ssubm     ZN     Enter subscript mode
# enter_superscript_mode      ssupm     ZO     Enter superscript mode
# enter_underline_mode        smul      us     begin underline mode
# exit_attribute_mode         sgr0      me     turn off all attributes
# exit_standout_mode          rmso      se     exit standout mode
# exit_subscript_mode         rsubm     ZV     End subscript mode
# exit_superscript_mode       rsupm     ZW     End superscript mode
# exit_underline_mode         rmul      ue     exit underline mode

export LESS_TERMCAP_mb
export LESS_TERMCAP_md
export LESS_TERMCAP_mh
export LESS_TERMCAP_mr
export LESS_TERMCAP_so
export LESS_TERMCAP_ZN
export LESS_TERMCAP_ZO
export LESS_TERMCAP_us
export LESS_TERMCAP_me
export LESS_TERMCAP_se
export LESS_TERMCAP_ZV
export LESS_TERMCAP_ZW
export LESS_TERMCAP_ue

# 0 = black
# 1 = red
# 2 = green
# 3 = yellow
# 4 = blue
# 5 = magenta
# 6 = cyan
# 7 = white

LESS_TERMCAP_mb=$(tput bold; tput setaf 6) # turn on blinking
LESS_TERMCAP_md=$(tput bold; tput setaf 2) # turn on bold (extra bright) mode
LESS_TERMCAP_mh=$(tput dim) # turn on half-bright mode
LESS_TERMCAP_mr=$(tput rev) # turn on reverse video mode
LESS_TERMCAP_so=$(tput bold; tput rev; tput setaf 4) # begin standout mode
LESS_TERMCAP_ZN=$(tput ssubm) # Enter subscript mode
LESS_TERMCAP_ZO=$(tput ssupm) # Enter superscript mode
LESS_TERMCAP_us=$(tput smul; tput bold; tput setaf 3) # begin underline mode
LESS_TERMCAP_me=$(tput sgr0) # turn off all attributes
LESS_TERMCAP_se=$(tput rmso; tput sgr0) # exit standout mode
LESS_TERMCAP_ZV=$(tput rsubm) # End subscript mode
LESS_TERMCAP_ZW=$(tput rsupm) # End superscript mode
LESS_TERMCAP_ue=$(tput rmul; tput sgr0) # exit underline mode

# For Konsole and Gnome-terminal
#export GROFF_NO_SGR=1

# https://stackoverflow.com/a/19871578
export MANPAGER='less -s -M +Gg'

# }}}

# {{{ env_parallel

[[ -f /usr/bin/env_parallel.bash ]] && source /usr/bin/env_parallel.bash

# }}}

# {{{ git completion

if [[ -f /usr/share/bash-completion/completions/git ]]
then
    source /usr/share/bash-completion/completions/git

elif [[ -f /etc/bash_completion.d/git ]]
then
    source /etc/bash_completion.d/git

elif [[ -f /usr/share/git/completion/git-completion.bash ]]
then
    source /usr/share/git/completion/git-completion.bash
fi

# }}}

# {{{ source other config files

# https://wiki.archlinux.org/index.php/Termite#Ctrl+Shift+t
# https://github.com/gnunn1/tilix/wiki/VTE-Configuration-Issue
#[[ -f /etc/profile.d/vte.sh ]] && source /etc/profile.d/vte.sh

if [[ -d "$XDG_CONFIG_HOME"/bash ]]
then
    for f in "$XDG_CONFIG_HOME"/bash/*.bash
    do
        if [[ -r "$f" ]]
        then
            source "$f"
        fi
    done
    unset f
fi

# }}}

# vim: set foldmethod=marker foldlevel=0:
