# Pivot Chunk 01 — Resolve the AGENT.md / AGENTS.md Duplication

## Why this chunk exists and why it goes first

HappyPaddleShifterCo is starting a structural pivot: the agent scaffolding was built
assuming the controller would always be an Arduino-family board (Uno/Mega/Nano). The
project now wants the scaffolding generalized so a future non-Arduino controller board
(ARM-based or otherwise) would not require rebuilding the scaffolding from scratch.

This is chunk 1 of a sequence. It is being done first because every later chunk in
this sequence touches files that currently exist in duplicate: each role folder
(`.agents/agents/{coding,documentation,research}/`) has both `AGENT.md` (singular)
and `AGENTS.md` (plural), and they have drifted from each other before. If this
duplication isn't resolved first, every later rename/reword chunk has to edit the
same content twice and re-sync two files, doubling the work and doubling the chance
of reintroducing drift.

Do not start chunk 02 until this chunk is fully resolved and committed.

## Background you need to load

Read these before doing anything else:

1. `CLAUDE.md` (repo root) — project overview and the "Critical Rules" section.
2. `.agents/WORKFLOW.md` — how the three roles collaborate, ownership rules.
3. `.agents/HANDOFFS.md` — specifically the **Escalations Awaiting Human Input**
   section, entry titled `[RESOLVED 2026-08-19] — Duplicate, diverging role-config
   files: AGENT.md vs AGENTS.md per role`. This is the prior attempt at this problem.
   Read the full history including the original `[ESCALATION NEEDED]` text kept below
   it — it explains why AGENTS.md exists at all (a second consuming tool, referred to
   as "Pi", is routed to it by `humans/start-*-role.md`) and why it wasn't just deleted
   last time.
4. `humans/start-coding-role.md`, `humans/start-documentation-role.md`,
   `humans/start-research-role.md` — see exactly how each routes readers to
   `AGENT.md` vs `AGENTS.md`.
5. Diff `AGENT.md` against `AGENTS.md` in each of the three role folders
   (`.agents/agents/coding/`, `.agents/agents/documentation/`,
   `.agents/agents/research/`) to see current drift, if any.

## The actual decision to make

Last time this was escalated, the resolution was "sync content, don't delete" — but
the human operator flagged that the dual-file-drift risk itself was NOT eliminated,
just patched. That's the open question you're here to close out, now that a bigger
structural pivot is starting anyway.

You have at least three real options:
- **Keep both files, formalize the sync.** E.g., make `AGENTS.md` a thin file that
  says "see AGENT.md for full content" plus only the bits Pi-specific tooling
  actually needs, rather than a full parallel copy.
- **Merge into one file** if the "Pi" tool consuming `AGENTS.md` doesn't actually
  need a separate document — investigate what `humans/start-*-role.md` says Pi
  needs before assuming this is safe.
- **Keep both as genuinely independent full documents**, but add something
  mechanical (a checklist step in `WORKFLOW.md`, a note in each file pointing at
  its sibling) that makes it hard to edit one without noticing the other exists.

## You are not confident enough to decide this alone — ask

You do not have visibility into what the "Pi" tool actually requires from
`AGENTS.md`, or whether the human operator still uses it. This is exactly the kind
of decision the project's own rules reserve for a human: `HANDOFFS.md` already
flagged this once as needing a human decision, not a role fixing content
unilaterally, and root-level scaffolding files aren't owned by any of the three
roles.

**Before making any file changes, ask the human operator:**
1. Is the "Pi" tool still in use, and does it genuinely require a separate
   `AGENTS.md` file, or would it tolerate reading `AGENT.md`?
2. Given the options above (or any other option you've identified), which approach
   do they want?

Use whatever question-asking mechanism is available to you in this session. If none
is available, stop and write your questions clearly at the end of your output rather
than guessing and proceeding.

## Once you have an answer

1. Implement the chosen approach across all three role folders consistently — don't
   solve it differently per role.
2. Update `humans/start-*-role.md` if the routing changes.
3. Update the `[RESOLVED 2026-08-19]` entry in `.agents/HANDOFFS.md` (or add a new
   entry immediately after it) recording the final decision and why, so this doesn't
   get re-litigated a third time.
4. Commit directly to the current branch (per `CLAUDE.md` Critical Rule #1 — never
   work on a new branch). Do not force-push or use destructive git operations.
5. Leave a short note at the end of your output confirming this chunk is done and
   chunk 02 (`02-rename-vendor-scoped-folders.md`) can start.

## Guardrails

- Don't touch `ArduinoCode/`, `.agents/knowledge/arduino/`, or any board/firmware
  content in this chunk — that's chunks 02–04. Stay scoped to the AGENT.md/AGENTS.md
  question only.
- Don't add speculative multi-board abstractions (interfaces, `#ifdef` scaffolding,
  etc.) — this pivot is about agent/doc scaffolding, not firmware architecture, and
  premature firmware abstraction is out of scope here.
- If you find anything else drifted or wrong while diffing the files, don't fix it
  silently — note it and ask, or drop a `[PENDING]` HANDOFFS entry for the owning
  role rather than editing content outside this chunk's scope.
