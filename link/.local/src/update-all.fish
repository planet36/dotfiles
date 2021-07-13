#!/usr/bin/fish

for DIR in (find . -type d -name .git -printf '%h\n' | sort --version-sort)
  echo "## $DIR"
  if test -d "$DIR"/.git
    cd "$DIR" || break
    git fetch || break
    git pull || break
    #git fsck || break
    #git gc || break
    cd - || break
  else
    echo "Not a git repo"
  end
  echo
  echo
end
