#!/usr/bin/bash

mapfile -t REPOS < git-repos.txt

for REPO in "${REPOS[@]}"
do
	echo "REPO=$REPO"

	if [[ "$REPO" == '#'* ]]
	then
		echo "##### skip"
		continue
	fi

	DIR="$(basename -s .git -- "$REPO")" || exit

	if [[ "$REPO" == https://git.suckless.org/* ]]
	then
		DIR="$DIR"-suckless
	fi

	if [[ -d "$DIR" ]]
	then
		make -C "$DIR" clean uninstall || exit
	fi
done
