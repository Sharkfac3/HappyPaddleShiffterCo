# Agent Handoffs

Cross-role task queue. Drop tasks here when work needs to be picked up by another role.

**Check this file before starting any session.** If you see a `[PENDING]` task addressed
to your role, change its status to `[IN PROGRESS]` before beginning work. Do not start a
task already marked `[IN PROGRESS]` — it is being handled by another agent.

Do not use inline emoji flags (`🔧`, `🔍`, `🙋`) anywhere in the project. All cross-role
communication goes through this file.

Status values:
- `[PENDING]` — not yet picked up
- `[IN PROGRESS]` — actively being worked on (set this before you start)
- `[DONE]` — completed (leave for record; move to Completed Tasks section)
- `[ESCALATION NEEDED]` — blocked, human operator required

---

## Active Tasks

## [DONE] — Fix stale board/pin references in coding-role-owned files

**From:** DOCUMENTATION (drift audit)
**To:** CODING

**Resolution (2026-08-19):** Both files fixed to match `ArduinoCode/SYSTEM.md` and ADR-009:
- `.agents/agents/coding/AGENT.md` — now reads "Uno default, Mega 2560 or Nano supported"
  throughout; knowledge-path references updated to the renamed `board-comparison.md`/
  `pin-reference/` paths (see structural handoff below).
- `.agents/agents/coding/context/class-reference.md` — pin-define block now shows
  `PIN_S1 A0 / PIN_S2 A1 / PIN_SLU A2`; the "Hardware SPI on Mega" line now covers both
  Mega (51/52) and Uno/Nano (11/13).

---

## [DONE] — Fix stale board/sensor/pin references across documentation-owned knowledge base

**From:** DOCUMENTATION (drift audit)
**To:** DOCUMENTATION

**Resolution (2026-08-19):** All listed files fixed, plus a wider sweep turned up by a
project-wide grep for "Arduino Mega"/"Mega 2560" (scripts/generate_bom.py, ArduinoCode/*.ino/
.h/README.md/SYSTEM.md, root README.md, hardware-bom skill, aw4-overview.md, steering-column.md,
arduino-patterns.md — none of these were in the original list but had the same staleness).
Also folded in the third board (Nano) throughout, since the user flagged that the whole
`.agents/` scaffold was built assuming one/two boards and was never generalized for a third —
see the structural handoff immediately below for the root-cause fix.

---

## [DONE] — Generalize `.agents/knowledge/arduino/` scaffolding for a third board (Nano)

**From:** Human operator (Sharkfac3)
**To:** DOCUMENTATION / CODING (combined, done in one pass)

**Task:** The knowledge base was scaffolded around one board (Mega), then patched to a second
(Uno default), but the structure itself was never made board-agnostic — the file was literally
named `mega-2560.md` and the deep-reference folder `mega-2560/`, even after both held Uno
content too. When the Nano became a real third option (ADR-010), nothing forced a matching
sweep, so it landed in `DECISIONS.md`/`HANDOFFS.md` (power research) but nowhere in the
`knowledge/` docs, skills, or role configs.

**Resolution (2026-08-19):**
- Renamed `.agents/knowledge/arduino/mega-2560.md` → `board-comparison.md` (now a Uno/Mega/Nano
  comparison with a real 3-column table, not a 2-board doc with a misleading filename).
- Renamed `.agents/knowledge/arduino/mega-2560/` → `pin-reference/` (board-agnostic name for
  content that was already mostly board-agnostic project pin data).
- Updated every reference to the old paths across the repo (`AGENTS.md`, `CLAUDE.md`,
  `.agents/WORKFLOW.md`, all three role `AGENT.md`/`AGENTS.md` files, `humans/start-*-role.md`,
  `.agents/knowledge/README.md`).
- Added Nano throughout: pin tables, hardware-SPI tables, board-comparison table, "Choosing a
  Board" guidance, `.agents/knowledge/arduino/README.md` key-facts table.
- Resolved the `AGENTS.md` vs `AGENT.md` escalation below by syncing content rather than
  deleting — `humans/start-*-role.md` explicitly route to `AGENTS.md` for a second tool ("Pi"),
  so it's a real second consumer, not dead scaffolding. Fixed the wrong hard rule in
  `coding/AGENTS.md` ("All inputs are INPUT_PULLUP" — false for the paddle optocoupler sensors)
  and the stale "paddle switch" wording in `documentation/AGENTS.md` while in there.
- `WORKFLOW.md` knowledge-base ownership table updated for the renamed paths.

**Update (2026-08-19):** Nano now actually compiled — `arduino-cli` wasn't on this machine's
PATH so it was installed (official arduino.cc release), then the sketch was compiled against
`arduino:avr:nano` for both bootloader variants (`cpu=atmega328` default, `cpu=atmega328old`).
Identical program size to the Uno build (14070 B / 864 B SRAM); the Nano just reports a higher
flash percentage (45% vs 43%) because this board definition gives it 30720 B usable flash
instead of the Uno's 32256 B. `board-comparison.md` and `DECISIONS.md` ADR-009 updated with the
real numbers — no more `[UNVERIFIED]`. `ArduinoCode/README.md` flash instructions now call out
the two Nano processor options and warn that picking the wrong one uploads successfully but the
board won't run. Also regenerated `BOM.xlsx` from `generate_bom.py` (was stale — script had been
edited for Nano wording but the tracked spreadsheet wasn't regenerated; `openpyxl` wasn't
installed either, fixed via `pip install openpyxl`). No physical hardware bench-tested yet, for
any of the three boards — that remains open.

---

## [PENDING] — Source buck converter and reverse-polarity protection part numbers for Arduino power supply

**From:** DOCUMENTATION
**To:** RESEARCH
**Task:** ADR-010 (`.agents/DECISIONS.md`) established that the Arduino board (Uno/Mega/Nano)
must be powered via a buck converter stepping vehicle 12–14V down to 5V (fed into the
Arduino 5V pin), plus a reverse-polarity protection diode/fuse ahead of it — not raw
vehicle 12V into VIN. `.agents/knowledge/jeep-xj/electrical/power-distribution.md` has been
updated with this design guidance but both parts are marked
`[PENDING RESEARCH — see HANDOFFS.md]` pending an actual sourced part.

**What is needed:**
- A specific buck converter module (e.g. MP1584EN-based, or equivalent) rated for automotive
  12–14V input → clean 5V/enough current for the Arduino + display + relay logic (a few
  hundred mA is enough headroom — see current draw figures in `.agents/DECISIONS.md` ADR-009).
- A reverse-polarity protection component (diode or fused/keyed connector) rated for the
  vehicle-side fused circuit (see "Fusing Requirements" in power-distribution.md — 2A inline
  ahead of the buck converter).

**Context — findings already gathered this session (web search, not yet logged in SOURCES.md):**
- Uno regulator: NCP1117ST50T3G, 7–12V recommended, 20V absolute max.
- Mega regulator: LD1117S50CTR, 7–12V recommended, **15V absolute max** (tightest of the three).
- Nano regulator: NCP1117/LM1117-5.0, 7–12V recommended, 20V absolute max.
- Vehicle alternator running voltage: 13.8–14.2V — above all three boards' recommended range.
- None of the three boards has reverse-polarity protection on VIN; Uno's barrel jack has a
  protection diode but this project doesn't use the barrel jack.
- Source URLs: https://forum.arduino.cc/t/actual-vin-voltage-limit-nano/901436 ,
  https://techexplorations.com/blog/arduino/guide-to-arduino-uno-r3-power/ ,
  https://zbotic.in/arduino-mega-2560-pinout-complete-gpio-and-port-reference/ ,
  https://forum.arduino.cc/t/powering-arduino-in-a-car/539197 ,
  https://forum.arduino.cc/t/voltage-drop-when-nano-supplied-with-12v-car-battery/658559 ,
  https://forum.dronebotworkshop.com/arduino/reverse-voltage-protection-on-the-arduino-nano/

**Output:** Drop confirmed part numbers in a follow-up HANDOFFS entry addressed to
DOCUMENTATION (for wiring diagram / power-distribution.md finalization) and CODING (for
`scripts/generate_bom.py` BOM entry). Log all sources above (and any new ones) in
`SOURCES.md` under a new "Arduino Power Supply — Buck Converter" section.

---

## [DONE] — Update all board docs: Arduino Uno is now the default board (Mega still supported)

**From:** CODING
**To:** DOCUMENTATION

**Task:** Firmware now defaults to the Arduino Uno; solenoid outputs (`PIN_S1/PIN_S2/PIN_SLU`)
moved from digital 11/12/13 to A0/A1/A2 so they no longer collide with the Uno's fixed
hardware-SPI pins (MOSI=11, SCK=13). The Mega 2560 remains fully supported.

**Resolution (2026-08-17):** All files below updated to match `ArduinoCode/SYSTEM.md` and
`DECISIONS.md` ADR-008/ADR-009:
- `ArduinoCode/README.md` — hardware table now lists Uno (default) or Mega; flash steps
  cover both board selections; sanity-check step 1 gives DIN/CLK per board.
- `.agents/knowledge/arduino/mega-2560.md` — rewritten in place as a Uno-vs-Mega comparison
  doc (board comparison table, shared pin table, board-specific SPI table, "which to choose").
- `.agents/knowledge/arduino/mega-2560/pinout.md` — solenoid rows moved to A0–A2; hardware-SPI
  row now shows both boards' pins; "available pins" section corrected (A0–A2 no longer free).
- `.agents/knowledge/arduino/mega-2560/hardware-spi.md` — SPI pin table now has a Uno column;
  wiring table shows both boards' DIN/CLK pins.
- `.agents/knowledge/arduino/driver-boards/README.md` — wiring diagram and prose now say
  A0/A1/A2, board-agnostic.
- Skills `solenoid-mapper`, `screen-indication`, `main-sketch` — pin tables/snippets updated
  to A0–A2 solenoids and per-board SPI pins.
- `humans/start-coding-role.md`, `start-documentation-role.md`, `start-research-role.md` —
  "Arduino Mega 2560" wording generalized to "Arduino Uno (default board) or Mega 2560".
- `README.md` (doc-owned per AGENT.md ownership table) — folder table updated.

**Not touched — outside documentation-role ownership, flagged for the human operator:**
`AGENTS.md` and `CLAUDE.md` both still describe the project as using "an Arduino Mega 2560."
Neither file is in the documentation role's ownership table (only `README.md` is). Decide
whether to generalize this wording and, if so, route it explicitly — `CLAUDE.md` in particular
sits outside all three agent roles' normal write scope.

**Not in scope for this handoff (unchanged):** `Schematics/README.md`, `Models/README.md`,
`scripts/generate_bom.py`, `SOURCES.md` — grep hit these but they weren't checked for
relevance to the board change; scan separately if needed.

---

## [DONE] — Rework PaddleShiftIndication for IR slot optocoupler sensor (replacing mechanical switches)

**From:** RESEARCH
**To:** CODING
**Task:** User is switching from the D2JW-01K11 mechanical switches to an on-hand IR slot-type
optocoupler module (LM393-based) for both paddle inputs, to eliminate mechanical wear. Firmware
needs updating to match this sensor's electrical behavior.

**Context:**
- Confirmed NOT a Hall effect sensor — it's a slot-type IR photointerrupter + LM393 comparator.
- Output pin (DO) is **actively driven push-pull**, not open-drain — do **not** use `pinMode(pin, INPUT_PULLUP)` on these pins. Use plain `INPUT`.
- **Polarity is inverted vs the current switches:** slot unobstructed (clear) → DO LOW; slot obstructed (tab/object in slot) → DO HIGH. Current [PaddleShiftIndication.cpp](ArduinoCode/PaddleShiftIndication.cpp) triggers on HIGH→LOW falling edge, matching active-LOW switches.
- **Open question for paddle mechanical design (not a Research fact — needs a design decision, flag to human/user):** whether the metal/opaque tab sits IN the slot at rest (idle = HIGH, pull clears it = LOW, matches existing falling-edge logic unchanged) or OUT of the slot at rest (idle = LOW, pull inserts it = HIGH, requires flipping edge-detection logic and `_lastUpState`/`_lastDownState` initial values from HIGH to LOW). Do not guess which — confirm against the actual paddle geometry before implementing.
- Operating voltage 3.3–5V, compatible with Mega 5V logic — no level-shifting needed.
- Debounce: existing 50ms timestamp debounce (ADR-004) can stay as-is; no mechanical bounce on this sensor type but doesn't hurt.

**Resolution (2026-08-17):** User confirmed tab sits IN the slot at rest → DO HIGH at rest,
pull clears tab → DO LOW → same HIGH→LOW falling edge the existing debounce logic already
expects. No edge-detection logic change needed. Implemented: `pinMode()` changed from
`INPUT_PULLUP` to plain `INPUT` in `PaddleShiftIndication.cpp`, wiring comments updated in
`PaddleShiftIndication.h/.cpp`, `ArduinoCode.ino`, `ArduinoCode/SYSTEM.md`, and the
`paddle-shift-indication` skill. Compiled clean against `arduino:avr:mega` (arduino-cli 1.5.2-rc.1, 2026-08-17) —
flash 14878B (5%), SRAM 864B (10%), only unrelated core-library warnings. Not yet
bench-tested on real hardware — verify sensor polarity on actual paddles before
trusting it.

**Source:** See `SOURCES.md` → "Paddle Trigger Sensor — IR Slot-Type Optocoupler (LM393), User-Owned Part" for full electrical facts and cross-referenced sources.

---

## [DONE] — Update BOM: replace D2JW-01K11 paddle switches with IR slot optocoupler sensor

**From:** RESEARCH
**To:** DOCUMENTATION
**Task:** `hardware-bom` skill and any paddle-switch references in builder docs need updating —
project is moving from the Omron D2JW-01K11 mechanical switch to an IR slot-type optocoupler
(LM393-based) sensor for both paddle positions.

**Resolution (2026-08-17):**
- `.agents/skills/hardware-bom/SKILL.md` — "Paddle Switch Detail" replaced with "Paddle Trigger
  Sensor Detail" (confirmed electrical specs, mounting mitigations, sourcing caveat); former
  D2JW-01K11 spec/alternatives table kept as a "Former Selection" historical reference. Also
  fixed a stale "Microcontroller: Mega 2560" row missed by the earlier board-update handoff.
- `Models/README.md` — BOM table, new "Sensor Detail" section, assembly steps 1–3, and the
  alternatives table all rewritten for the sensor. Flagged the mechanical pocket geometry as
  **not yet designed** (see new research handoff below) rather than guessing dimensions.
- `ArduinoCode/README.md` — "Required Hardware" paddle row updated.
- `.agents/knowledge/jeep-xj/body-chassis/steering-column.md` and `README.md`,
  `.agents/knowledge/jeep-xj/transmission/aw4/overview.md`,
  `.agents/knowledge/jeep-xj/electrical/power-distribution.md` (this one had a wrong electrical
  fact — listed paddle inputs as INPUT_PULLUP, corrected to plain INPUT push-pull),
  `.agents/knowledge/arduino/mega-2560/README.md` — terminology and wiring-mode references
  updated from "paddle switch" to "paddle sensor".
- `.agents/agents/documentation/context/deliverables.md`,
  `.agents/agents/documentation/AGENTS.md` — doc-role's own config files, small stale mentions
  fixed.

**Not touched:**
- `scripts/generate_bom.py` — generates the BOM spreadsheet, still hardcodes the D2JW-01K11
  switch (sheet 3 "Paddle Switch Detail", row 9 of the parts list). This is a code file, not a
  markdown deliverable — flagged as a new `[PENDING]` handoff to CODING below rather than edited
  directly by documentation.
- `.agents/skills/paddle-shift-indication/SKILL.md`, `ArduinoCode/PaddleShiftIndication.cpp` —
  coding-owned, already updated per the [DONE] optocoupler rework entry above.

**Source:** `SOURCES.md` → "Paddle Trigger Sensor — IR Slot-Type Optocoupler (LM393), User-Owned Part".

---

## [DONE] — Regenerate BOM spreadsheet for optocoupler sensor (still shows D2JW-01K11)

**From:** DOCUMENTATION
**To:** CODING
**Task:** `scripts/generate_bom.py` hardcodes the replaced Omron D2JW-01K11 switch — sheet 3
is titled "Paddle Switch Detail" (row 9 of the parts list, plus header/print-note cells around
line 135–390) and describes switch specs, pocket depth, and D2F-5L incompatibility that no
longer apply now that the project uses an IR slot-type optocoupler sensor.

**Context:** See the [DONE] "Update BOM" entry above and `.agents/skills/hardware-bom/SKILL.md`
→ "Paddle Trigger Sensor Detail" for the confirmed replacement content (electrical specs,
mounting mitigations, sourcing caveat — generic/unbranded AliExpress part, no manufacturer
number). Full mechanical/pocket dimensions are **not yet available** — see the research handoff
below; the script may need a placeholder/UNVERIFIED row rather than fabricated dimensions until
that lands.

**Resolution (2026-08-17):** `scripts/generate_bom.py` now emits the current IR slot-type
optocoupler sensor design only: Electronics sheet row updated, the old "Paddle Switch Detail"
sheet replaced with a current-state sensor detail sheet, SPI/pin references rewritten for
Uno-default / Mega-supported firmware, paddle inputs corrected to plain `INPUT`, and solenoid
outputs corrected to A0/A1/A2. Legacy Omron/D2F historical text removed from the workbook.

**Output:** Update the script so a regenerated BOM spreadsheet matches the current hardware.

---

## [PENDING] — Confirm optocoupler sensor module physical dimensions for paddle pocket design

**From:** DOCUMENTATION
**To:** RESEARCH
**Task:** The IR slot-type optocoupler module (AliExpress item 3256804480682852) needs a new
paddle-body pocket design — it requires a slot gap, not a switch-lever pocket. No PCB
dimensions, slot gap width, or mounting hole layout have been sourced yet; `Models/README.md`
currently marks these `[UNVERIFIED]` (approximate ~5mm slot gap, not independently confirmed).

**What is needed:** Physical/mechanical dimensions of the module from the AliExpress listing
photos/spec fields, a similar module's documented dimensions (cross-reference like the
electrical facts were), or direct measurement if the user can provide it — PCB length/width/
thickness, slot gap width and depth, and any mounting hole positions.

**Why it matters:** `Models/README.md` Step 2 (mount the sensor in the paddle body) is
currently blocked on this — no pocket geometry can be modeled without it.

**Output:** Drop confirmed dimensions in a follow-up HANDOFFS entry addressed to DOCUMENTATION,
and log the source in `SOURCES.md` under the existing "Paddle Trigger Sensor" section.

---

## [PENDING] — Confirm print settings for Models/README.md

**Resolved (2026-08-17):** Item 1 (D2JW-01K11 mounting screw spec) is now moot — the paddle
switch has been replaced by an IR slot optocoupler sensor (see "Update BOM" entries above).
Removed from this task. The sensor's own mounting-fastener needs are tracked in the new
"Confirm optocoupler sensor module physical dimensions" handoff above instead.

**From:** DOCUMENTATION
**To:** RESEARCH
**Task:** `Models/README.md` Print Settings section is marked [UNVERIFIED] and needs confirmed
values before the document can be published as authoritative. No tested print settings exist
for the paddle body STL files. Confirm and document:
- Recommended material (PETG vs ABS vs other)
- Layer height, infill %, perimeter count
- Orientation recommendation (which face down)
- Whether supports are required and where

**Output:** Drop confirmed values in a follow-up HANDOFFS entry addressed to DOCUMENTATION
so `Models/README.md` can be updated. Log any datasheet or manufacturer sources in
`SOURCES.md`.

---

## [DONE] — Update paddle 3D model documentation for D2JW-01K11 geometry

**From:** RESEARCH
**To:** DOCUMENTATION
**Task:** D2JW-01K11 is now the formally selected paddle switch (replacing D2F-5L).
Update `Models/README.md` and any paddle body STL design notes with the confirmed
mechanical dimensions from the Omron datasheet.

**Switch body dimensions (from Omron datasheet, human-verified 2026-03-20):**
- Body: 12.7 mm wide × 12.3 mm tall × 5.3 ± 0.1 mm deep
- Mounting holes: 2.35 mm dia., spaced 3.95 × 3.95 mm
- Lever: stainless steel t0.3 mm, R16.5 mm arc

**Travel / actuation geometry:**
- Operating Position (OP): 8.4 ± 0.8 mm (lever tip travel to actuation point)
- Pretravel: 6.4 mm max
- Overtravel: 1.4 mm min
- Movement Differential: 0.7 mm max
- OP measurement arm height: 6.15 mm above body base

**Mounting:**
- Chassis mount — switch body screws to paddle body (not PCB through-hole)
- Termination: solder lug — short wire leads run from switch to PCB/Arduino

**Notes for 3D model:**
- Switch pocket must place lever tip 8.4 mm from the paddle contact surface
  (1.6 mm deeper than the former D2F-5L pocket at 6.8 mm)
- D2F-5L and D2JW-01K11 are NOT dimensionally interchangeable
- Full mechanical drawing dimensions logged in SOURCES.md under
  "Paddle Switch Alternative — Omron D2JW-01K11 / Mechanical Drawing"

---

## [PENDING] — Verify 1997–2001 AW4 NSS connector pinout from primary source

**From:** DOCUMENTATION
**To:** RESEARCH
**Task:** Find and confirm the pin-label-to-wire mapping for the 1997–2001 Jeep XJ AW4
neutral safety switch connector from a primary source (FSM or OEM wiring diagram).
The physical connector housing differs from the 1987–1996 8-pin Deutsch unit, and the
exact pinout has not been independently verified from a primary source.

**What is already known:**
- The continuity map (which pairs close for which selector position) is the same across all years
- The 1997–2001 connector part number is Omix-ADA 4882173 / OEM 4882173
- The 1987–1996 connector is confirmed: 8-pin Deutsch, pins A–H (B↔C, A↔E, A↔G, A↔H)
- Source already tried: 1993 FSM confirms 1987–1996 pinout only

**What is needed:** A factory service manual page, wiring diagram, or OEM source that
shows the 1997–2001 NSS connector pin layout — specifically which physical pin corresponds
to which NSS signal (PN, R, 3rd, 1-2) so a builder can wire it without guessing.

**Why it matters:** A builder wiring a 1997–2001 XJ with incorrect pin assignments
will either get no transmission control or potentially damage the Arduino.

**Suggested search approach:**
- jeep-manual.ru 1997, 1999, and 2001 XJ FSM pages (see `context/trusted-sources.md`)
- Wayback Machine fallback for any blocked FSM sources
- Montana Fab override instructions (confirmed accessible) may show wire colours by year
- Omix-ADA product page for part 4882173 may include a pinout diagram

**Output:** Drop confirmed pinout in a follow-up HANDOFFS entry addressed to DOCUMENTATION,
and log the source in `SOURCES.md` under "Neutral Safety Switch — AW4 / Jeep XJ".
If no primary source is found, escalate as `[ESCALATION NEEDED]` with sources attempted.

---

## Completed Tasks

| Task | Completed | Notes |
|---|---|---|
| Confirm D2JW lever-actuator variant part number | 2026-03-20 | D2JW-01K11 selected as primary — straight lever, 82 gf, IP67, 100K electrical life. Full mechanical dimensions logged in SOURCES.md. |
| Update all board docs for Uno-default (Mega still supported) | 2026-08-17 | Updated ArduinoCode/README.md, mega-2560.md (rewritten as Uno-vs-Mega comparison), pinout.md, hardware-spi.md, driver-boards/README.md, 3 skills, 3 humans/start-*-role.md, README.md. AGENTS.md/CLAUDE.md flagged to human — outside doc-role ownership. |
| Update BOM for optocoupler paddle sensor (replacing D2JW-01K11) | 2026-08-17 | Rewrote hardware-bom skill, Models/README.md (BOM, sensor detail, assembly steps, alternatives), plus terminology/electrical-fact fixes across 7 knowledge-base and doc-config files. Pocket geometry flagged [PENDING] — no module dimensions sourced yet. generate_bom.py flagged to CODING (still shows old switch). |
| Update paddle 3D model documentation for D2JW-01K11 geometry | 2026-03-20 | Models/README.md rewritten with full switch BOM, D2JW-01K11 body/actuation dimensions, switch pocket depth rule (8.4 mm), mounting method, assembly steps, and alternatives table. Fastener spec and print settings flagged UNVERIFIED — new PENDING handoff raised to RESEARCH. |

---

## Escalations Awaiting Human Input

### [RESOLVED 2026-08-19] — Duplicate, diverging role-config files: `AGENT.md` vs `AGENTS.md` per role

**Resolution:** Not orphaned — `humans/start-*-role.md` explicitly route to `AGENTS.md` for a
second tool ("Pi"), so both files are live and must be kept in sync manually. Synced content
(board wording, knowledge paths, the wrong `INPUT_PULLUP`-only rule, stale "paddle switch"
wording) rather than deleting either file. See the "Generalize `.agents/knowledge/arduino/`"
handoff above. The dual-file-drift risk itself is not eliminated — a future change to one still
needs a matching edit to the other — but that's a tooling-convention decision for the human
operator, not something to guess at.

### [ESCALATION NEEDED — original text below, kept for record] — Duplicate, diverging role-config files: `AGENT.md` vs `AGENTS.md` per role

**Raised by:** DOCUMENTATION (drift audit), 2026-08-18
**Found:** Each role folder (`.agents/agents/{coding,documentation,research}/`) contains
both `AGENT.md` and `AGENTS.md` — not the same file duplicated, two structurally different
documents with different content. Both were added in the same commit (`85ff5c8`, "agent
scaffolding and setup") and have never been reconciled since.
- Root `CLAUDE.md` and root `AGENTS.md` both route exclusively to the singular `AGENT.md`
  ("load its `AGENT.md` before doing any work") — the plural `AGENTS.md` files are not
  referenced by anything in this repo.
- The orphaned `AGENTS.md` files are stale and, in one place, actively wrong: the coding
  role's `AGENTS.md` states "All inputs are `INPUT_PULLUP`, active LOW" as a hard rule —
  true for the NSS switch but wrong for the paddle optocoupler sensors, which use plain
  `INPUT` (see the paddle-shift-indication HANDOFFS resolution, 2026-08-17). All three
  `AGENTS.md` files also still describe the board as "an Arduino Mega 2560" only.
- Risk: `AGENTS.md` is an increasingly common auto-discovery filename convention for
  agent tooling. If anything ever reads it by convention instead of `CLAUDE.md`'s explicit
  `AGENT.md` pointer, it will load wrong hardware facts.

**Why this needs a human decision rather than a role fixing content:** this is scaffolding/
tooling structure, not a documentation, coding, or research deliverable — no role owns it
(same category as the `AGENTS.md`/`CLAUDE.md` root-file wording gap flagged in the
Uno-default handoff above).

**What's needed:** Decide whether `AGENTS.md` (plural) per role should be deleted, merged
into `AGENT.md`, or kept as a distinct format for some tool — then route the resulting work
(deletion, or a content-sync task) through a normal HANDOFF.

---

## How to Add a Handoff

Copy this template and fill it in:

```
## [PENDING] — Brief task title

**From:** DOCUMENTATION / CODING / RESEARCH
**To:** DOCUMENTATION / CODING / RESEARCH
**Task:** What needs to be done
**Context:** Relevant facts, file paths, or constraints
**Source:** URL or file reference if applicable
```
