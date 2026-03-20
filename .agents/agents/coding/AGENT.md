---
name: coding
description: >
  Arduino firmware for the HappyPaddleShifterCo transmission controller. Owns all
  .ino, .h, and .cpp files in ArduinoCode/. Use this role for any change to the
  state machine, class implementations, pin assignments, or debounce logic.
---

# Coding Role

Writes and maintains the Arduino Mega 2560 firmware that controls the AW4 automatic
transmission. This includes the main sketch state machine, all four subsystem classes,
and their header files.

---

## What This Role Owns

| File | Purpose |
|---|---|
| `ArduinoCode/ArduinoCode.ino` | Main sketch — setup(), loop(), applyState(), state machine |
| `ArduinoCode/PaddleShiftIndication.h/.cpp` | Debounced paddle switch reader |
| `ArduinoCode/GearSelectorSwitch.h/.cpp` | AW4 NSS reader, selector state enum |
| `ArduinoCode/SolenoidMapper.h/.cpp` | Gear-to-solenoid truth table |
| `ArduinoCode/ScreenIndication.h/.cpp` | SSD1351 OLED display wrapper |

This role does **not** write documentation or Markdown files (except inline code comments).
If a firmware change needs to be reflected in wiring docs or pinout tables, drop a task
in `.agents/HANDOFFS.md` for the documentation role.

---

## Context to Load Before Starting

1. **Shared knowledge base** — read the relevant sections of `.agents/knowledge/` first:
   - `jeep-xj/transmission/solenoid-truth-table.md` — the verified gear/solenoid map
   - `jeep-xj/transmission/nss.md` — NSS wiring, pin pairs, active-LOW behaviour
   - `jeep-xj/transmission/aw4/selector-gate.md` — selector gate mechanics, GEAR_SEL_UNKNOWN cause
   - `jeep-xj/transfer-case/np231.md` — why currentGear must be preserved through Neutral
   - `arduino/mega-2560.md` — hardware SPI pins, memory constraints
   - `arduino/mega-2560/hardware-spi.md` — detailed SPI wiring and Mega vs Uno differences
   - `arduino/driver-boards/README.md` — driver board requirements, flyback diodes

2. **Role context** — load all files in this folder:
   - `context/existing-classes.md` — public API reference for all four classes
   - `context/validation.md` — Serial Monitor expected output, state machine checks
   - `context/class-reference.md` — class ownership rules, `currentGear` ownership detail
   - `context/firmware-conventions.md` — naming, style, and structural rules for all code
   - `context/arduino-patterns.md` — non-blocking debounce, one-shot flags, redraw guard patterns

3. **REQUIRED — load the skill for the subsystem you are modifying before writing any code:**
   - `paddle-shift-indication` — PaddleShiftIndication.h/.cpp
   - `screen-indication` — ScreenIndication.h/.cpp
   - `gear-selector-switch` — GearSelectorSwitch.h/.cpp
   - `solenoid-mapper` — SolenoidMapper.h/.cpp
   - `main-sketch` — ArduinoCode.ino

   Do not modify a subsystem file without first loading its skill. Skills carry safety-critical
   hardware context that is not repeated in the code. Skipping them reintroduces known bugs.

4. **`.agents/DECISIONS.md`** — read before any significant change. Many constraints here
   exist because of hard-won debugging; violating them reintroduces known bugs.

---

## Critical Constraints

- **Do NOT reset `currentGear` in the `justEnteredParkNeutral()` handler.** This was the
  original bug. See `DECISIONS.md` and the `gear-selector-switch` skill for full context.
- **Solenoids are never driven directly from Arduino pins.** Always via relay/driver board.
- **Display VCC is 3.3V only.** Do not wire or configure it for 5V.
- **Hardware SPI pins 51 (MOSI) and 52 (SCK) are fixed on the Mega.** Do not reassign.
- **All debounce is non-blocking (timestamp-based).** Never use delay() in the main loop.
- **`justEntered*()` handlers use `return`** to exit loop() immediately after a state
  transition — this is intentional and prevents double-processing in the same cycle.
- **`ArduinoCode/SYSTEM.md` is owned by this role.** Update it after any pin assignment
  or architectural change. Documentation reads it but must not modify it.

---

## Coordination

- If a code change affects wiring or pinout docs, drop a `[PENDING]` task in
  `.agents/HANDOFFS.md` for the **documentation role**.
- **Do not fetch URLs, open datasheets, or confirm part numbers yourself.** If a code
  change requires research, drop a `[PENDING]` task in `.agents/HANDOFFS.md` for the
  **research role** and wait for the finding. Do not implement based on unverified data.
- **Do not add entries to `SOURCES.md` directly.** All source logging goes through the
  research role via HANDOFFS.md.
