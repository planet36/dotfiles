# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# shellcheck shell=bash

# {{{ abbr

alias -- -='cd - > /dev/null'
alias amek=make
alias amke=make
alias bahs=bash
alias b2=b2sum
alias b3=b3sum
alias c=clear
alias cdl=cld
alias celan=clean
alias clena=clean
alias cu=checkupdates
alias dc=cd
# shellcheck disable=SC2139
alias e="$EDITOR"
# shellcheck disable=SC2139
alias ed="$EDITOR"
alias emdl=meld
alias emld=meld
alias f=find
alias fidn=find
alias fiel=file
alias i="$EDITOR -c startinsert"
alias ip3=ipython3
alias ipy3=ipython3
alias m=make
alias maek=make
alias mc='make clean'
alias md5=md5sum
alias medl=meld
alias mkae=make
alias mled=meld
alias p3=python3
alias py3=python3
alias q=exit
alias reutrn=return
alias rtash=trash
alias sctl=systemctl
alias sha1=sha1sum
alias sha224=sha224sum
alias sha256=sha256sum
alias sha384=sha384sum
alias sha512=sha512sum
alias tiem=time
alias trahs=trash
alias trsah=trash
alias treu=true
alias tyep=type
alias upd='doas pacman -Syw'
alias upg='doas pacman -Syu'
# shellcheck disable=SC2139
alias v="$VISUAL"
alias whcih=which

# }}}

# {{{ alias

alias chgrp='chgrp --preserve-root --changes'
alias chmod='chmod --preserve-root --changes'
alias chown='chown --preserve-root --changes'
alias cp='cp --archive --backup=numbered'
alias ctags='ctags --recurse=yes --totals=yes --languages=C,C++'
#alias d='ls --human-readable -o --file-type --color'
#alias d='lsd --date=relative --icon=never --long'
alias d='eza --long --color-scale=all --icons=never --group --smart-group --time-style=relative --no-git'
alias da='d --almost-all'
alias df='df --human-readable --print-type --exclude-type=squashfs'
alias diff='diff --unified --color'
alias dir-sizes='du --separate-dirs --bytes'
alias dn='d --sort=modified'
alias ds='d --sort=size'
alias du2='du --summarize'
alias du3='du --max-depth=1'
alias du4='du --separate-dirs'
alias du='du --bytes --human-readable'
alias fd='fd -H'
#alias fe='find . -type f -print0 | fzf --read0 --print0 | xargs --null --no-run-if-empty --verbose --open-tty -- "$EDITOR"'
#alias ff='find . -type f | fzf'
alias file-dates='find . -type f -printf "%T@\t%Tc\t%p\n"'
alias file-lines='find . -type f -print0 | wc --lines --files0-from=-'
alias file-sizes='find . -type f -printf "%s\t%p\n"'
alias file-times=file-dates
alias file1-dates='find . -maxdepth 1 -type f -printf "%T@\t%Tc\t%p\n"'
alias file1-lines='find . -maxdepth 1 -type f -print0 | wc --lines --files0-from=-'
alias file1-sizes='find . -maxdepth 1 -type f -printf "%s\t%p\n"'
alias file1-times=file1-dates
alias find-dangling-symlinks='find . -xtype l'
alias gf='git log --oneline --decorate --color | fzf --no-sort --layout=reverse-list --preview "git show --color=always {1}"'
alias gif2png='gif2png -m -n -s -O'
alias jpegtran2='jpegtran -optimize -copy all'
alias longest_line="awk 'length > l {r = NR; l = length} END{print r, l}'"
alias mirror2='wget --verbose --force-directories --no-host-directories --html-extension --mirror --convert-links --backup-converted --page-requisites --relative --no-parent'
alias mirror='wget --verbose --mirror --page-requisites'
alias mv='mv --backup=numbered'
alias my_ip='curl ipinfo.io'
alias num-file-extensions="find . \( -type f -or -type l \) -printf '%f\n' | awk --field-separator . '{print \$NF}' | sort | uniq --count"
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
alias pcal='python3 -m calendar -f 6'
alias prettyjson='python3 -m json.tool'
alias ps1='ps --forest --headers -e                    --sort pid'
alias ps2='ps --forest --headers -U root -u root -N    --sort pid'
alias ps3='ps --forest --headers -U "$USER" -u "$USER" --sort pid'
alias pstree='pstree -ahlnp'
alias pwgen='tr -cd "0-9A-Za-z_" < /dev/urandom | head -c 16 ; echo'
alias rdiff='diff --recursive --new-file'
# https://debbugs.gnu.org/cgi/bugreport.cgi?bug=42501
alias rm='rm --preserve-root --interactive'
alias split='split --verbose --suffix-length=3 --numeric-suffixes'
alias ssh_my='TERM=xterm-256color ssh_to $MY_WEBSITE'
alias ssh_to='ssh -Y -o ServerAliveInterval=60'
alias swp='exch'
alias t-tmp='cd && clean code && find . -type f -name a.out -delete && t code/tmp && command xz --verbose -9 -e tmp.tar && mv tmp.tar.xz Downloads/ && cd Downloads/ && printf "del tmp.tar.xz && exit\n"'
alias tma='tmux attach-session || tmux'
alias tmd='tmux detach-client'
alias tree='tree -AFCaq'
alias watch='watch --differences'
alias wc2='echo "  lines   words file" ; wc --lines --words'
alias wc3='wc --lines --words ; echo "  lines   words"'
alias wget='wget --hsts-file="$XDG_DATA_HOME/wget-hsts"'
alias xz='xz --verbose --threads=0'
alias zero-out='truncate --size=0 --no-create'

# https://wiki.archlinux.org/index.php/Pacman/Rosetta
# https://www.archlinux.org/pacman/pacman.8.html
alias inst='doas pacman -S --needed'
##### XXX what about:
# --answerclean All
# --answeredit None
# --answerupgrade None
# --cleanafter
alias yinst='yay -S --needed --answerclean None --answerdiff None'
alias uninst='doas pacman -Rs'
alias yuninst='yay -Rs'
alias autorm='pacman -Qdtq | doas pacman -Rs -'
alias pf="pacman -Sl | fzf --nth 2.. --preview 'pacman -Si {2}'"

# https://wiki.archlinux.org/index.php/Pacman/Tips_and_tricks#Browsing_packages
# pacman -Qq | fzf --preview 'pacman -Qil {}' --layout=reverse --bind 'enter:execute(pacman -Qil {} | less)'

# }}}
