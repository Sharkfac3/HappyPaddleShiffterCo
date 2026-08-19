# Architectural Decisions

Decisions that affect the firmware design, hardware choices, or project approach.
Read this before making any significant change. Many of these decisions exist because
violating them reintroduced a real bug.

---

## ADR-001: Do NOT reset currentGear when entering Park/Neutral

**Decision:** `justEnteredParkNeutral()` calls `solenoids.allOff()` but does NOT
reset `currentGear`.

**Reason:** The physical selector gate is P → R → N → D. Engaging 4WD Low (NP231
transfer case) requires moving the selector to Neutral while working the transfer
case lever, then returning to Drive. If `currentGear` were reset on every Neutral
entry, the transmission would always drop back to 1st when returning from the 4WD
Low engagement procedure — forcing an unwanted downshift while the vehicle is in
motion or at low speed.

**Consequence:** When the selector returns to Drive, `justEnteredDrive()` fires and
calls `solenoids.applyGear(currentGear)` — re-engaging at the preserved gear.

**Startup exception:** `applyState()` (called once in `setup()`) DOES initialise
`currentGear = 1` for the `GEAR_SEL_PARK_NEUTRAL` case. This is correct — there is
no previous gear to preserve at power-on.

**Reverse is different:** `justEnteredReverse()` DOES reset `currentGear = 1`. Reverse
always requires the vehicle to be fully stopped; 1st gear on return is always correct.

**Do not reverse this decision** without considering the 4WD Low use case.

---

## ADR-002: Solenoids driven via relay/driver board, not directly from Arduino pins

**Decision:** S1, S2, and SLU outputs go to a relay or high-side driver board, which
then switches the 12V solenoid circuit. Arduino pins never carry 12V or solenoid current.

**Reason:** AW4 solenoids run on 12V and draw up to 2A each. Arduino output pins are
rated to ~40mA. Direct connection would immediately destroy the Arduino.

**Required:** Flyback diodes (1N4007) across each solenoid coil to protect the driver
board from inductive kickback.

**SLU note:** SLU is digital on/off on this AW4 variant — NOT PWM. Do not attempt to
implement torque-converter slip control with PWM; it is not supported by this hardware.

---

## ADR-003: Display is SSD1351, initialised with begin() not initR()

**Decision:** `ScreenIndication` uses `_tft.begin()` (Adafruit SSD1351 init),
not `initR()` (which is ST7735-only).

**Reason:** The WaveShare 1.5" RGB OLED uses the SSD1351 driver chip. `initR()` is
for the ST7735 family. Calling `initR()` produces a blank or corrupted display.

**VCC:** The display is 3.3V only. Connecting it to 5V permanently damages it.

---

## ADR-004: All debounce is non-blocking (timestamp-based)

**Decision:** All input debounce uses `millis()` timestamps with a 50ms settle window.
No `delay()` calls in the main loop.

**Reason:** `delay()` blocks the entire loop, preventing the selector state machine and
paddle inputs from being sampled. A 50ms delay would make the controller unresponsive
and potentially cause solenoid state glitches during gear transitions.

---

## ADR-005: justEntered*() handlers use return to exit loop() immediately

**Decision:** Each `justEntered*()` handler in `loop()` ends with `return` to exit
the loop iteration immediately after a state transition.

**Reason:** Prevents double-processing. Without `return`, a state transition on one
iteration could also be processed by the `switch(state)` block below it in the same
cycle, potentially applying conflicting solenoid states.

---

## ADR-006: Hardware SPI pins 51 (MOSI) and 52 (SCK) are fixed on the Mega

**Decision:** The SSD1351 display uses hardware SPI. On the Arduino Mega 2560,
hardware SPI is on pins 51 (MOSI) and 52 (SCK). These cannot be reassigned.

**Reason:** The Adafruit SSD1351 library in hardware SPI mode uses the hardware SPI
peripheral. Software SPI (bit-banging) is an alternative but is significantly slower
and has not been tested on this project.

---

## ADR-007: Park and Neutral are treated identically

**Decision:** Both Park and Neutral cause `GEAR_SEL_PARK_NEUTRAL` — they cannot be
distinguished by the NSS alone (both close pins B↔C).

**Reason:** This is a hardware limitation of the AW4 NSS. Distinguishing them would
require an additional park pawl sensor or a separate input.

**Display:** Both show "P". If hard differentiation is required in future, a separate
park switch must be added to the hardware.

---

## ADR-008: Arduino Uno confirmed technically viable as an alternative to the Mega 2560

**Decision:** Project remains on the Mega 2560 (see ADR-006) for now, but the Uno is
confirmed a viable substitute if a future BOM/cost driver calls for it. This is not
a switch — no wiring or pin-assignment change has been made. It records the outcome
of an evaluation so it does not need to be re-litigated.

**Pin count:** Not a blocker on its own — Uno has 20 usable I/O (14 digital + 6 analog,
which are fully digital-capable, not analog-only). Project uses 14.

**Pin conflict (the real blocker, now resolved on paper):** Uno's hardware SPI is fixed
on pins 11 (MOSI) and 13 (SCK) — the same pins currently used for the S1 and SLU
solenoid outputs (see ADR-006 for the Mega's equivalent fixed pins, 51/52). Fix: move
solenoid outputs S1/S2/SLU from digital 11/12/13 to analog A0/A1/A2 (used as digital
outputs — same technique already proven by this project's own CS/DC/RST wiring on
A3/A4/A5). This is a wiring + `#define` change only, not yet applied.

**Memory (the suspected blocker — measured, not a blocker):** Compiled with
`arduino-cli` against `arduino:avr:uno`:

- Flash: 15794 / 32256 bytes (48%)
- SRAM: 867 / 2048 bytes (42%), 1181 bytes free for locals

Same SRAM figure as the Mega build (867 bytes) — the Adafruit_SSD1351 library writes
directly over SPI and keeps no RAM framebuffer, so display memory cost doesn't scale
with screen resolution the way it would for a buffered display driver (e.g. SSD1306).
Headroom is comfortable on both flash and SRAM axes.

**Why the original estimate was wrong:** `.agents/knowledge/arduino/mega-2560.md`
estimated the GFX+SSD1351 stack at "~25 KB" flash. Measured usage is ~16 KB. The
Arduino toolchain links with `--gc-sections`; this sketch only calls text primitives
(`fillScreen`, `setTextColor`, `setTextSize`, `setCursor`, `print`), so unused GFX
drawing code (circles, triangles, bitmap blit) never gets linked in.

**Consequence:** If board choice is revisited for cost/BOM reasons, Uno is a real
option — remap solenoid pins to A0–A2 and re-verify wiring, no memory redesign
required. Mega remains the documented board until that decision is explicitly made.

**Resolution (2026-08-17): Superseded by ADR-009 — the remap described above has now
been applied and the Uno is the default board.**

---

## ADR-009: Arduino Uno adopted as default board; Mega 2560 retained as supported alternative

**Decision:** Firmware now targets the Uno by default. The Mega 2560 remains fully
supported — same source files, same pin `#define`s, same wiring, no `#ifdef` branching.
This was possible because the only real conflict (ADR-008) was solenoid outputs sitting
on the Uno's fixed hardware-SPI pins.

**Change applied:** `PIN_S1/PIN_S2/PIN_SLU` moved from digital 11/12/13 to A0/A1/A2 in
`ArduinoCode.ino`. This frees the Uno's hardware SPI (MOSI=11, SCK=13) for the display.
The Mega's hardware SPI (MOSI=51, SCK=52) was never on 11/12/13, so it is unaffected —
the same firmware and wiring now work unchanged on both boards. See `Firmware/SYSTEM.md`
for the updated pin table.

**Why one firmware image works for both:** The display's DIN/CLK hardware-SPI pins are
never a project `#define` — the `Adafruit_SSD1351` library resolves them from the `SPI`
object automatically based on the board the sketch is compiled for. Every other pin in
this project (paddles, NSS, solenoids, CS/DC/RST) is a plain digital/analog-as-digital
pin available in the same numbering on both boards.

**Not yet done:** Bench verification on real hardware. Compiles clean (arduino-cli 1.5.2-rc.1)
against `arduino:avr:uno` (flash 14070B/43%, SRAM 864B/42%, 2026-08-17), `arduino:avr:mega`
(flash 14878B/5%, SRAM 864B/10%, 2026-08-17), and `arduino:avr:nano` (flash 14070B/45%, SRAM
864B/42% — identical byte count to the Uno, higher percentage only because the Nano's usable
flash is 30720B not 32256B; verified against both the `atmega328` and `atmega328old` bootloader
options, 2026-08-19) — not yet flashed/tested on physical hardware for any of the three.

**Consequence for documentation:** `Firmware/README.md`, `.agents/knowledge/microcontroller/`,
and the `solenoid-mapper`/`screen-indication`/`main-sketch` skills still describe the old
Mega-only, pins-11/12/13 setup — flagged to the documentation role via `HANDOFFS.md`.

---

## ADR-010: Arduino board power supplied via buck converter, not raw vehicle 12V into VIN

**Decision:** The controller's Arduino board (whichever of Uno/Mega/Nano ships) is powered
by feeding a buck-converter-regulated 5V into the Arduino's 5V pin — not by wiring vehicle
12V directly into VIN or a barrel jack.

**Reason:** User raised whether the Nano could be run directly off the vehicle's 12V line,
having done so successfully in a past project, and had heard Uno/Mega could not. Research
(web) found this distinction does not hold: Uno (NCP1117ST50T3G), Mega (LD1117S50CTR), and
Nano (NCP1117/LM1117-5.0) all use the same class of onboard linear (LDO) regulator, all
rated for a 7–12V *recommended* input despite higher absolute maximums (Uno/Nano 20V, Mega
15V — Mega has the least headroom of the three, not the most). A running vehicle's charging
system holds 13.8–14.2V, already above every board's recommended ceiling. Multiple forum
reports confirm Nano regulators run hot under load at this voltage the same as Uno/Mega —
the user's past success was most likely due to low current draw in that project, not a
board-specific tolerance. See sources logged via the Research handoff below.

**Consequence:** Power design now requires a buck converter (e.g. MP1584EN-based module)
between the vehicle's fused 12V feed and the Arduino's 5V pin, plus a reverse-polarity
protection diode/fuse ahead of it (VIN has no built-in reverse-polarity protection on any
board, and this project does not use a barrel jack). Applies identically regardless of
which board (Uno/Mega/Nano) ships. `.agents/knowledge/jeep-xj/electrical/power-distribution.md`
updated with this guidance; exact buck converter and protection-diode part numbers not yet
sourced — see `[PENDING]` HANDOFFS entry to Research.

**Not yet done:** Part number selection/verification, BOM entry, updated wiring diagram
showing the buck converter stage.

---

## ADR-011: Vendor-scoped folder names renamed to board-agnostic names (multi-controller pivot, chunk 02)

**Decision:** `ArduinoCode/` (repo root) renamed to `Firmware/`; `.agents/knowledge/arduino/`
renamed to `.agents/knowledge/microcontroller/`. Both via `git mv`, history preserved.

**Reason:** Part of a sequence generalizing the agent scaffolding so a future non-Arduino
controller board wouldn't require rebuilding it (see `humans/multi-controller-pivot/`). Both
old names actively misled: a future agent working on a non-Arduino board would see
`ArduinoCode/`/`knowledge/arduino/` and assume neither applied, even though most underlying
content (relay/driver wiring, SPI pin tables, state-machine architecture) was already
board-agnostic — only the folder *names* were vendor-scoped. Target names confirmed by the
human operator (2026-08-19) rather than guessed, per the chunk's own guardrail against
unilaterally choosing low-reversibility names.

**Date:** 2026-08-19.

**Scope:** Rename and reference-fix only — every live reference to the old paths across the
repo (`AGENTS.md`, `CLAUDE.md`, `.agents/WORKFLOW.md`, both role `AGENTS.md` files, role
`context/` files, all six `.agents/skills/*/SKILL.md`, `.agents/knowledge/**`,
`humans/start-*-role.md`, `scripts/generate_bom.py`, `README.md`, `Schematics/README.md`,
`Models/README.md`, `SOURCES.md`) was updated to the new paths and `scripts/generate_bom.py`
was re-run to confirm it still functions (regenerated `BOM.xlsx` — only the source-citation
strings changed). Historical/dated entries in `.agents/HANDOFFS.md`, the ADR-008 quote above,
and the `humans/multi-controller-pivot/` chunk files themselves were deliberately left
referencing the old names — they are accurate records of what those names were at the time,
not live pointers. No prose inside the renamed folders was generalized beyond the folders'
own title lines (`Firmware/README.md`, `Firmware/SYSTEM.md`) — deeper Arduino-specific
rewording is chunk 03 (coding-role identity) and chunk 04 (root docs), not this chunk.

**Consequence:** If a stale reference to `ArduinoCode/` or `.agents/knowledge/arduino/` turns
up anywhere this sweep missed, it's leftover from before this rename — update it to
`Firmware/` / `.agents/knowledge/microcontroller/` respectively rather than treating it as
intentional.
