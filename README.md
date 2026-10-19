# dotfiles

## Description

This repository has my dotfiles.

## Usage

`install.bash` installs the dotfiles into the current directory, which is normally `$HOME`.

```sh
cd
git clone https://github.com/planet36/dotfiles.git .dotfiles
bash .dotfiles/install.bash -n    # show what would be done
bash .dotfiles/install.bash
```

It symlinks the files under `link/`, so editing one of them edits the repo.  It copies the files
under `copy/`, which are configs that their programs rewrite and empty placeholders for private
settings.  An existing file in the way is renamed with a numbered backup suffix, such as
`.bashrc.~1~`.

The `-d` option removes what an install created, and `-h` lists every option.
