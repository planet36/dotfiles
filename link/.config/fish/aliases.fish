# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

alias bc='bc -l'
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
alias z='zoxide'
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

