# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash disable=SC1090,SC1091

# {{{ bash history

# https://www.gnu.org/software/bash/manual/html_node/Bash-Variables.html#index-HISTCONTROL
HISTCONTROL=ignoreboth:erasedups

HISTFILE="$XDG_DATA_HOME"/bash/history
HISTFILESIZE=9999
HISTSIZE=9999
HISTTIMEFORMAT='%F %T %z : '

# }}}

# {{{ readline key bindings

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

# {{{ shell options

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

# {{{ env_parallel

if command -v env_parallel > /dev/null
then
    [[ -f /usr/bin/env_parallel.bash ]] && source /usr/bin/env_parallel.bash
fi

# }}}

# {{{ z

export _Z_CMD=j
export _Z_DATA="${XDG_CACHE_HOME}"/z-data
[[ -r "/usr/share/z/z.sh" ]] && source /usr/share/z/z.sh

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

if [[ -f "$XDG_CONFIG_HOME"/bash/aliases.bash ]]
then
    source "$XDG_CONFIG_HOME"/bash/aliases.bash
fi

if [[ -f "$XDG_CONFIG_HOME"/bash/prompt.bash ]]
then
    source "$XDG_CONFIG_HOME"/bash/prompt.bash
fi

if [[ -d "$XDG_CONFIG_HOME"/bash ]]
then
    for f in "$XDG_CONFIG_HOME"/bash/functions/*.bash
    do
        if [[ -r "$f" ]]
        then
            source "$f"
        fi
    done
    unset f
fi

# }}}
