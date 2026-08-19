# Pivot Chunk 04 — Generalize Root Project Identity

## Why this chunk exists

Final chunk in the sequence generalizing HappyPaddleShifterCo's agent scaffolding so
a future non-Arduino controller board won't require rebuilding the scaffolding. See
`humans/multi-controller-pivot/01-resolve-agent-agents-duplication.md` for the full
background. **Do not start this chunk until chunk 03 is committed** — confirm via
`.agents/DECISIONS.md`.

The root `CLAUDE.md` and root `AGENTS.md` both currently describe the project's
identity itself in Arduino-specific terms — not as an implementation detail buried in
a role file, but in the very first paragraph every agent (any role, any tool) reads
before anything else. Paraphrased, the current framing is: *"Steering-wheel paddles
replace the factory TCU. The driver controls gear selection directly; an Arduino
board (Uno — default — Mega 2560, or Nano, all supported) reads the selector
position, the paddles, and drives the transmission solenoids accordingly."*

This is the last and most sensitive piece: it's root-level, read first, and — per the
existing `.agents/HANDOFFS.md` history — outside any single role's normal write
authority. It was explicitly flagged once before and left untouched for exactly that
reason. This chunk exists to finally close that out, now that chunks 01–03 have done
the supporting structural work underneath it.

## Background you need to load

1. `CLAUDE.md` (repo root) — the file you're primarily editing. Read it in full,
   not just the opening section — check for other Arduino-specific identity
   statements later in the file (e.g. in the folder-structure diagram, Critical
   Rules).
2. `AGENTS.md` (repo root) — the "Pi" tool's equivalent entry point. Check whether
   chunk 01's resolution merged this with `CLAUDE.md`'s content or kept it separate;
   edit accordingly.
3. `.agents/HANDOFFS.md` — search for the prior note (in the "Update all board docs"
   `[DONE]` entry) explaining why root `CLAUDE.md`/`AGENTS.md` were left untouched
   during the earlier Uno-default rollout: *"Neither file is in the documentation
   role's ownership table... CLAUDE.md in particular sits outside all three agent
   roles' normal write scope."* You are the resolution to that flag.
4. `.agents/DECISIONS.md` — read the entries chunks 01–03 added, plus ADR-008/009/010,
   to make sure your root-level wording stays consistent with what those chunks
   already established (final folder names, final role framing, current board list).
5. `README.md` (repo root, documentation-role-owned) — check whether it has similar
   root-identity wording that should stay consistent with what you write here, even
   though you're not the owner of that file (don't edit it — just don't contradict
   it; flag a HANDOFF to documentation if you find it's now inconsistent).

## The actual work

Reword the project identity description so it describes the product — a
paddle-shifter transmission controller — without hardcoding a specific controller
vendor/family as inherent to what the product *is*. Something in the direction of:
*"...a microcontroller reads the selector position, the paddles, and drives the
transmission solenoids accordingly. The project currently targets Arduino-family
boards (Uno default, Mega 2560 or Nano supported) — see
`.agents/knowledge/<renamed-controller-folder>/` for board specifics."* — but don't
just copy that sentence verbatim; write it to fit the surrounding document's voice,
and confirm the renamed knowledge folder path from chunk 02 before citing it.

Also check and update, if present:
- The Agent Roles table's one-line description of the coding role (currently
  "Arduino firmware — `.ino`, `.h`, `.cpp` files") — align with chunk 03's reframing.
- Any folder-structure diagram in `CLAUDE.md` that labels `ArduinoCode/` or
  `.agents/knowledge/arduino/` — update to match chunk 02's renamed paths.
- The Critical Rules section — check rule wording doesn't assume Arduino
  specifically where it's actually a general hardware-safety rule (e.g. "Solenoids
  are not driven directly from Arduino pins" — the *principle* applies to any MCU's
  GPIO, not just Arduino's).

## Where you're not confident — ask

This is root-level, first-read-by-everyone content with no natural owner among the
three roles. Treat your confidence bar here as higher than the earlier chunks:

- **Before writing anything**, propose your reworded paragraph(s) to the human
  operator and get explicit confirmation before committing — don't just ask about
  ambiguous cases, ask about the whole rewrite, since this file sets the tone every
  future session reads first. Use whatever question-asking mechanism is available
  in this session; if none is available, write your proposed wording clearly at the
  end of your output and stop rather than committing unreviewed root-doc changes.
- If you find the root `README.md` (documentation-owned, not yours to edit) is now
  inconsistent with your changes, don't edit it — drop a `[PENDING]` HANDOFFS entry
  to documentation describing exactly what's inconsistent and why.
- If wording chunk 03 used for the coding role's identity doesn't obviously extend
  to root-doc phrasing (different audience — root docs are read by every role,
  including non-coding ones), don't force a mechanical copy-paste; ask if unsure
  which framing fits better at root level.

## When done

1. Get explicit human confirmation on the proposed wording before committing (see
   above) — this is the one chunk in the sequence where that's required before, not
   after, the edit.
2. Commit directly to the current branch (never a new branch, per `CLAUDE.md`
   Critical Rule #1).
3. Add a closing entry to `.agents/DECISIONS.md` (or update the chunk 01–03 entries
   into one consolidated record) noting the full multi-controller-pivot sequence is
   complete, with a one-line summary of what changed at each step and pointers to
   the four chunk files in `humans/multi-controller-pivot/` for full detail.
4. Resolve any `[PENDING]` HANDOFFS entries this sequence created (e.g. the
   documentation-role README consistency flag, if raised) don't leave them dangling.
5. Leave a note confirming the full pivot sequence (chunks 01–04) is complete.

## Guardrails

- This is the smallest chunk by diff size but the highest-visibility one — don't
  rush it because it looks simple. Get confirmation before committing, per above.
- Don't touch anything in `ArduinoCode/` (or its renamed equivalent),
  `.agents/agents/*/context/`, or knowledge-base content in this chunk — that's all
  handled by chunks 02–03. This chunk is root-doc wording only.
- Don't commit the project to naming or supporting any specific non-Arduino board.
  The pivot is about scaffolding flexibility, not a hardware decision — keep the
  wording as "currently Arduino-family, structured so that could change" rather than
  implying a specific future board is planned.
