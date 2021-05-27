#!/usr/bin/bash

# https://mywiki.wooledge.org/BashFAQ/020

while IFS= read -r -d '' DIR
do
  echo "## $DIR"
  cd "$DIR" || break
  if test -d .git
  then
    git fetch || break
    git pull || break
    git fsck || break
    git gc || break
  else
    echo "Not a git repo"
  fi
  cd - &> /dev/null || break
  echo
  echo
done < <(find . -type d -name .git -printf '%h\0' | sort --version-sort --zero-terminated)
