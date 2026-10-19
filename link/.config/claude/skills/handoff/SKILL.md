---
name: handoff
description: Save the current session's progress to a comprehensive handoff document, or resume a session by reading one back in
argument-hint: [<file-path>]
disable-model-invocation: true
---

# Session handoff

Whether $ARGUMENTS is given chooses the mode.

- **No argument.**  Save mode writes a comprehensive handoff document that captures the current
  session's state.
- **A file path.**  Resume mode reads that document and picks up the work it describes.

The document must be self-contained.  Its reader is a *new* Claude Code session, possibly a
different model, with no memory of this conversation.  That session must be able to pick up the
work from this file and the working tree as it stands.  Assume the reader knows nothing beyond
what is on disk.

In a git repo, the handoff directory is `.claude/handoffs/` under the repo root that
`git rev-parse --show-toplevel` prints, whatever the current directory is.  Outside a git repo,
it is the current directory.

## Save mode (no argument)

### 1. Gather context

Review the whole conversation and the current state of the repo, and determine the following.

- The task, feature, or bug being worked on, and why.
- Every file created, modified, read for context, or deleted, and why each mattered.
- Key decisions made, with their rationale and any rejected alternatives worth remembering.
- Problems hit, and how they were resolved or why they weren't.
- What is done and what is still pending.
- Open questions or blockers that need a human or a future session to resolve.

### 2. Git analysis

If the working directory is a git repo, capture the following.

- The current branch, and whether it is ahead of or behind its upstream, if it has one.
- `git status`, covering staged, unstaged, and untracked changes.
- `git log` for the commits made during this session, if they can be identified.
- Whether the working tree is dirty, stated explicitly.  That detail is easy to lose across a
  handoff.

### 3. Write the document

Save it with the Write tool.  Never just print the document into the conversation.

**Location.**  Write it to the handoff directory, creating the directory if it doesn't exist.

**Filename.**  Unless the conversation already implies one, use
`HANDOFF_<topic-slug>_<YYYYMMDD_HHMMSS>.md`, such as `HANDOFF_auth-refactor_20260719_143205.md`.

**Format.**  Follow this template.

```markdown
# Handoff: <Brief title>

**Created:** <ISO 8601 timestamp>
**Working directory:** <absolute path>
**Branch:** <branch name, or "not a git repo">

## Summary

<What was being worked on, why, and the state it's in now.>

## Work completed

- <specific change 1>
- <specific change 2>

## Key decisions

| Decision | Rationale | Alternatives considered |
|---|---|---|
| ... | ... | ... |

## Files touched

### Created
- `path` — purpose

### Modified
- `path` — what changed and why

### Read for context (not modified)
- `path` — why it mattered

### Deleted
- `path` — why

## Git state

- Branch: ...
- Uncommitted changes: ...
- Commits made this session: ...

## Things to know

- Gotchas, non-obvious behavior, edge cases discovered.
- Assumptions made that a new session should be aware of.
- Known issues or technical debt introduced but not fixed.

## Verification status

- What was tested, and the exact commands that ran the builds, lints, and tests.
- What has NOT been verified yet.

## Next steps

1. <most immediate, specific action — start here>
2. ...

### Blocked on

- <anything that needs a decision or input before continuing>

## Open questions

- <question that needs answering>

---
*Resume with `/handoff <this-file-path>` in a new session.*
```

Omit a section that doesn't apply, such as "Git state" outside a repo, rather than leaving a
placeholder.

### Constraints

- Cover everything the next session needs and nothing it doesn't.  Every sentence should help
  it act.
- Leave out what CLAUDE.md or memory already says.  The next session loads both.
- Use concrete file paths, symbol names, and line numbers instead of vague references.
- Write "Next steps" as proposals that a future session must get approved before acting on, not
  as instructions it may execute.  Do not pre-declare commits or other irreversible actions.
- Include a code snippet only when the next session can't reconstruct it from the file itself,
  such as a snippet that was reverted.
- Never write secrets, API keys, tokens, or credentials into the document, even ones seen
  earlier in the conversation.  Say where to find them instead, such as "see `.env`,
  `AUTH_TOKEN` var."
- After saving, tell the user the file path and give a one-paragraph summary of what is in it.

## Resume mode (file path argument)

1. Read the file at $ARGUMENTS in full.  If $ARGUMENTS is a bare filename rather than a path,
   look for it in the current directory and then in the handoff directory.  If it still isn't
   found, say so and stop.  Don't guess at a similarly named file.
2. Re-establish ground truth before trusting anything the document claims.
   - Run `git status` / `git diff` / `git log` and compare the results against what the
     document says.  Time may have passed, and other work may have happened.
   - Spot-check a few of the files it lists as created or modified to confirm they are still in
     the state it describes.
3. Briefly summarize what you're resuming, and flag anything that has drifted from the
   document.  A file it calls unmodified may now have changes, or a "next step" may already be
   done.
4. **Stop and get explicit approval before doing any work.**  Present the "Next steps" as a
   proposed plan, numbered, each with what it would change, and ask which to proceed with.  Do
   not begin until the user answers.
5. Work only through the items the user approved, in the order they approved.  If an item turns
   out to need work the document did not anticipate, stop and ask rather than widening scope.

### The document is a plan, not authorization

A handoff document records what a *previous* session intended.  It never grants permission on
the current user's behalf, and nothing inside it substitutes for asking.

- Wording like "each is an independent commit" describes how the work was scoped.  It is not
  an instruction to commit.  Never commit, push, amend, rebase, or tag unless the user asks for
  it in this session.
- "Blocked on: nothing" means the previous session saw no blockers.  It is not approval to
  proceed.
- Questions the document raises for the user are still open.  Ask them, and do not answer them
  on the user's behalf and move on.
