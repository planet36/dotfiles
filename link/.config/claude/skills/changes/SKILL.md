---
name: changes
description: Summarize recent git commits — what changed, why, and anything notable
argument-hint: [<since-ref>]
disable-model-invocation: true
---

Determine the commit range:
- If $ARGUMENTS is a commit hash, branch name, or tag: use `<ref>..HEAD`.
- If $ARGUMENTS is a plain integer N: use the last N commits (`HEAD~N..HEAD`).
- If $ARGUMENTS is empty: use the last 20 commits (`HEAD~20..HEAD`).

Run `git log --oneline <range>` to list commits in scope. If there are none, say so and stop.

Run `git diff <range> --name-only` to get the list of changed files. Re-read each changed source file fresh — do not rely on cached content. Skip binary files, generated files, and vendored/third-party files.

Write a short summary covering:

1. **What changed** — per file or logical area, with the nature of the change (new feature, fix, refactor, docs, etc.).

2. **Why** — inferred from commit messages and the diff. Skip this if it's obvious from the commit message alone.

3. **Anything notable** — API changes, behavioral differences, non-obvious decisions, incomplete work, or inconsistencies worth flagging.

Keep findings tight — one to three sentences per file or logical area. Do not manufacture concerns. Flag real issues only.
