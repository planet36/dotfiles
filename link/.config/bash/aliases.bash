# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash

# {{{ abbr

alias -- -='cd - > /dev/null'
alias amek=make
alias amke=make
alias bahs=bash
alias blake2=b2sum
alias cdl=cld
alias clena=clean
alias csl=cls
# shellcheck disable=SC2139
alias e="$EDITOR"
# shellcheck disable=SC2139
alias ed="$EDITOR"
alias f=find
alias gci='git commit'
alias gcl='git clean'
alias gco='git checkout'
alias gd='git diff'
alias gi=git
alias gk=gitk
alias gl='git log'
alias gs='git status'
alias his=history
alias hist=history
alias ip3=ipython3
alias ipy3=ipython3
alias m=man
alias maek=make
alias md5=md5sum
alias medl=meld
alias p2=python2
alias p3=python3
alias py2=python2
alias py3=python3
alias rbn='sudo reboot now'
alias reutrn=return
alias s=sudo
alias sctl=systemctl
alias sdn='sudo shutdown now'
alias sha1=sha1sum
alias sha224=sha224sum
alias sha256=sha256sum
alias sha384=sha384sum
alias sha512=sha512sum
alias treu=true
alias tyep=type
# shellcheck disable=SC2139
alias v="$VISUAL"
alias whcih=which
alias xa='xargs -r'

# }}}

# {{{ alias

alias chgrp='chgrp --preserve-root --changes'
alias chmod='chmod --preserve-root --changes'
alias chown='chown --preserve-root --changes'
alias cld='cls ; d'
alias clda='cls ; da'
alias cls='printf "\ec"' # tput clear
alias cp='cp --archive --backup=numbered'
alias ctags='ctags --recurse=yes --totals=yes --languages=C,C++'
#alias d='ls --human-readable -o --file-type --color'
alias d='lsd --long'
alias da='d --almost-all'
alias df='df --human-readable --print-type --exclude-type=squashfs'
alias diff='diff --unified --color'
alias dir-sizes='du --separate-dirs --bytes'
alias du2='du --summarize'
alias du3='du --max-depth=1'
alias du4='du --separate-dirs'
alias du='du --bytes --human-readable'
alias fd='fd -H'
alias fe='fzf --print0 | xargs --null --no-run-if-empty --verbose --open-tty -- "$EDITOR"'
alias ff='find -type f | fzf'
alias file-dates='find -type f -printf "%T@\t%Tc\t%p\n"'
alias file-lines='find -type f -print0 | wc --lines --files0-from=-'
alias file-sizes='find -type f -printf "%s\t%p\n"'
alias find-dangling-symlinks='find -xtype l'
# We don't want an alias named "grep" with so many options
#alias grep='grep --color --line-number --binary-files=without-match --directories=skip'
alias g='grep --color --line-number --binary-files=without-match --directories=skip'
# shellcheck disable=SC2139
alias gccc="gcc $CFLAGS"
alias gf='git log --oneline --decorate --color | fzf --no-sort --layout=reverse-list --preview "git show --color=always {1}"'
alias gif2png='gif2png -m -n -s -O'
# shellcheck disable=SC2139
alias gpp="g++ $CXXFLAGS"
alias gr='g --directories=recurse --exclude-dir={.bzr,CVS,.git,.hg,.svn}'
alias jpegtran2='jpegtran -optimize -copy all'
alias longest_line="awk 'length > l {r = NR; l = length} END{print r, l}'"
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
alias pylint='pylint --disable=bad-indentation --disable=fixme --disable=invalid-name --disable=pointless-string-statement --disable=trailing-newlines'
alias rdiff='diff --recursive --new-file'
# https://debbugs.gnu.org/cgi/bugreport.cgi?bug=42501
alias rm='rm --preserve-root --interactive'
alias split='split --verbose --suffix-length=3 --numeric-suffixes'
alias ssh_my='TERM=xterm-256color ssh_to $MY_WEBSITE'
alias ssh_to='ssh -Y -o ServerAliveInterval=60'
alias t-code='cd && t code && xz -9 -e code.tar && mv code.tar.xz Downloads/ && cd Downloads/ && printf "del code.tar.xz && exit\n"'
alias tree='tree -AFCaq'
alias units='units --history ""'
alias watch='watch --differences'
alias wc2='echo "  lines   words file" ; wc --lines --words'
alias wc3='wc --lines --words ; echo "  lines   words"'
alias xz='xz --verbose --threads=0'
alias zero-out='truncate --size=0 --no-create'

# {{{ package management

# shellcheck disable=SC1091
[[ -f /etc/os-release ]] && source /etc/os-release

# $ID is set in /etc/os-release
case "${ID}" in

# https://wiki.archlinux.org/index.php/Pacman/Rosetta

# https://www.archlinux.org/pacman/pacman.8.html
arch)
    alias cu='checkupdates'
    alias sp='sudo pacman --color always'

    alias inst='sudo pacman --color always -S --needed'
    alias yinst='yay --color always -S --needed --answerclean None --answerdiff None'
    ##### XXX what about:
    # --answeredit None
    # --answerupgrade None
    # --cleanafter
    alias uninst='sudo pacman --color always -Rs'
    ##### TODO: maybe use xargs
    alias autorm='pacman -Qdtq | sudo pacman --color always -Rs -' ##### TODO: test this
    alias upd='sudo pacman --color always -Syw'
    alias upg='sudo pacman --color always -Syu'
    ;;

fedora)
    ##### TODO: test these
    alias cu='dnf check-update'
    alias sd='sudo dnf'

    alias inst='sudo dnf install'
    alias uninst='sudo dnf remove'
    alias autorm='sudo dnf autoremove'
    alias upd='sudo dnf list updates'
    alias upg='sudo dnf upgrade'

    alias dnff='dnf list | fzf --preview "dnf info {1}"'
    ;;

ubuntu)
    alias sa='sudo apt'
    alias syn='sudo synaptic'

    alias inst='sudo apt install'
    alias uninst='sudo apt purge' # or remove
    alias autorm='sudo apt autoremove'
    alias upd='sudo apt update'
    alias upg='sudo apt upgrade'

    alias rmdeborphan='sudo apt-get purge $(deborphan)'

    alias af='apt-cache pkgnames | fzf --preview "apt-cache show {}"'
    ;;

*)
    ;;

esac

# }}}

# }}}

