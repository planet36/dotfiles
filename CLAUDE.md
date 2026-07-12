# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A personal dotfiles repo (`~/.dotfiles`, GitHub `planet36`). `install.bash` deploys it into a target
directory (normally `$HOME`), run *from* that target directory:

- Files under `copy/` are **copied** to the target.
- Files under `link/` are **symlinked** to the target (unless `-c` copies them too).
- Both preserve directory structure and create parent dirs. `-d` reverses the install (deletes only
  files/links still identical to their source, and empty dirs it created), `-n` is a dry run, `-v`
  is verbose. See `bash install.bash -h`.

After a normal install it runs `fc-cache` and byte-compiles `~/.local/lib/python/` at all three
optimization levels. It refuses to install into the dotfiles dir itself.

## Layout

- `link/.local/bin/` — executable scripts on `$PATH` (16 Python, 18 bash, 7 POSIX sh). The current
  working directory.
- `link/.local/lib/python/` — hand-written Python modules `import`ed by the `bin/` scripts.
- `link/.local/include/` — C/C++ headers (`.hpp`/`.h`) consumed by other projects via `-iquote`.
- `link/.local/src/` — a `Makefile` that clones external repos (dwm, st, slstatus, PractRand, …) and
  builds the buildable ones. Not this repo's own source.
- `link/.config/` — application configs (bash, fish, nvim, git, terminals, claude, …).
- `link/.config/claude/skills/` — repo-local Claude Code slash-command skills: `review` (C/C++
  file review), `review-py` (Python file review), `changes` (summarize recent commits).
- `copy/` — files that are copied rather than linked.
- `other/generate-src/` — source-file generators. **Has its own CLAUDE.md.**
- `other/build-local/` — small C/C++ CLI utilities and daemons. **Has its own CLAUDE.md.**
- `other/depot/` — plain lists (browser extensions).

## The load-bearing environment coupling

`link/.config/bash/envvars.bash` (symlinked to `~/.config/bash/envvars.bash` on install) is what
ties the pieces together, and much of the code here only works once it is installed and sourced:

- `PYTHONPATH=$HOME/.local/lib/python` — how `bin/` scripts resolve their `import`s of the
  `lib/python/` modules (which are symlinks into this repo).
- `CPPFLAGS` includes `-iquote $HOME/.local/include` — how C/C++ code elsewhere (notably
  `other/build-local`) finds the headers in `link/.local/include/` (also symlinks).
- `CFLAGS`/`CXXFLAGS` pin the latest `-std=gnu2y`/`-std=gnu++26` the installed GCC supports plus a
  strict warning set; `CC=gcc`, `CXX=g++`.

So: editing a `lib/python` module or an `include/` header changes behavior everywhere those are
consumed, but only on a machine where the dotfiles are installed. Generated headers/modules under
`link/.local/` are produced by `other/generate-src` — regenerate there, don't hand-edit generated
output.

## Verifying changes (there is no test suite)

Verification is per-language, using tools installed globally with **no project config** — don't add
config files; false positives are suppressed with inline per-file comments (e.g. `# pylint:
disable=...`).

- **Python** (`bin/*.py`, `lib/python/*.py`): a change is clean when `ruff check`, `mypy
  --ignore-missing-imports`, and `pylint` all pass on the changed file(s), plus the script runs.
- **bash / sh** (`bin/*`, `install.bash`, `*.bash`): `shellcheck` and `shellharden` stay quiet.
- **C/C++ headers** (`link/.local/include/`): `make` compiles every header as its own translation
  unit under a strict, `-Werror` warning set; `make lint` runs `clang-tidy`. Fix the code rather
  than loosening flags.
- The two `other/` subtrees have their own build/verify commands — see their CLAUDE.md files.

The `/review` (C/C++) and `/review-py` (Python) skills wrap these checks into a structured review;
`/review-py` runs `ruff check`, `mypy --ignore-missing-imports`, and `pylint` (plus `pytest` if a
suite exists) and respects existing inline `# pylint: disable=` / `# noqa` suppressions.

## Conventions worth matching

- Every file carries an SPDX header: `SPDX-FileCopyrightText: Steven Ward` /
  `SPDX-License-Identifier: MPL-2.0`.
- Python scripts define `__author__`/`__license__`/`__version__` (version is an ISO date string),
  a module docstring, and a `main(argv=None)` that returns an exit code, called via
  `sys.exit(main())`.
- bash scripts use `set -euo pipefail`, factor logic into functions, and parse options with
  `getopts` (`-V` version / `-h` help are near-universal).
- A few files are vendored copies kept in sync with upstream (e.g. `lib/python/hsluv.py`,
  `bin/unimatrix`) — make only upstream-reconciliation edits there, never local lint/style fixes,
  and exclude them from repo-wide sweeps.

## Commits

End commit messages with the `Co-Authored-By` trailer. When only one file changed, omit its filename
from the summary line.
