---
name: review-py
description: Review Python (.py) files for correctness, type safety, maintainability, performance, security, and documentation, using the repo's linters as a baseline
argument-hint: <file-path>...
disable-model-invocation: true
---

# Python review

## Workflow

If $ARGUMENTS is empty, ask the user which files to review, and wait for the answer.

Re-read each file in $ARGUMENTS before doing anything else.  Do not rely on any cached content.

Check CLAUDE.md and memory before reviewing.  Skip a vendored file, or report a defect in one as a fix to make upstream.  Do not re-raise anything memory marks as intentional.

Before reading the code, run the repo's checks on each file where they are installed, and use their output as the baseline for the review.

- Run `ruff check`, `mypy --ignore-missing-imports`, and `pylint`, and `pytest` if the project has a test suite.
- Run a script, at least with `-h`, to confirm that it starts.
- Respect existing inline `# pylint: disable=` and `# noqa` suppressions.  They mark known false positives, so do not re-raise them.

## What to look for

### 1. Correctness and type safety

- Logic errors, off-by-one errors, and input the code does not handle, such as an empty file, an empty string, or a missing argument.  Prove each one before reporting it, with a run that shows the wrong output.
- Missing or incorrect type hints, in `typing` or PEP 585 and PEP 604 syntax.
- A bare `except:` or overly broad exception handling.
- A resource opened without a `with` block.
- A mutable default argument, such as `def append_to(element, to=[])`.

### 2. Maintainability and conventions

- PEP 8 naming.  Take the line-length limit from the project and its linters, not PEP 8's 79 columns.
- The conventions in CLAUDE.md, such as the module-level metadata and the shape of `main()`.
- Dead code, overly complex nested logic, or redundant loops.

### 3. Performance and resource use

- Heavy I/O inside a loop.
- A large list built where a generator would do.
- Inefficient string concatenation or unnecessary copies of objects.

### 4. Security

Focus on the sinks that matter when data crosses a trust boundary.  For a script, that boundary is argv, the environment, and files.  For a library module, it is the arguments callers pass in, which the code cannot assume are trusted.

- **Shell injection.**  `subprocess(..., shell=True)` or `os.system(...)` with any argument built from a filename, a command-line or environment value, a function parameter, or other caller-supplied data.  Prefer a list argv with `shell=False`.
- **Unsafe deserialization.**  `pickle.load`, `yaml.load` without `SafeLoader`, or `marshal` on data the code did not itself produce.
- **Insecure temp files.**  `tempfile.mktemp()` or a hand-rolled, predictable `/tmp` path, which invites TOCTOU and symlink races.  Prefer `mkstemp` or `NamedTemporaryFile`.
- **Path traversal.**  An untrusted filename joined into a path without normalization, so that `../` escapes, or symlinks followed blindly.  Also `extractall` from `tarfile` or `zipfile` on an untrusted archive.
- **Code execution.**  `eval`, `exec`, or `compile` on data that is not literal.
- **Hardcoded secrets.**  A string in the code that is genuinely a credential.

Do not flag these when the command and all its arguments are fully literal, or when a hardcoded string is a default path or format rather than a secret.  A value from a function parameter is not literal.  In library code, treat it as potentially untrusted rather than waving it through.

### 5. Documentation

- A module docstring, `-h` text, or usage string that no longer matches the behavior.
- Any README or CLAUDE.md that documents the file and has gone stale.

## Report

Present the report before making any changes, structured as follows.

### Python review summary

- **Files reviewed.**  The list of files.
- **Overall status.**  Pass, Minor Issues, Major Issues, or Critical Issues, which is the highest severity found below.

### Detailed findings

Group the findings by severity, as **Critical**, **Major**, and **Minor**.  Give each finding the following.

1. **Location.**  The `path:line`.
2. **Problem.**  A short explanation of the underlying flaw.
3. **Fix.**  A clear, actionable explanation, or a concise diff showing the remedied code.

### Modernization suggestions

Where the code uses a legacy pattern that a newer Python feature clearly improves on, suggest the replacement.  Omit this section when there are none.

After presenting the report, wait for confirmation before applying any fixes.
