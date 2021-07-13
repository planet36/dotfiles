#!/usr/bin/bash

# https://mywiki.wooledge.org/BashFAQ/020

while IFS= read -r -d '' DIR
do
  echo "## $DIR"
  if test -d "$DIR"/.git
  then
    cd "$DIR" || break
    git fetch || break
    git pull || break
    #git fsck || break
    #git gc || break
    cd - &> /dev/null || break
  else
    echo "Not a git repo"
  fi
  echo
  echo
done < <(find . -type d -name .git -printf '%h\0' | sort --version-sort --zero-terminated)
