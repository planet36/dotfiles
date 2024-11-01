# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# abbr is a real-time replacement in interactive mode
# alias is a function wrapper for a command

# {{{ abbr

abbr --add --global -- - cd -
abbr --add --global amek make
abbr --add --global amke make
abbr --add --global bahs bash
abbr --add --global b2 b2sum
abbr --add --global b3 b3sum
abbr --add --global c clear
abbr --add --global cdl cld
abbr --add --global celan clean
abbr --add --global clena clean
abbr --add --global dc cd
abbr --add --global e "$EDITOR"
abbr --add --global ed "$EDITOR"
abbr --add --global emdl meld
abbr --add --global emld meld
abbr --add --global f find
abbr --add --global fidn find
abbr --add --global fiel file
abbr --add --global i "$EDITOR" -c startinsert
abbr --add --global ip3 ipython3
abbr --add --global ipy3 ipython3
abbr --add --global maek make
abbr --add --global md5 md5sum
abbr --add --global medl meld
abbr --add --global mkae make
abbr --add --global mled meld
abbr --add --global p3 python3
abbr --add --global py3 python3
abbr --add --global q exit
#abbr --add --global rbn doas reboot now
# log out, then reboot
abbr --add --global rbn doas systemctl reboot   --when=+3s \& disown \; exit 0
abbr --add --global reutrn return
abbr --add --global rtash trash
abbr --add --global sctl systemctl
#abbr --add --global sdn doas shutdown now
# log out, then poweroff
abbr --add --global sdn doas systemctl poweroff --when=+3s \& disown \; exit 0
abbr --add --global sha1 sha1sum
abbr --add --global sha224 sha224sum
abbr --add --global sha256 sha256sum
abbr --add --global sha384 sha384sum
abbr --add --global sha512 sha512sum
abbr --add --global tiem time
abbr --add --global trahs trash
abbr --add --global trsah trash
abbr --add --global treu true
abbr --add --global tyep type
abbr --add --global upd doas pacman -Syw
abbr --add --global upg doas pacman -Syu
abbr --add --global v "$VISUAL"
abbr --add --global whcih which

# }}}
