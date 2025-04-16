#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# https://mywiki.wooledge.org/BashFAQ/020

while IFS= read -r -d '' DIR
do
  echo "## $DIR"
  if test -d "$DIR"/.git
  then
    cd "$DIR" || break
    if [[ "$(git rev-parse --is-bare-repository)" == 'false' ]]
    then
      git pull --no-all || break
    else
      git fetch --no-all || break
    fi
    #git fsck || break
    #git gc || break
    cd - > /dev/null || break
  else
    echo "Not a git repo"
  fi
  echo
  echo
done < <(find . -type d -name .git -printf '%h\0' | sort --ignore-case --version-sort --zero-terminated)
