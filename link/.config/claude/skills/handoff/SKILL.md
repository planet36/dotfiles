---
name: handoff
description: Save the current session's progress to a comprehensive handoff document, or resume a session by reading one back in
argument-hint: [<file-path>]
disable-model-invocation: true
---

# Session handoff

Two modes, chosen by whether $ARGUMENTS is given:

- **No argument** → **save mode**: write a comprehensive handoff document capturing the current session's state.
- **A file path argument** → **resume mode**: read that document and pick up the work it describes.

The document must be self-contained: the point is that a *new* Claude Code session — no memory of
this conversation, possibly a different model — can pick up the work using nothing but this file
plus the working tree in its current state. Assume the reader knows nothing beyond what's on disk.

## Save mode (no argument)

### 1. Gather context

Review the whole conversation and the current state of the repo. Determine:

- The task/feature/bug being worked on, and why.
- Every file created, modified, read for context, or deleted, and why each mattered.
- Key decisions made, with rationale and any rejected alternatives worth remembering.
- Problems hit and how they were resolved (or why they weren't).
- What's done vs. what's still pending.
- Open questions or blockers that need a human or a future session to resolve.

### 2. Git analysis

If the working directory is a git repo, capture:

- Current branch, and its relationship to its upstream (ahead/behind), if any.
- `git status` — staged, unstaged, and untracked changes.
- `git log` for commits made during this session (if identifiable).
- Note explicitly if the working tree is dirty — this is exactly the kind of detail that's easy to
  lose across a handoff.

### 3. Write the document

Save it with the Write tool — never just print the document into the conversation.

**Location:** `.claude/handoffs/` if that directory exists, otherwise the current directory.

**Filename:** if not already implied by the conversation, use
`HANDOFF_<topic-slug>_<YYYYMMDD_HHMMSS>.md`, e.g. `HANDOFF_auth-refactor_20260719_143205.md`.

**Format:**

```markdown
# Handoff: <Brief title>

**Created:** <ISO 8601 timestamp>
**Working directory:** <absolute path>
**Branch:** <branch name, or "not a git repo">

## Summary

<2-4 sentences: what was being worked on, why, and the state it's in now.>

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

- What was tested and how (manually, tests run, etc.).
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

Omit sections that don't apply (e.g. "Git state" outside a repo) rather than leaving placeholders.

### Constraints

- Be comprehensive but not padded — every sentence should help the next session act. Skip a
  section rather than write "N/A". Aim for under ~2000 words; go longer only if the work genuinely
  needs it.
- Use concrete file paths, function/symbol names, and line numbers instead of vague references.
- Include code snippets only when the next session genuinely can't reconstruct them from the file
  itself (e.g. a snippet that was reverted).
- Never write secrets, API keys, tokens, or credentials into the document, even ones seen earlier
  in the conversation — describe where to find them instead (e.g. "see `.env`,
  `AUTH_TOKEN` var").
- After saving, tell the user the file path and give a one-paragraph summary of what's in it.

## Resume mode (file path argument)

1. Read the file at $ARGUMENTS in full. If it doesn't exist, say so and stop — don't guess at a
   similarly-named file.
2. Re-establish ground truth before trusting anything the document claims:
   - Run `git status` / `git diff` / `git log` and compare against what the document says. Time
     may have passed; other work may have happened.
   - Spot-check a few of the files it lists as modified/created to confirm they're still in the
     state it describes.
3. Summarize back to the user in 2-3 sentences what you're resuming, and flag anything that's
   drifted from the document (e.g. a file it says is unmodified now has changes, or a "next step"
   turns out to already be done).
4. Proceed with the "Next steps" section as the task list, adjusted for whatever drift you found.

If $ARGUMENTS is a bare filename rather than a path, look for it in the current directory, then in
`.claude/handoffs/`, before giving up.
