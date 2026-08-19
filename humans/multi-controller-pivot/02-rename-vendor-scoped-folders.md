# Pivot Chunk 02 — Rename Vendor-Scoped Folders

## Why this chunk exists

Part of a sequence generalizing HappyPaddleShifterCo's agent scaffolding so a future
non-Arduino controller board (ARM-based or otherwise) won't require rebuilding the
scaffolding. See `humans/multi-controller-pivot/01-resolve-agent-agents-duplication.md`
for the full background — **do not start this chunk until chunk 01 is committed.**
Confirm by checking `.agents/HANDOFFS.md` for the chunk 01 resolution note before
proceeding.

Two directories in this repo are named after the Arduino vendor/platform rather than
their function:

- `ArduinoCode/` (repo root) — contains the firmware source (`.ino`, `.h`, `.cpp`)
  and `SYSTEM.md`.
- `.agents/knowledge/arduino/` — contains board comparison, pin reference, and driver
  board knowledge. Most of the content here is already fairly board-agnostic
  (relay/driver wiring, SPI pin tables per board) — it's the folder *name* that's
  vendor-scoped, not necessarily all the content.

If a future controller board isn't an Arduino at all, both names actively mislead:
a future agent (or human) would look at `ArduinoCode/` and `knowledge/arduino/` and
reasonably assume neither applies to their non-Arduino work, even where the content
underneath is generic and reusable.

## Background you need to load

1. `CLAUDE.md` (repo root) — project overview, folder structure, Critical Rules.
2. `.agents/WORKFLOW.md` — the "Which Role Owns What" and "Knowledge Base Ownership"
   tables. Both currently hardcode the paths you're about to change.
3. `.agents/DECISIONS.md` — read in full, especially ADR-006 through ADR-010, to
   understand what's currently board-specific vs already board-general in the
   content you're moving. You are renaming folders, not rewriting their content in
   this chunk — but you need to know what's in them.
4. `.agents/knowledge/README.md` and `.agents/knowledge/arduino/README.md` — current
   structure documentation for the folder you're renaming.
5. Grep the whole repo for `ArduinoCode/` and `knowledge/arduino` (or
   `arduino/board-comparison`, `arduino/pin-reference`, `arduino/driver-boards`) to
   find every reference before you start. Expect hits in: `CLAUDE.md`, `AGENTS.md`,
   `.agents/WORKFLOW.md`, all three roles' `AGENT.md` (and `AGENTS.md` if chunk 01
   kept it), role `context/` files, `.agents/skills/*/SKILL.md`,
   `.agents/knowledge/**`, `humans/start-*-role.md`, `scripts/generate_bom.py`,
   `README.md`, `Schematics/README.md`, `Models/README.md`. Treat this list as a
   starting point, not the full list — the grep is the source of truth.

## What to actually do

1. **Don't guess the target names yourself — ask first.** You have candidate names
   (e.g. `ArduinoCode/` → `Firmware/`, `.agents/knowledge/arduino/` →
   `.agents/knowledge/controller/`), but naming is a low-reversibility choice that
   ripples through the whole repo and every future session's muscle memory. Before
   renaming anything, ask the human operator to confirm or supply the target names
   for both directories. Use whatever question-asking mechanism is available in this
   session; if none is available, stop and list your proposed names clearly at the
   end of your output instead of proceeding on a guess.
2. Once confirmed, rename both directories using `git mv` (not delete-and-recreate)
   so history is preserved.
3. Update every reference you found in the grep sweep, including this file's own
   sibling chunks if they mention the old paths (they currently do, by design — see
   the Guardrails note below).
4. Re-run the grep for the old path strings after your edits to confirm nothing was
   missed. Also check `scripts/generate_bom.py` actually runs against the new paths
   if it reads from them at generation time (don't just fix string literals blindly —
   confirm the script still functions).
5. Update `.agents/knowledge/README.md` and the renamed folder's own `README.md` to
   reflect the new path in their own prose, not just external references to it.

## Where you're not confident — ask

- If you find a reference to the old paths in a file that seems to belong to a role
  that isn't "yours" to edit in this cross-cutting chunk (e.g. content clearly owned
  per `.agents/WORKFLOW.md`'s ownership tables), you may still fix the path — this
  pivot work is explicitly cross-cutting structural work, not a normal role task —
  but if the surrounding content looks like it needs more than a path-string fix
  (e.g. prose that assumes the old name in a way a simple substitution would make
  awkward or wrong), stop and ask rather than rewriting prose you're not confident
  about. Path fixes are safe to make directly; prose judgment calls are not this
  chunk's job (that's chunks 03/04).
- If the grep turns up a reference in a file outside `.agents/`, `ArduinoCode/`,
  `humans/`, or root docs that you don't recognize the purpose of, ask before editing
  it.

## When done

1. Commit directly to the current branch (never a new branch, per `CLAUDE.md`
   Critical Rule #1).
2. Add a short entry to `.agents/DECISIONS.md` recording the rename (folder name,
   old path, new path, date, one-line reason) so future sessions understand why the
   paths changed if they hit stale references anywhere this sweep missed.
3. Leave a note confirming chunk 02 is done and chunk 03
   (`03-reframe-coding-role-identity.md`) can start.

## Guardrails

- This chunk is a **rename and reference-fix pass only**. Do not rewrite the
  Arduino-specific prose inside these folders to be more generic — that's chunk 03
  (role identity) and chunk 04 (root docs). If you're touching a sentence and it
  would be trivial to generalize it while you're in there, resist — keep this chunk's
  diff mechanically reviewable (a rename), not mixed with judgment-call rewording.
- Don't touch `AGENT.md`/`AGENTS.md` structure itself beyond fixing path references
  inside them — chunk 01 already resolved that question; don't reopen it.
- These prompt files in `humans/multi-controller-pivot/` reference the old paths
  intentionally (they were written before this chunk ran) — update this chunk's own
  file and the later chunk files' path references if needed so the sequence stays
  internally consistent, but don't renumber or restructure the sequence itself.
