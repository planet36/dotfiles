#!/usr/bin/bash

declare -a REPOS=(
https://github.com/planet36/arch-install.git
https://github.com/planet36/dwm.git
#git@github.com:planet36/dwm.git
https://github.com/planet36/slstatus.git
#git@github.com:planet36/slstatus.git
https://github.com/planet36/st.git
#git@github.com:planet36/st.git
https://git.suckless.org/dwm
https://git.suckless.org/slstatus
https://git.suckless.org/st
https://github.com/sineemore/stw.git
)

for REPO in "${REPOS[@]}"
do
	DIR="$(basename -s .git -- "$REPO")" || exit

	if [[ "$REPO" =~ https://git.suckless.org/* ]]
	then
		DIR="$DIR"-suckless
	fi

	if [[ -d "$DIR" ]]
	then
		make PREFIX="$HOME"/.local -C "$DIR" clean uninstall || exit
	fi
done
