# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

##### XXX: "add fish syntax highlighting"
# https://github.com/vim/vim/issues/820

##### TODO: do syntax checking (fish -n config.fish)

##### XXX: this will change in fish 3.2.0
# https://github.com/fish-shell/fish-shell/pull/7265
set fish_greeting

ulimit -c unlimited

# {{{ login shell

if status is-login

# {{{ prepend user path

if test -d "$HOME"/.local/bin && not contains "$HOME"/.local/bin $fish_user_paths
    set --global --prepend fish_user_paths "$HOME"/.local/bin $fish_user_paths
end

# }}}

# {{{ XDG vars

function setup_xdg_vars

    # https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html

    if not set -q XDG_CACHE_HOME  ; set -x -g XDG_CACHE_HOME  "$HOME"/.cache                ; end
    if not set -q XDG_CONFIG_DIRS ; set -x -g XDG_CONFIG_DIRS /etc/xdg                      ; end
    if not set -q XDG_CONFIG_HOME ; set -x -g XDG_CONFIG_HOME "$HOME"/.config               ; end
    if not set -q XDG_DATA_DIRS   ; set -x -g XDG_DATA_DIRS   /usr/local/share/:/usr/share/ ; end
    if not set -q XDG_DATA_HOME   ; set -x -g XDG_DATA_HOME   "$HOME"/.local/share          ; end

    mkdir --verbose --parents -- "$XDG_CACHE_HOME"
    mkdir --verbose --parents -- "$XDG_CONFIG_HOME"
    mkdir --verbose --parents -- "$XDG_DATA_HOME"
end

setup_xdg_vars

# }}}

# {{{ env vars

# {{{ compile options

set -x BC_ENV_ARGS "$XDG_CONFIG_HOME"/bc/config.bc

set -x CC gcc
set -x CXX g++

# Too many benign warnings:
# -Wpadded
# -Wfloat-equal
set -x GCC_COMMON_OPTIONS -pipe -Wall -Wextra -Wpedantic -Wfatal-errors -Wcast-align -Wcast-qual -Wduplicated-branches -Wduplicated-cond -Wformat-overflow=2 -Wformat=2 -Wlogical-op -Wmissing-include-dirs -Wshadow -Wswitch-default -Wswitch-enum -Wuninitialized -Wunsafe-loop-optimizations

# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
#OPTIMIZE_OPTIONS '-O3 -march=native -fassociative-math -fno-math-errno -freciprocal-math -fno-signed-zeros -fno-trapping-math'
# Using -fsigned-zeros disables associative-math
#OPTIMIZE_OPTIONS '-O3 -march=native -fno-math-errno -freciprocal-math -fno-trapping-math'
set -x OPTIMIZE_OPTIONS -O3 -flto -march=native

set -x DEBUG_OPTIONS -Og -ggdb3

set -x PERF_TEST_OPTIONS $OPTIMIZE_OPTIONS -fno-allocation-dce -fno-dce -fno-dse -fno-gcse -fno-split-paths -fno-tree-builtin-call-dce -fno-tree-copy-prop -fno-tree-dce -fno-tree-dse -fno-tree-fre -fno-tree-partial-pre -fno-tree-pre

set -x PROFILE_OPTIONS $PERF_TEST_OPTIONS -pg

set -x EXTRACXXFLAGS -fchar8_t -fcoroutines -fdiagnostics-show-template-tree -Wctor-dtor-privacy -Wextra-semi -Wmismatched-tags -Wmultiple-inheritance -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-tags -Wsign-promo -Wstrict-null-sentinel -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wuseless-cast -Wzero-as-null-pointer-constant

set -x CFLAGS $GCC_COMMON_OPTIONS -std=c2x
set -x CXXFLAGS $GCC_COMMON_OPTIONS -std=c++20 $EXTRACXXFLAGS

# }}}

if command --quiet nvim
    set -x EDITOR nvim
    set -x VISUAL nvim
else if command --quiet vim
    set -x EDITOR vim
    set -x VISUAL vim
end

set -x FZF_DEFAULT_OPTS '--multi --inline-info --ansi --tabstop=4 --color=bg+:25,fg+:220,gutter:-1 --preview-window=right'

if command --quiet highlight
    #FZF_DEFAULT_OPTS+=' --preview "highlight -- {} | head -n ${FZF_PREVIEW_LINES}"'
    # --line-range option added in highlight 3.43 (2018-04-30)
    # shellcheck disable=SC2016
    set --append FZF_DEFAULT_OPTS '--preview "highlight --line-range=1-$FZF_PREVIEW_LINES -- {}"'
else
    # shellcheck disable=SC2016
    set --append FZF_DEFAULT_OPTS '--preview "head -n $FZF_PREVIEW_LINES -- {}"'
end

set -x GIT_EDITOR "$EDITOR"

set -x HIGHLIGHT_OPTIONS '--force -t 4 --out-format=ansi'

set -x IPYTHONDIR "$XDG_DATA_HOME"/ipython

#set -x LANG en_US.UTF-8
#set -x LC_ALL en_US.UTF-8

#set -x LESS '--RAW-CONTROL-CHARS --quit-if-one-screen --no-init'
set -x LESS '--RAW-CONTROL-CHARS --no-init'
set -x LESSHISTFILE /dev/null

# Inhibit these dbind warnings: Couldn't register with accessibility bus
# https://wiki.archlinux.de/title/GNOME#Tipps_und_Tricks
# https://askubuntu.com/a/318997
# This affects meld.
set -x NO_AT_BRIDGE 1

# https://www.reddit.com/r/linux/comments/12wxsl/whats_in_your_bashrc/c6z0y5g/
#set -x JAVA_HOME (readlink -f -- (which javac) | sed 's|bin/javac||')

set -x PS_FORMAT pid,nice,pri,user,stime,etime,sz,pmem,pcpu,command

set -x PYLINTHOME "$XDG_CACHE_HOME"/pylint.d

# https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPATH
set -x PYTHONPATH "$HOME"/.local/lib/python

# https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPYCACHEPREFIX
set -x PYTHONPYCACHEPREFIX "$XDG_CACHE_HOME"/__pycache__

set -x RSYNC_ARGS -v -c -u -p -t -r -z -h
#-v, --verbose               increase verbosity
#-c, --checksum              always checksum
#-u, --update                update only (don't overwrite newer files)
#-p, --perms                 preserve permissions
#-t, --times                 preserve times
#-n, --dry-run               show what would have been transferred
#-r, --recursive             recurse into directories
#-z, --compress              compress file data during the transfer
#-C, --cvs-exclude           auto ignore files in the same way CVS does
#-h, --human-readable        output numbers in a human-readable format
#    --progress              show progress during transfer
#-i, --itemize-changes       output a change-summary for all updates
#    --password-file=FILE    read daemon-access password from FILE

# /usr/bin/time format similar to bash's time
set -x TIME "real\t%E\nuser\t%U\nsys\t%S\n"

set -x TRASH_DIR "$XDG_DATA_HOME"/Trash
if not test -d "$TRASH_DIR"
    mkdir --verbose --mode=0700 -- "$TRASH_DIR"
end

set -x TZ 'America/New_York'

set -x VCS_REPOS_MATCH '( -type d -and ( -name CVS -or -name .svn -or -name .git -or -name .hg ) )'
set -x VCS_REPOS_PRUNE "( $VCS_REPOS_MATCH -prune , -not $VCS_REPOS_MATCH )"

if not test -d "$XDG_CACHE_HOME"/xorg
    mkdir --verbose --parents -- "$XDG_CACHE_HOME"/xorg
end
set -x XAUTHORITY "$XDG_CACHE_HOME"/xorg/Xauthority

# {{{ Start X at login
# https://wiki.archlinux.org/index.php/Fish#Start_X_at_login
#if status is-login
    if test -z "$DISPLAY" -a "$XDG_VTNR" = 1
        #exec startx -- -keeptty
        :
    end
#end
# }}}

# }}}

end

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

#if string match --entire --regex --quiet '/dev/tty[0-9]+' (tty)
##### TODO: see if this works without "--entire"
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

# }}}

if status is-interactive

# {{{ prevent st unknown escape sequence

# https://github.com/fish-shell/fish-shell/issues/3425
if string match -q "st-*" "$TERM"
    set -e VTE_VERSION
end

# }}}

# {{{ ls colors

# convert from sh to fish syntax
#eval (dircolors | sed -r -e 's/^([^=]+?)=(.*)/set \1 \2/' -e 's/^export .+//')
#dircolors | sed -r -e 's/^([^=]+)=(.*)/set -x \1 \2/' -e 's/^export .+//' | source

#if test $TERM = linux
#    # change dir color
#    set --append --export --path LS_COLORS 'di=0;33'
#end

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

# 0 = black
# 1 = red
# 2 = green
# 3 = yellow
# 4 = blue
# 5 = magenta
# 6 = cyan
# 7 = white

set -x LESS_TERMCAP_mb (tput bold; tput setaf 6) # turn on blinking
set -x LESS_TERMCAP_md (tput bold; tput setaf 2) # turn on bold (extra bright) mode
set -x LESS_TERMCAP_mh (tput dim) # turn on half-bright mode
set -x LESS_TERMCAP_mr (tput rev) # turn on reverse video mode
set -x LESS_TERMCAP_so (tput bold; tput rev; tput setaf 4) # begin standout mode
set -x LESS_TERMCAP_ZN (tput ssubm) # Enter subscript mode
set -x LESS_TERMCAP_ZO (tput ssupm) # Enter superscript mode
set -x LESS_TERMCAP_us (tput smul; tput bold; tput setaf 3) # begin underline mode
set -x LESS_TERMCAP_me (tput sgr0) # turn off all attributes
set -x LESS_TERMCAP_se (tput rmso; tput sgr0) # exit standout mode
set -x LESS_TERMCAP_ZV (tput rsubm) # End subscript mode
set -x LESS_TERMCAP_ZW (tput rsupm) # End superscript mode
set -x LESS_TERMCAP_ue (tput rmul; tput sgr0) # exit underline mode

# For Konsole and Gnome-terminal
#set -x GROFF_NO_SGR 1

# https://stackoverflow.com/a/19871578
set -x MANPAGER 'less -s -M +Gg'

# }}}


# {{{ env_parallel

if command --quiet env_parallel
    source (which env_parallel.fish)
end

# }}}

# {{{ source other config files

if test -f (dirname (status filename))/private.fish
    source (dirname (status filename))/private.fish
end

# }}}

# {{{ abbr

# abbr is a real-time replacement in interactive mode
# alias is a function wrapper for a command

abbr --add --global -- - cd -
abbr --add --global amek make
abbr --add --global amke make
abbr --add --global cdl cld
abbr --add --global clena clean
abbr --add --global csl cls
abbr --add --global e "$EDITOR"
abbr --add --global ed "$EDITOR"
abbr --add --global f find
abbr --add --global ff fzf
abbr --add --global gci git commit
abbr --add --global gcl git clean
abbr --add --global gco git checkout
abbr --add --global gd git diff
abbr --add --global gi git
abbr --add --global gk gitk
abbr --add --global gl git log
abbr --add --global gs git status
abbr --add --global his history
abbr --add --global hist history
abbr --add --global ip3 ipython3
abbr --add --global ipy3 ipython3
abbr --add --global m man
abbr --add --global maek make
abbr --add --global medl meld
abbr --add --global p2 python2
abbr --add --global p3 python3
abbr --add --global py2 python2
abbr --add --global py3 python3
abbr --add --global rbn sudo reboot now
abbr --add --global reutrn return
abbr --add --global s sudo
abbr --add --global sctl systemctl
abbr --add --global sdn sudo shutdown now
abbr --add --global treu true
abbr --add --global tyep type
abbr --add --global v "$VISUAL"
abbr --add --global whcih which
abbr --add --global xa xargs -r

# }}}

# {{{ alias

alias bc='bc -l'
alias chgrp='chgrp --preserve-root --changes'
alias chmod='chmod --preserve-root --changes'
alias chown='chown --preserve-root --changes'
alias cld='cls ; d'
alias clda='cls ; da'
alias cls='printf "\ec"' # tput clear
alias cp='cp --archive --backup=numbered'
alias ctags='ctags --recurse=yes --totals=yes --languages=C,C++'
alias d='ls --human-readable -o --file-type --color'
alias da='d --almost-all'
alias df='df --human-readable --print-type --exclude-type=squashfs'
alias diff='diff --unified --color'
alias dir-sizes='du --separate-dirs --bytes'
alias du2='du --summarize'
alias du3='du --max-depth=1'
alias du4='du --separate-dirs'
alias du='du --bytes --human-readable'
alias fe='fzf --print0 | xargs --null --no-run-if-empty --verbose --open-tty -- "$EDITOR"'
alias file-dates='find -type f -printf "%T@\t%Tc\t%p\n"'
alias file-lines='find -type f -print0 | wc --lines --files0-from=-'
alias file-sizes='find -type f -printf "%s\t%p\n"'
alias find-dangling-symlinks='find -xtype l'
# We don't want an alias named "grep" with so many options
#alias grep='grep --color --line-number --binary-files=without-match --directories=skip'
alias g='grep --color --line-number --binary-files=without-match --directories=skip'
alias gccc="gcc $CFLAGS"
alias gf='git log --oneline --decorate --color | fzf --no-sort --layout=reverse-list --preview "git show --color=always {1}"'
alias gif2png='gif2png -m -n -s -O'
alias gr='g --directories=recurse --exclude-dir={.bzr,CVS,.git,.hg,.svn}'
alias gpp="g++ $CXXFLAGS"
alias jpegtran2='jpegtran -optimize -copy all'
alias longest_line="awk 'length > l {r = NR; l = length} END{print r, l}'"
alias lsd='lsd --classify --long --date relative --icon never --size short'
alias mirror2='wget --verbose --force-directories --no-host-directories --html-extension --mirror --convert-links --backup-converted --page-requisites --relative --no-parent'
alias mirror='wget --verbose --mirror --page-requisites'
alias mv='mv --backup=numbered'
alias my_ip='curl ipinfo.io'
alias num-file-extensions="f \( -type f -or -type l \) -printf '%f\n' | awk --field-separator . '{print \$NF}' | sort | uniq --count"
# XXX: version sort doesn't do case folding
# List all directories in the current working directory.
alias only-dirs='find . -maxdepth 1 -type d -not -name ".*" -printf "%f\0" | xargs --null --no-run-if-empty ls --human-readable -o --file-type --color --directory'
alias only-dirs-all='find . -maxdepth 1 -type d -not -name "." -printf "%f\0" | xargs --null --no-run-if-empty ls --human-readable -o --file-type --color --directory'
# XXX: version sort doesn't do case folding
# List all files in the current working directory.
alias only-files='find . -maxdepth 1 -type f -not -name ".*" -printf "%f\0" | xargs --null --no-run-if-empty ls --human-readable -o --file-type --color --directory'
alias only-files-all='find . -maxdepth 1 -type f -not -name "." -printf "%f\0" | xargs --null --no-run-if-empty ls --human-readable -o --file-type --color --directory'
alias optijpg='jpegoptim --preserve --strip-none'
alias optipng='optipng -fix -preserve -quiet -o 2 -i 0'
alias palindromes='paste --delimiters="\n" /usr/share/dict/words <(rev /usr/share/dict/words) | uniq --repeated'
alias prettyjson='python3 -m json.tool'
alias ps1='ps --forest --headers -e                    --sort pid'
alias ps2='ps --forest --headers -U root -u root -N    --sort pid'
alias ps3='ps --forest --headers -U "$USER" -u "$USER" --sort pid'
alias pstree='pstree -ahlnp'
alias pwgen='tr -cd "0-9A-Za-z_" < /dev/urandom | head -c 16 ; echo'
alias pylint='pylint --disable=pointless-string-statement'
alias rdiff='diff --recursive --new-file'
# https://debbugs.gnu.org/cgi/bugreport.cgi?bug=42501
alias rm='rm --preserve-root --interactive'
alias split='split --verbose --suffix-length=3 --numeric-suffixes'
alias ssh_my='ssh_to $MY_WEBSITE'
alias ssh_to='ssh -Y -o ServerAliveInterval=60'
alias t-code='cd && t code && xz -9 -e code.tar && mv code.tar.xz Downloads/ && cd Downloads/ && printf "del code.tar.xz && exit\n"'
alias tmux='tmux -f "$XDG_CONFIG_HOME"/tmux/tmux.conf'
alias tree='tree -AFCaq'
alias units='units --history ""'
alias watch='watch --differences'
alias wc2='echo "  lines   words file" ; wc --lines --words'
alias wc3='wc --lines --words ; echo "  lines   words"'
alias xz='xz --verbose --threads=0'
alias zero-out='truncate --size=0 --no-create'

alias blake2=b2sum
alias md5=md5sum
alias sha1=sha1sum
alias sha224=sha224sum
alias sha256=sha256sum
alias sha384=sha384sum
alias sha512=sha512sum


# {{{ package management

# convert from sh to fish syntax
sed -r -e 's/^([^=]+)=(.*)/set \1 \2/' /etc/os-release | source

# $ID is set in /etc/os-release
switch "$ID"

# https://wiki.archlinux.org/index.php/Pacman/Rosetta

# https://www.archlinux.org/pacman/pacman.8.html
case arch
    abbr --add --global cu checkupdates
    abbr --add --global sp sudo pacman --color always

    alias inst='sudo pacman --color always -S --needed'
    ##### XXX what about:
    # --answerclean All
    # --answeredit None
    # --answerupgrade None
    # --cleanafter
    alias yinst='yay -S --needed --answerdiff None'
    alias uninst='sudo pacman --color always -Rs'
    ##### TODO: maybe use xargs
    alias autorm='pacman -Qdtq | sudo pacman --color always -Rs -' ##### TODO: test this
    alias upd='sudo pacman --color always -Syw'
    alias upg='sudo pacman --color always -Syu'
    alias pf="pacman -Sl | fzf --preview 'pacman --color always -Si {2}'"

# https://wiki.archlinux.org/index.php/Pacman/Tips_and_tricks#Browsing_packages
# pacman -Qq | fzf --preview 'pacman -Qil {}' --layout=reverse --bind 'enter:execute(pacman -Qil {} | less)'

case fedora
    ##### TODO: test these
    alias cu='dnf check-update'
    abbr --add --global sd sudo dnf

    alias inst='sudo dnf install'
    alias uninst='sudo dnf remove'
    alias autorm='sudo dnf autoremove'
    alias upd='sudo dnf list updates'
    alias upg='sudo dnf upgrade'

    alias dnff='dnf list | fzf --preview "dnf info {1}"'

case ubuntu
    abbr --add --global sa sudo apt
    abbr --add --global syn sudo synaptic

    alias inst='sudo apt install'
    alias uninst='sudo apt purge' # or remove
    alias autorm='sudo apt autoremove'
    alias upd='sudo apt update'
    alias upg='sudo apt upgrade'

    alias rmdeborphan='sudo apt-get purge (deborphan)'

    alias af='apt-cache pkgnames | fzf --preview "apt-cache show {}"'

case '*'

end

# }}}

# }}}

end

