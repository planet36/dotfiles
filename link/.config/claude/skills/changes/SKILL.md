---
name: changes
description: Review the committed changes since (and including) a given commit — bugs, inconsistencies, and documentation left stale
argument-hint: <commit> | <N>
disable-model-invocation: true
---

# Review recent changes

## 1. Determine the range

The range is inclusive, so the named commit is reviewed along with everything after it.

Try $ARGUMENTS as a commit first, with `git rev-parse --verify --quiet '<arg>^{commit}'`.  A
short hash can be all digits, so do this even when $ARGUMENTS looks like an integer.

- If $ARGUMENTS is empty, ask the user for the starting commit.  Do not guess one.
- If it resolves to a commit and is not a plain integer, the range is `<ref>^..HEAD`.
- If it is a plain integer N that does not resolve, the range is the last N commits,
  `HEAD~N..HEAD`.
- If it is a plain integer that also resolves to a commit, ask the user which was meant.  When
  N exceeds the number of commits in the history, it can only be the commit.

If `<ref>` is a root commit, `<ref>^` does not exist, so use the empty tree
(`git hash-object -t tree /dev/null`) in its place.  If `HEAD~N` does not exist, review the
whole history.

Run `git log --oneline <range>` to list the commits in scope.  If there are none, say so and
stop.

## 2. Committed content only

Review what is committed, never the working tree.

- Get the changed paths from `git diff --name-status <range>`, and the changes themselves from
  `git log -p <range>` or `git diff <range>`.
- Read each file's committed state with `git show HEAD:<path>`, not with the Read tool, because
  the working copy may carry uncommitted edits.  Do not rely on cached content.
- Ignore untracked files and uncommitted changes entirely.  Do not review them, report them, or
  let them color a finding.

## 3. Skip externally controlled files

Do not review files that are copied from, or controlled by, an external repo or upstream
project.  These sources identify them.

- The project's CLAUDE.md files, root and nested, and memory may name vendored files or files
  synced from other repos.
- A commit message in the range may say "Sync with <repo>" or "Update from upstream."
- A file header may name another author, license, or upstream source.

A change to such a file is still worth one check, which is whether a file in this repo that
consumes it needs to follow.

Also skip binary files and generated output.  For generated output, check only that a generator
changed in the range had its output regenerated in the range too.

## 4. Review

Scope the review to what the range changed.  Read the surrounding code for context, but do not
audit untouched code, because `/review` and `/review-py` exist for whole-file audits.

Look for the following kinds of problem in each remaining file.  Each heading is also a group in
the report.

### Bugs

- Broken edge cases, wrong error paths, and behavior changes the commit message does not
  account for.
- In C and C++, a memory leak, meaning an allocation without a matching release on every path,
  including error branches.
- In Python, a bare `except:` or overly broad exception handling, a resource opened without
  `with`, or a mutable default argument.
- In shell, an unquoted expansion that splits or globs, including one inside `[ ]`, or a path
  argument with no `--` before it.

### Inconsistencies

- The change against the rest of the file and the repo, such as naming, parameter ordering,
  return conventions, and the conventions in CLAUDE.md.
- Sibling files that do the same thing but were not updated to match.
- Changed comments and doc blocks, and the commit messages in the range, checked against the
  repo's prose style guide, such as COMMENT-STYLE.md, if it has one.
- In C and C++, `constexpr` and `noexcept` opportunities where the types involved permit them.
- In Python, missing or wrong type hints, and dead code or needless complexity where a modern
  idiom would be clearer.

### Security

- Shell injection built from caller-supplied data, through `shell=True`, `os.system`, or an
  unquoted shell expansion.
- Unsafe deserialization.
- Predictable temp files.
- Path traversal.
- Buffer overflows, out-of-bounds access, unsafe C functions such as `strcpy`, `sprintf`, and
  `gets`, and integer overflow in size calculations.
- A weak cryptographic primitive or RNG where it matters.

### Performance

- Unnecessary copies, including a copy where a reference or `std::move` would do.
- Expensive work inside a loop that could be hoisted out of it.
- Allocations that could be avoided, including a missing `reserve()` on a container that grows
  incrementally.
- Repeated I/O or subprocess calls that could be batched.

### Loose ends

- References to removed or renamed files, functions, options, or variables that survive
  elsewhere in the repo.  Grep the committed tree with `git grep <pattern> HEAD` to confirm.
- In C and C++, an `#include` nothing uses, or a symbol used without including its header.

### Documentation to update

- README files, CLAUDE.md files, doc comments, `-h` help text, usage strings, and comments that
  no longer match the committed behavior.  Include documentation outside the changed files.
  Report these even when the code itself is fine.
- In C and C++, a doc comment whose `\param`, `\return`, or `\pre` no longer matches the
  signature or behavior.

### Ground rules

Do not flag a TODO comment as unfinished work.

Do not manufacture concerns.  Honor inline suppressions (`# noqa`, `# pylint: disable=`,
`// NOLINT`) and anything memory marks as intentional.

If CLAUDE.md names a verification command for a changed file type, such as `shellcheck` for a
shell script, it may be run.  Run it only when that file has no uncommitted changes, which
`git status --short <path>` shows, since the tools read the working tree.

## 5. Report

Start with the scope.

- The range and the commits in it, as `git log --oneline` prints them.
- The files reviewed.
- The files skipped, each with its reason, such as external, generated, or binary.

Then list the findings under the step 4 headings, in that order, omitting any empty group.  For
each finding, give `path:line` for the line in the committed file, the commit that introduced it
when that helps, the problem, and a suggested fix.  If nothing survives, say so plainly.

Present the report before making any changes.  Wait for confirmation before applying fixes, and
never commit unless asked.
