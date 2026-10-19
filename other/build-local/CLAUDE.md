# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this
directory.

## What this is

`other/build-local` holds small, independent C and C++ command-line utilities and daemons.
Each lives in its own directory with exactly one source file and a `Makefile`, and the binary
takes the directory's name.

## Building and verifying

Run these from this directory to act on every utility, or from one utility's directory to act
on that one alone.

```sh
make            # build
make clean      # remove what the build wrote
make lint       # run clang-tidy with the .clang-tidy in this directory
make install    # install to $DESTDIR$PREFIX/bin (PREFIX defaults to /usr/local)
make uninstall
```

The flags come from the environment, as the top-level CLAUDE.md describes.  The Makefiles add
only `-MMD -MP`, so a shell that has not sourced `envvars.bash` builds with the wrong standard
and warning set.  `cpuavgd`, `netrxavgd`, `nettxavgd`, and `printints` also include headers
from `link/.local/include/`, which only the `-iquote` in `CPPFLAGS` can find.  To compile one
file by hand, use `$CC $CPPFLAGS $CFLAGS` or `$CXX $CPPFLAGS $CXXFLAGS` rather than a bare
`gcc`.

There is no test suite.  A change is verified when it adds no compiler warning and no
clang-tidy diagnostic, and the program still behaves as its `-h` text says.  Neither check is
clean today, and neither one fails the command, so compare the output before and after the
change.  Fix the code rather than adding flags to a Makefile.

## The per-utility Makefile

Every utility's `Makefile` is a copy of one template.  The C and C++ versions differ only in the
source extension and in which compiler and flags they name, and `isprime` adds `LDLIBS` for GMP.
The top-level `Makefile` runs each goal in every subdirectory, so a new utility must support
`all`, `clean`, `install`, `uninstall`, and `lint`.  Start a new one from `durfmt/Makefile` for
C or `dir_is_empty/Makefile` for C++.

## Code conventions

- Every source file starts with the SPDX header, `// SPDX-FileCopyrightText: Steven Ward` and
  `// SPDX-License-Identifier: MPL-2.0`.
- A program that takes options defines `program_author`, `program_version`, and
  `program_license`, plus `print_version()` and `print_usage()`.  It parses options with
  `getopt` and a short-option string that starts with `"+:"`, and it always offers `-V` and
  `-h`.  The usage text has an `OPTIONS` section and sometimes a `SEE ALSO` section.
  `cpuavgd/cpuavgd.c` is the fullest example, and `isprime/isprime.cpp` shows `SEE ALSO`.
- C sources use C23 features such as `constexpr`, `nullptr`, and `[[maybe_unused]]`.
- `as_bool` and `dir_is_empty` are predicates for shell conditionals.  They exit 0 for true and
  1 for false.

## The daemons

`cpuavgd`, `netrxavgd`, and `nettxavgd` share one design by copy rather than by a shared source
file.  Each samples a counter in `/proc` or `/sys` every `-i MSEC` milliseconds and computes a
rate since the previous sample.  It prints the rate with `puts()`, or with `-f FILE` writes it
to a file that something like a status bar reads.

- `setitimer` raises `SIGALRM` for each sample, and the loop waits in `sigsuspend` between
  samples.
- `SIGUSR1` and `SIGUSR2` restart the timer.  `SIGHUP`, `SIGINT`, `SIGPIPE`, `SIGQUIT`, and
  `SIGTERM` set `done`, which ends the loop.
- The `atexit` handler removes the `-f` file only after one of those signals ends the loop.  An
  exit through `err()` leaves the file behind.
- The `-f` file is created with `O_CREAT | O_EXCL`, so it must not already exist.  The daemon
  keeps that descriptor open and rewrites the file in place each tick with `lseek`, `write`, and
  `ftruncate`.  Reopening the path instead would let the path be swapped for a symlink between
  writes.  The rewrite is not atomic, so a reader can see a short or empty value mid-write.

`netrxavgd` and `nettxavgd` differ only in reading `rx_bytes` or `tx_bytes` from
`/sys/class/net/<iface>/statistics/`.  A fix to one almost always belongs in the other.
