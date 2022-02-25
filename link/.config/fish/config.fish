# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# vim: set foldmethod=marker foldlevel=0:

##### XXX: "add fish syntax highlighting"
# https://github.com/vim/vim/issues/820

#ulimit -c unlimited

# {{{ login shell

if status is-login

# {{{ prepend user path
# https://gcc.gnu.org/onlinedocs/gcc/Environment-Variables.html
#if not contains "$HOME"/.local/lib $LIBRARY_PATH
#    set --export --path --prepend LIBRARY_PATH "$HOME"/.local/lib
#end
# }}}

# {{{ interactive shell

#if status is-interactive

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

#if string match --regex --quiet '/dev/tty[0-9]+' (tty)
#
#    # {{{ turn on numlock
#    setleds -D +num
#    # }}}
#
#end

# {{{ Start X at login

# https://wiki.archlinux.org/index.php/Fish#Start_X_at_login
#if status is-login
#    if test -z "$DISPLAY" -a "$XDG_VTNR" = 1
#        #exec startx -- -keeptty
#        :
#    end
#end

# }}}

#end # status is-interactive

# }}}

end # status is-login

# }}}

if test -f (status dirname)/envvars.fish
    source (status dirname)/envvars.fish
end

# {{{ interactive shell

if status is-interactive

# {{{ prevent st unknown escape sequence

# https://github.com/fish-shell/fish-shell/issues/3425
if string match --quiet "st-*" "$TERM"
    set --erase VTE_VERSION
    # fixed by https://github.com/fish-shell/fish-shell/commit/6606dfbeb5e65e1f9d1b900248e02dea6690d48c
    bind \e\[P delete-char
end

# }}}

# {{{ ls colors

# convert from sh to fish syntax
#eval (dircolors | sed -r -e 's/^([^=]+?)=(.*)/set \1 \2/' -e 's/^export .+//')
#dircolors | sed -r -e 's/^([^=]+)=(.*)/set --export \1 \2/' -e 's/^export .+//' | source

#if test $TERM = linux
#    # change dir color
#    set --append --export --path LS_COLORS 'di=0;33'
#end

# }}}

# {{{ env_parallel

if command --quiet env_parallel
    source (which env_parallel.fish)
end

# }}}

# {{{ z

set Z_CMD "j"
#set ZO_CMD "$Z_CMD"o

# }}}

# {{{ zoxide

#if command --quiet zoxide
#    #https://github.com/ajeetdsouza/zoxide#step-3-add-zoxide-to-your-shell
#    zoxide init fish | source
#end

# }}}

# {{{ command not found function

# https://github.com/fish-shell/fish-shell/issues/7841
function fish_command_not_found
    __fish_default_command_not_found_handler $argv
end

# }}}

# {{{ source other config files

if test -f (status dirname)/private.fish
    source (status dirname)/private.fish
end

if test -f (status dirname)/abbrs.fish
    source (status dirname)/abbrs.fish
end

if test -f (status dirname)/aliases.fish
    source (status dirname)/aliases.fish
end

# }}}

end # status is-interactive

# }}}
