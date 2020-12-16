#!/usr/bin/fish

for DIR in (find . -type d -name .git -printf '%h\n' | sort --version-sort)
  echo "## $DIR"
  cd "$DIR" || break
  if test -d .git
    git fetch || break
    git pull || break
  else
    echo "Not a git repo"
  end
  cd - || break
  echo
  echo
end
