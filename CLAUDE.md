# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this
repository.

## What this is

A personal dotfiles repo (`~/.dotfiles`, GitHub `planet36`).  `install.bash` deploys it into a
target directory, normally `$HOME`, and is run *from* that target directory.  It copies the
files under `copy/` and symlinks the files under `link/`.  See `bash install.bash -h`.

Unless it is a dry run (`-n`), an install also runs `fc-cache` and byte-compiles
`~/.local/lib/python/` at all three optimization levels.  The script refuses to run from the
dotfiles directory or anywhere under it.

Prose in comments, doc blocks, commit messages, and documentation files follows this guide:

@COMMENT-STYLE.md

A session started below the repo root may not have that import.  If the guide's rules are not
in context, read `COMMENT-STYLE.md` before writing any of that prose.

## Layout

- `link/.local/bin/` holds the scripts, and `link/.local/lib/python/` holds the modules they
  import.
- `link/.local/include/` holds C and C++ headers.
- `link/.local/src/Makefile` clones external repos (dwm, st, slstatus, PractRand, Castella, …)
  into `~/.local/src/` and builds the buildable ones.  None of them is this repo's own source.
- `link/.config/claude/skills/` holds the Claude Code skills, including `/review` and
  `/review-py`.
- `other/generate-src/` holds source-file generators, and `other/build-local/` holds small C
  and C++ utilities and daemons.  **Each has its own CLAUDE.md.**

## The environment coupling

`link/.config/bash/envvars.bash` ties the pieces together.  Install symlinks it to
`~/.config/bash/envvars.bash`, and much of the code here works only once it is installed and
sourced.

- `PYTHONPATH=$HOME/.local/lib/python` is how the scripts in `bin/` resolve their imports of
  the modules in `lib/python/`, which are symlinks into this repo.
- `CPPFLAGS` includes `-iquote $HOME/.local/include`, which is how C and C++ code elsewhere,
  notably `other/build-local`, finds the headers in `link/.local/include/`.
- `CFLAGS` and `CXXFLAGS` pin the latest `-std=gnu2y` and `-std=gnu++26` the installed GCC
  supports, plus a strict warning set.
- It also exports `CC=gcc` and `CXX=g++`.

Editing a module in `lib/python/` or a header in `include/` therefore changes behavior
everywhere it is consumed, but only on a machine where the dotfiles are installed.

The generated headers and modules under `link/.local/` come from `other/generate-src`.
Regenerate them there rather than editing the output by hand.

## Verifying changes (there is no test suite)

Each language has its own checks, run with globally installed tools.  The Python and shell
checks use no project config, so don't add one.  Suppress a false positive with an inline
comment in the file, such as `# pylint: disable=...`.

- **Python.**  A change to a script or a module in `lib/python/` is clean when `ruff check`,
  `mypy --ignore-missing-imports`, and `pylint` all pass on the changed files and the script
  runs.
- **bash and sh.**  `shellcheck` and `shellharden` stay quiet on the scripts in `bin/`,
  `install.bash`, and any `*.bash` file.
- **C and C++ headers.**  In `link/.local/include/`, `make` compiles each header as its own
  translation unit under a strict `-Werror` warning set.  Every recipe ignores errors, so
  `make` exits 0 even when a header fails, and only its output shows the failure.
- **clang-tidy.**  `make lint` runs `clang-tidy` with the `.clang-tidy` in that directory.
  Its output is not clean, because some diagnostics are accepted, so judge only new ones.
  Fix the code rather than loosening flags.
- The two `other/` subtrees have their own build and verify commands, which their CLAUDE.md
  files give.

The `/review` (C/C++) and `/review-py` (Python) skills wrap these checks into a structured
review.

## Conventions worth matching

- Every script and source file carries an SPDX header, `SPDX-FileCopyrightText: Steven Ward`
  and `SPDX-License-Identifier: MPL-2.0`.  Config files and vendored copies may lack one.
- Python scripts define `__author__`, `__license__`, and `__version__`, whose value is an ISO
  date string.  They also have a module docstring and, unless the script is a trivial stdin
  filter, a `main(argv: list[str] | None = None) -> int | None` called via
  `sys.exit(main())`.
- `install.bash` is the model for a bash script that takes options.  It factors its logic into
  functions and parses options with `getopts`, offering `-V` for the version and `-h` for help.
- Headers in `link/.local/include/` wrap a debug `assert` and its `<cassert>` include in
  `#if defined(DEBUG)`.  The check is off unless `DEBUG` is defined, whatever `NDEBUG` says.
  `make` never defines `DEBUG`, so to check that code, instantiate it in a test program built
  with `-DDEBUG`.
- A few files are vendored copies kept in sync with upstream, such as `lib/python/hsluv.py`,
  `bin/unimatrix`, `bin/wttr`, and `bin/dseq`.  Make only upstream-reconciliation edits there,
  never local lint or style fixes, and exclude them from repo-wide sweeps.
- Some headers in `link/.local/include/` are copies of headers in the Castella,
  prng-test-bench, and randp repos, which `link/.local/src/Makefile` clones into
  `~/.local/src/`.  Treat them like the vendored copies.  The other repo's copy wins, so fix a
  defect there and sync it back.  A shared header stays here only while another header here
  includes it.

## Commits

End commit messages with the `Co-Authored-By` trailer.  Leave filenames out of the summary
line, and describe the change rather than which files it touched.
