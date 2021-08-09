# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

##### XXX: "add fish syntax highlighting"
# https://github.com/vim/vim/issues/820

#ulimit -c unlimited

# {{{ login shell

if status is-login

# {{{ prepend user path

# Move ~/.local/bin to the front of PATH.
fish_add_path --move "$HOME"/.local/bin

# https://gcc.gnu.org/onlinedocs/gcc/Environment-Variables.html
#if not contains "$HOME"/.local/lib $LIBRARY_PATH
#    set --export --prepend LIBRARY_PATH "$HOME"/.local/lib:
#end

# }}}

# {{{ my location

#set MY_LOCATION (curl -s -f 'http://ip-api.com/json/?fields=lat,lon')
set MY_LOCATION (curl -s -f 'http://ip-api.com/line/?fields=lat,lon')
#set --export LAT (echo "$MY_LOCATION" | jq -r '.lat')
#set --export LON (echo "$MY_LOCATION" | jq -r '.lon')
set --export LAT $MY_LOCATION[1]
set --export LON $MY_LOCATION[2]
set --erase MY_LOCATION

# }}}

# {{{ XDG vars

function setup_xdg_vars

    # https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html

    if not set --query XDG_CACHE_HOME  ; set --export --global XDG_CACHE_HOME  "$HOME"/.cache                ; end
    if not set --query XDG_CONFIG_DIRS ; set --export --global XDG_CONFIG_DIRS /etc/xdg                      ; end
    if not set --query XDG_CONFIG_HOME ; set --export --global XDG_CONFIG_HOME "$HOME"/.config               ; end
    if not set --query XDG_DATA_DIRS   ; set --export --global XDG_DATA_DIRS   /usr/local/share/:/usr/share/ ; end
    if not set --query XDG_DATA_HOME   ; set --export --global XDG_DATA_HOME   "$HOME"/.local/share          ; end

    mkdir --verbose --parents -- "$XDG_CACHE_HOME"
    mkdir --verbose --parents -- "$XDG_CONFIG_HOME"
    mkdir --verbose --parents -- "$XDG_DATA_HOME"
end

setup_xdg_vars

# }}}

# {{{ env vars

set --export ACKRC "$XDG_CONFIG_HOME"/ack/ackrc

set --export CC gcc
set --export CXX g++

if command --quiet nvim
    set --export EDITOR nvim
    set --export VISUAL nvim
else if command --quiet vim
    set --export EDITOR vim
    set --export VISUAL vim
else
    echo "Warning: No editor found.  Install nvim or vim."
end

set --export DIFFPROG "$VISUAL -d"

set --export DOTNET_CLI_TELEMETRY_OPTOUT 1

set --export FZF_DEFAULT_OPTS '--multi --inline-info --ansi --tabstop=4 --color=bg+:25,fg+:220,gutter:-1 --preview-window=right'

if command --quiet highlight
    #FZF_DEFAULT_OPTS+=' --preview "highlight -- {} | head -n ${FZF_PREVIEW_LINES}"'
    # --line-range option added in highlight 3.43 (2018-04-30)
    # shellcheck disable=SC2016
    set --append FZF_DEFAULT_OPTS '--preview "highlight --line-range=1-$FZF_PREVIEW_LINES -- {}"'
else
    # shellcheck disable=SC2016
    set --append FZF_DEFAULT_OPTS '--preview "head -n $FZF_PREVIEW_LINES -- {}"'
end

set --export GIT_EDITOR "$EDITOR"

set --export GNUPGHOME "$XDG_DATA_HOME"/gnupg

set --export HIGHLIGHT_OPTIONS '--force -t 4 --out-format=ansi'

set --export IPYTHONDIR "$XDG_DATA_HOME"/ipython

#set --export LANG en_US.UTF-8
#set --export LC_ALL en_US.UTF-8

#set --export LESS '--RAW-CONTROL-CHARS --quit-if-one-screen --no-init'
set --export LESS '--RAW-CONTROL-CHARS --no-init'
set --export LESSHISTFILE /dev/null

# Inhibit these dbind warnings: Couldn't register with accessibility bus
# https://wiki.archlinux.de/title/GNOME#Tipps_und_Tricks
# https://askubuntu.com/a/318997
# This affects meld.
set --export NO_AT_BRIDGE 1

# https://www.reddit.com/r/linux/comments/12wxsl/whats_in_your_bashrc/c6z0y5g/
#set --export JAVA_HOME (readlink -f -- (which javac) | sed 's|bin/javac||')

set --export PARALLEL_HOME "$XDG_CONFIG_HOME"/parallel

set --export PASSWORD_STORE_DIR "$XDG_DATA_HOME"/pass

set --export PREFIX "$HOME"/.local

#set --export PS_FORMAT pid,nice,pri,user,stime,etime,sz,pmem,pcpu,command
set --export PS_FORMAT pid,nice,pri,user,stime,etime,cputimes,%cpu,%mem,rss,args

set --export PYLINTHOME "$XDG_CACHE_HOME"/pylint.d

# https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPATH
set --export PYTHONPATH "$HOME"/.local/lib/python

# https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPYCACHEPREFIX
set --export PYTHONPYCACHEPREFIX "$XDG_CACHE_HOME"/__pycache__

set --export RIPGREP_CONFIG_PATH "$XDG_CONFIG_HOME"/ripgrep/ripgreprc

set --export SCREENRC "$XDG_CONFIG_HOME"/screen/screenrc

# /usr/bin/time format similar to bash's time
set --export TIME "real\t%E\nuser\t%U\nsys\t%S\n"

set --export TRASH_DIR "$XDG_DATA_HOME"/Trash
if not test -d "$TRASH_DIR"
    mkdir --verbose --mode=0700 -- "$TRASH_DIR"
end

set --export TZ ':America/New_York'

#set --export VCS_REPOS_MATCH '( -type d -and ( -name CVS -or -name .svn -or -name .git -or -name .hg ) )'
#set --export VCS_REPOS_PRUNE "( $VCS_REPOS_MATCH -prune , -not $VCS_REPOS_MATCH )"

if not test -d "$XDG_CACHE_HOME"/xorg
    mkdir --verbose --parents -- "$XDG_CACHE_HOME"/xorg
end
set --export XAUTHORITY "$XDG_CACHE_HOME"/xorg/Xauthority

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

# 0 = black
# 1 = red
# 2 = green
# 3 = yellow
# 4 = blue
# 5 = magenta
# 6 = cyan
# 7 = white

set --export LESS_TERMCAP_mb (tput bold; tput setaf 6) # turn on blinking
set --export LESS_TERMCAP_md (tput bold; tput setaf 2) # turn on bold (extra bright) mode
set --export LESS_TERMCAP_mh (tput dim) # turn on half-bright mode
set --export LESS_TERMCAP_mr (tput rev) # turn on reverse video mode
set --export LESS_TERMCAP_so (tput bold; tput rev; tput setaf 4) # begin standout mode
set --export LESS_TERMCAP_ZN (tput ssubm) # Enter subscript mode
set --export LESS_TERMCAP_ZO (tput ssupm) # Enter superscript mode
set --export LESS_TERMCAP_us (tput smul; tput bold; tput setaf 3) # begin underline mode
set --export LESS_TERMCAP_me (tput sgr0) # turn off all attributes
set --export LESS_TERMCAP_se (tput rmso; tput sgr0) # exit standout mode
set --export LESS_TERMCAP_ZV (tput rsubm) # End subscript mode
set --export LESS_TERMCAP_ZW (tput rsupm) # End superscript mode
set --export LESS_TERMCAP_ue (tput rmul; tput sgr0) # exit underline mode

# For Konsole and Gnome-terminal
#set --export GROFF_NO_SGR 1

# https://stackoverflow.com/a/19871578
set --export MANPAGER 'less -s -M +Gg'

# }}}

# }}}

# {{{ interactive shell

if status is-interactive

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

if string match --regex --quiet '/dev/tty[0-9]+' (tty)

    # {{{ turn on numlock
    setleds -D +num
    # }}}

    # {{{ set console font
    if command --quiet setfont
        # To print the character set of the active font: showconsolefont

        # Fonts are in:
        # /usr/share/kbd/consolefonts (arch)
        # /lib/kbd/consolefonts (fedora)

        setfont Lat2-Terminus16
    end
    # }}}
end

# {{{ Start X at login

# https://wiki.archlinux.org/index.php/Fish#Start_X_at_login
#if status is-login
    if test -z "$DISPLAY" -a "$XDG_VTNR" = 1
        #exec startx -- -keeptty
        :
    end
#end

# }}}

end # status is-interactive

# }}}

end # status is-login

# }}}

# {{{ compile options
# XXX: These variables must be set in every shell because fish can't
# reconstruct lists from variables it imports.
# If these were set in the is-login or is-interactive blocks, then when used in
# a nested shell, they would be expanded to a single string.

# XXX: The universal variables are thus so that when they are expanded unquoted
# in interactive mode, they will be split about spaces like in bash.
# XXX: Universal variables will be removed from fish in the future.
# https://github.com/fish-shell/fish-shell/issues/7379

# Too many benign warnings:
# -Wpadded
# -Wfloat-equal
set GCC_COMMON_OPTIONS -O2 -pipe -Wall -Wextra -Wpedantic -Wfatal-errors -Wcast-align -Wcast-qual -Wduplicated-branches -Wduplicated-cond -Wformat-overflow=2 -Wformat=2 -Wlogical-op -Wmissing-include-dirs -Wno-format-nonliteral -Wno-unused-function -Wshadow -Wswitch-default -Wswitch-enum -Wuninitialized -Wunsafe-loop-optimizations
# https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
set --append GCC_COMMON_OPTIONS -D__STDC_WANT_IEC_60559_BFP_EXT__ -D__STDC_WANT_IEC_60559_FUNCS_EXT__ -D__STDC_WANT_IEC_60559_TYPES_EXT__ -D__STDC_WANT_IEC_60559_EXT__
set --append GCC_COMMON_OPTIONS -D_GNU_SOURCE -D_FORTIFY_SOURCE=2
# https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html
set --append GCC_COMMON_OPTIONS -fstack-protector -fstack-clash-protection

# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
#OPTIMIZE_OPTIONS '-O3 -march=native -fassociative-math -fno-math-errno -freciprocal-math -fno-signed-zeros -fno-trapping-math'
# Using -fsigned-zeros disables associative-math
#OPTIMIZE_OPTIONS '-O3 -march=native -fno-math-errno -freciprocal-math -fno-trapping-math'
set --export OPTIMIZE_OPTIONS -O3 -flto -march=native

set --export DEBUG_OPTIONS -Og -g3
# https://www.gnu.org/software/libc/manual/html_node/Consistency-Checking.html
set --append DEBUG_OPTIONS -UNDEBUG
# https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html
set --append DEBUG_OPTIONS -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG -D_GLIBCXX_SANITIZE_VECTOR

set --export PERF_TEST_OPTIONS $OPTIMIZE_OPTIONS -fno-allocation-dce -fno-dce -fno-dse -fno-gcse -fno-split-paths -fno-tree-builtin-call-dce -fno-tree-copy-prop -fno-tree-dce -fno-tree-dse -fno-tree-fre -fno-tree-partial-pre -fno-tree-pre

set --export PROFILE_OPTIONS $PERF_TEST_OPTIONS -pg

# https://gcc.gnu.org/onlinedocs/cpp/Invocation.html
set --export CPPFLAGS -iquote "$HOME"/.local/include

set --export CFLAGS $GCC_COMMON_OPTIONS -std=c2x
set --export CXXFLAGS $GCC_COMMON_OPTIONS -std=c++23 -fchar8_t -fdiagnostics-show-template-tree -Wctor-dtor-privacy -Wextra-semi -Wmismatched-tags -Wmultiple-inheritance -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-tags -Wsign-promo -Wstrict-null-sentinel -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wuseless-cast -Wzero-as-null-pointer-constant

# }}}

# {{{ interactive shell

if status is-interactive

# {{{ prevent st unknown escape sequence

# https://github.com/fish-shell/fish-shell/issues/3425
if string match --quiet "st-*" "$TERM"
    set --erase VTE_VERSION
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
