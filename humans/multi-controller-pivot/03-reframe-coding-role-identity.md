# Pivot Chunk 03 — Reframe the Coding Role's Identity

## Why this chunk exists

Part of a sequence generalizing HappyPaddleShifterCo's agent scaffolding so a future
non-Arduino controller board won't require rebuilding the scaffolding. See
`humans/multi-controller-pivot/01-resolve-agent-agents-duplication.md` for the full
background. **Do not start this chunk until chunk 02 is committed** — confirm via
`.agents/DECISIONS.md` and `.agents/HANDOFFS.md` that the folder renames landed, and
use whatever the new folder names actually are (do not assume the names proposed in
earlier chunk files — read chunk 02's resolution to get the real final names).

The coding role today is defined by vendor and file extension, not by function. Its
`AGENT.md` frontmatter currently reads (paraphrased from the pre-pivot version):
*"Arduino firmware for HappyPaddleShifterCo... Owns all .ino, .h, and .cpp files."*
That framing means the role's own self-description — not just its content — assumes
an Arduino toolchain. A future non-Arduino board might use different file extensions,
a different build tool, or a different language entirely (e.g. PlatformIO project
layout, ESP-IDF, a different vendor's IDE). This chunk reframes the role's identity
around its function (firmware/controller-logic role) while keeping today's Arduino
specifics as clearly-labeled *current implementation* detail rather than baked-in
identity.

## Background you need to load

1. `CLAUDE.md` (repo root) — project overview, Agent Roles table, Critical Rules.
2. `.agents/WORKFLOW.md` — full file. Pay attention to the "Role Summary" table and
   "Which Role Owns What" — both describe the coding role's scope in vendor terms.
3. `.agents/agents/coding/AGENT.md` (and `AGENTS.md` if chunk 01 kept it as a
   separate file) — the file you're primarily reworking.
4. Every file in `.agents/agents/coding/context/` — `existing-classes.md`,
   `validation.md`, `class-reference.md`, `firmware-conventions.md`,
   `arduino-patterns.md`. Read all of them fully before editing any of them.
5. `.agents/DECISIONS.md` in full — several ADRs (e.g. ADR-002 solenoid driver
   boards, ADR-004 non-blocking debounce, ADR-006/008/009 pin/board specifics) are
   genuinely general firmware-engineering principles that happen to currently be
   described in Arduino-specific terms. Others (exact pin numbers, `arduino-cli`
   compile commands) are inherently board-specific facts that should stay concrete,
   not be vaguely generalized.
6. `.agents/knowledge/README.md` and the renamed board-knowledge folder from chunk 02
   — to understand what's already separated out as board-specific knowledge vs what
   lives in the role's own context files.
7. `humans/start-coding-role.md` — routes a fresh session into this role; its
   framing needs to match whatever you land on here.

## The actual work

Go file by file through the coding role's `AGENT.md`/`AGENTS.md` and `context/`
folder and classify every Arduino-specific statement into one of two buckets:

- **General firmware principle, currently described in Arduino terms.** Example
  candidates: "non-blocking debounce, no `delay()` in the main loop" (ADR-004) is a
  real-time firmware principle that applies to any MCU, not an Arduino quirk.
  "Solenoids are never driven directly from output pins, always via relay/driver
  board" (ADR-002) is a general current-sourcing principle. Reword these so the
  *principle* is stated in board-agnostic language, with the current Arduino
  implementation detail (if still relevant) kept as a supporting example, not the
  rule itself.
- **Genuinely Arduino/AVR-specific fact.** Example candidates: exact pin numbers,
  `.ino` sketch structure (`setup()`/`loop()`), `arduino-cli` toolchain commands,
  hardware SPI pin numbers per board. These should stay concrete and specific — do
  not vaguely water them down into something that sounds generic but loses the
  precision a builder actually needs for the board that's actually shipping today.
  Label them clearly as current-board-family facts (e.g. under a heading like
  "Current Implementation: Arduino Family" or similar) rather than deleting or
  hedging them.

Reword the role's own frontmatter `description` and opening section so the role is
introduced as a firmware/controller-logic role for the project, with "currently
targets Arduino-family boards (Uno default, Mega 2560 or Nano supported)" stated as
a fact about the present, not the role's permanent identity.

## Where you're not confident — ask

This chunk requires judgment calls a fresh agent cannot always get right alone:

- **When a statement could go either way** (is this ADR describing a real-time
  firmware principle, or is it actually inseparable from AVR-specific behavior?),
  don't guess. Ask the human operator, or if no question-asking mechanism is
  available in this session, list the ambiguous cases clearly at the end of your
  output instead of silently picking an interpretation.
- **Do not weaken or hedge any safety-critical constraint** while generalizing
  language — e.g. the display VCC 3.3V warning (ADR-003), the `currentGear`
  preservation rule (ADR-001), the solenoid driver-board requirement (ADR-002). If
  rewording one of these for board-agnostic language would make it read as less
  firm or less specific than the original, stop and ask rather than publishing a
  softened version of a rule that exists because it prevented a real bug or hardware
  damage.
- If you're unsure whether a given `context/` file's content belongs in the role
  definition at all vs. belongs in board-specific knowledge (i.e., should some of
  this actually move to the knowledge base from chunk 02's renamed folder instead of
  just being reworded in place), ask rather than relocating content on your own
  judgment — that's a bigger structural change than this chunk's scope.

## When done

1. Commit directly to the current branch (never a new branch, per `CLAUDE.md`
   Critical Rule #1).
2. Update `humans/start-coding-role.md` if its framing of the role no longer matches.
3. Add an entry to `.agents/DECISIONS.md` recording that the coding role's identity
   was reframed from Arduino-specific to firmware-general, with a one-line summary
   of the principle used to classify statements (general-principle-vs-board-fact).
4. Leave a note confirming chunk 03 is done and chunk 04
   (`04-generalize-root-project-identity.md`) can start.

## Guardrails

- Don't touch the documentation or research roles' files in this chunk — they're
  out of scope here even if they have similar Arduino-scoping issues. Flag them via
  a `[PENDING]` HANDOFFS entry if you notice something, don't fix it inline.
- Don't rewrite firmware source code (`.ino`/`.h`/`.cpp`) in this chunk — this is
  agent-scaffolding/documentation work only, not a firmware change. If reviewing the
  role docs makes you notice an actual firmware bug or inconsistency, drop a
  `[PENDING]` HANDOFFS entry rather than fixing code here.
- Don't invent a hypothetical second board's specifics to make the generalization
  feel more "real." Keep unknowns as genuinely unknown/future — this project is not
  committing to any specific non-Arduino board yet (per the original framing: "not
  saying we will 100% use another board... want to make sure we won't have to
  rebuild if that comes along").
