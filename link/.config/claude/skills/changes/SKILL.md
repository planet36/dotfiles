---
name: changes
description: Review the committed changes since (and including) a given commit — bugs, inconsistencies, and documentation left stale
argument-hint: <commit> | <N>
disable-model-invocation: true
---

# Review recent changes

## 1. Determine the range

The range is inclusive: the named commit is reviewed along with everything after it.

- If $ARGUMENTS is a commit hash, branch name, or tag: the range is `<ref>^..HEAD`.
  If `<ref>` is a root commit, `<ref>^` does not exist, so diff against the empty tree
  (`git hash-object -t tree /dev/null`) instead.
- If $ARGUMENTS is a plain integer N: the range is the last N commits (`HEAD~N..HEAD`).
- If $ARGUMENTS is empty: ask the user for the starting commit. Do not guess one.

Run `git log --oneline <range>` to list the commits in scope. If there are none, say so and stop.

## 2. Committed content only

Review what is committed, never the working tree.

- Get changed paths from `git diff --name-status <range>`, and the changes themselves from
  `git log -p <range>` or `git diff <range>`.
- Read each file's committed state with `git show HEAD:<path>`, not with the Read tool, because
  the working copy may carry uncommitted edits. Do not rely on cached content.
- Ignore untracked files and uncommitted changes entirely. Do not review them, report them, or
  let them color a finding.

## 3. Skip externally controlled files

Do not review files that are copied from, or controlled by, an external repo or upstream project.
Identify them from:

- the project's CLAUDE.md files (root and nested) and memory, which may name vendored files or
  files synced from other repos;
- commit messages in the range such as "Sync with <repo>" or "Update from upstream";
- file headers naming another author, license, or upstream source.

A change to such a file is still worth one check: whether a file in this repo that consumes it
needs to follow. Also skip binary files and generated output (review the generator instead).

## 4. Review

Scope the review to what the range changed. Read the surrounding code for context, but do not
audit untouched code; `/review` and `/review-py` exist for whole-file audits.

For each remaining file, look for:

- **Correctness** — bugs, broken edge cases, error paths, and behavior changes the commit message
  does not account for.
- **Consistency** — the change against the rest of the file and the repo: naming, parameter
  ordering, return conventions, conventions in CLAUDE.md, and sibling files that do the same
  thing but were not updated to match.
- **Security** — shell injection (`shell=True`, `os.system`, unquoted shell expansions) built from
  caller-supplied data; unsafe deserialization; predictable temp files; path traversal; buffer
  overflows, out-of-bounds access, unsafe C functions (`strcpy`, `sprintf`, `gets`), and integer
  overflow in size calculations; weak cryptographic primitives or RNG where it matters.
- **Performance** — unnecessary copies; expensive work inside a loop that could be hoisted out;
  allocations that could be avoided; repeated I/O or subprocess calls that could be batched.
- **Loose ends** — references to removed or renamed files, functions, options, or variables that
  survive elsewhere in the repo. Grep the committed tree (`git grep <pattern> HEAD`) to confirm.
- **Documentation to update** — README files, CLAUDE.md files, doc comments, `-h` help text, usage
  strings, and comments that no longer match the committed behavior. Include documentation outside
  the changed files. Report these even when the code itself is fine.

Language-specific checks, applied to the changed code:

- **C/C++** — memory leaks (allocations without a matching release on every path, including
  error branches); include audit (an `#include` nothing uses, or a symbol used without including
  its header); `constexpr` and `noexcept` opportunities, where the types involved permit them;
  copies where a reference or `std::move` would do; missing `reserve()` on containers that grow
  incrementally; doc comments whose `\param`, `\return`, or `\pre` no longer match the signature or behavior.
- **Python** — missing or wrong type hints; bare `except:` or overly broad exception handling;
  resources opened without `with`; mutable default arguments; dead code or needless complexity
  where a modern idiom would be clearer.

Do not flag a TODO comment as unfinished work.

Do not manufacture concerns. Honor inline suppressions (`# noqa`, `# pylint: disable=`,
`// NOLINT`) and anything memory marks as intentional. If CLAUDE.md names a verification command
for a changed file type, it may be run, but only when that file has no uncommitted changes (check
`git status --short <path>`), since the tools read the working tree.

## 5. Report

Start with the scope:

- the range and the commits in it (`git log --oneline` output);
- the files reviewed;
- the files skipped, each with the reason (external, generated, binary).

Then list findings grouped under **Bugs**, **Security**, **Performance**, **Inconsistencies**,
**Language-specific**, and **Documentation to update**, omitting any empty group. For each finding give `path:line` (the line in the committed file), the
commit that introduced it when that helps, the problem, and a suggested fix. If nothing survives,
say so plainly.

Present the report before making any changes. Wait for confirmation before applying fixes, and
never commit unless asked.
