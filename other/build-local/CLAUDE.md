# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

`other/build-local` is a subdirectory of a personal dotfiles repo (`~/.dotfiles`). It holds a
collection of small, independent single-purpose C/C++ command-line utilities and daemons, each
in its own directory with exactly one source file and a boilerplate `Makefile`.

## Build commands

Run from this directory (`other/build-local`) or from a single utility's subdirectory:

```sh
make            # build all utilities (or the one in cwd)
make clean      # remove built binaries, .o, and .d files
make lint       # run clang-tidy over the sources (uses .clang-tidy in this dir)
make install    # install to $DESTDIR$PREFIX/bin (PREFIX defaults to /usr/local)
make uninstall
```

The top-level `Makefile` just fans `all`/`clean`/`install`/`uninstall`/`lint` out to every
subdirectory (`$(wildcard */.)`). There is no top-level test target and no test suite in this
directory — verification is: it builds cleanly, `make lint` is quiet, and manual invocation
behaves per the program's `-h` usage text.

To build/lint/test a single utility, `cd` into its directory and run `make`/`make lint` there.

### Build environment dependency (important)

Every per-utility `Makefile` is intentionally minimal and leaves `CFLAGS`/`CXXFLAGS`/`CPPFLAGS`
unset (commented out) so they are inherited from the shell environment. That environment is
defined elsewhere in the dotfiles repo, in `link/.config/bash/envvars.bash`, which is symlinked
to `~/.config/bash/envvars.bash` by the repo's `install.bash`. Notably:

- `CPPFLAGS` includes `-iquote $HOME/.local/include`. Several utilities here (`cpuavgd`,
  `netrxavgd`, `nettxavgd`) `#include` local headers (e.g. `acfile.h`, `pscanf.h`, `strtou.h`,
  `timeval.h`, `timespec.h`) that live in `../../link/.local/include/` and are only resolvable
  via that flag. **These will fail to compile unless the dotfiles are installed** (so
  `~/.local/include` is populated with symlinks into `link/.local/include`) and the shell has
  sourced `envvars.bash`.
- `CFLAGS`/`CXXFLAGS` auto-detect and pin to the *latest* `-std=gnu2y` / `-std=gnu++26` the
  installed GCC supports, plus a large, deliberately strict warning set (`-Wall -Wextra
  -Wpedantic -Wshadow -Wcast-qual -Wc++-compat` for C, plus various `-W...` C++ hardening flags
  for C++). Don't add flags to individual Makefiles to work around warnings from this shared set
  — fix the code instead, matching the existing style in these files.
- `CC=gcc`, `CXX=g++` are also exported there.

If you need to build/lint a single file outside `make` (e.g. to check a warning), reproduce these
flags rather than guessing at a plain `gcc file.c -o file`, or the local-header includes and
warning set won't match.

## Per-utility Makefile pattern

Every subdirectory's `Makefile` is a copy of the same template (only `SRCS` extension — `.c` vs
`.cpp` — and occasional extra `LDLIBS` differ):

- `BIN = $(notdir $(CURDIR))` — the binary name is always the directory name.
- `SRCS = $(wildcard *.c)` (or `*.cpp`) — each directory has exactly one source file compiled by
  the implicit pattern rule.
- `-MMD -MP` generate `.d` dependency files that are `-include`d for incremental rebuilds.
- `lint:` runs `clang-tidy --quiet $(SRCS) -- $(CPPFLAGS) $(CFLAGS|CXXFLAGS)`, using the same
  `.clang-tidy` config at the top of this directory for every utility.
- One utility adds its own `LDLIBS`: `isprime` links GMP via `pkg-config --libs gmpxx`.

When adding a new utility, copy an existing Makefile of the matching language (C: e.g.
`durfmt/Makefile`; C++: e.g. `dir_is_empty/Makefile`) rather than writing one from scratch — the
convention is load-bearing (top-level `make`/`make lint`/etc. depend on every subdir following
it).

## Code conventions

These are small, self-contained CLI tools reading from stdin/argv and writing to stdout, following
consistent conventions worth matching in new code:

- SPDX header on every file: `// SPDX-FileCopyrightText: Steven Ward` /
  `// SPDX-License-Identifier: MPL-2.0`.
- Programs that take options define `program_author`/`program_version`/`program_license`
  constants and `print_version()`/`print_usage()` functions, parsed via `getopt` with a
  `"+:..."` short-option string (`-V` version, `-h` help are near-universal). Usage text lists
  `OPTIONS` (and sometimes `SEE ALSO`) in a fixed style — see `cmeter/cmeter.c` or
  `cpuavgd/cpuavgd.c` for the fullest examples.
- C sources use modern C (`constexpr`, `nullptr`, `[[maybe_unused]]`) via the pinned
  `-std=gnu2y`; C++ sources target `-std=gnu++26`.
- Exit codes follow the Unix convention (0 success / boolean-true, 1 failure /
  boolean-false), e.g. `as_bool` and `dir_is_empty` are predicates meant for use in shell
  conditionals.

## Daemon utilities (`cpuavgd`, `netrxavgd`, `nettxavgd`)

These three share one design, factored by copy-paste rather than a shared source file:
continuously sample a `/proc` or `/sys` metric (CPU idle ticks, network rx/tx byte counters) at a
configurable interval (`-i MSEC`), compute a rate/ratio since the last sample, and either `puts()`
it to stdout or atomically rewrite a `-f FILE` destination file each tick (used for shoveling a
live value into something like a status bar). They share:

- `SIGALRM`-driven sampling via `setitimer`, with `sigsuspend` idling between ticks.
- `SIGUSR1`/`SIGUSR2` to force an alarm/interval reset; any other terminating signal sets a
  `done` flag, and an `atexit` handler removes the `-f` destination file on clean exit.
- The local headers noted above (`acfile.h` for scope-guarded `FILE*`, `pscanf.h` for scanf'ing a
  file by path, `strtou.h`, `timeval.h`/`timespec.h`) that live outside this repo in
  `link/.local/include/` — see the build-environment note above before touching these.

`netrxavgd`/`nettxavgd` are near-identical (rx vs tx byte counter from
`/sys/class/net/<iface>/statistics/{rx,tx}_bytes`); when fixing a bug in one, check whether the
same bug exists in the other.
