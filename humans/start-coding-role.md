# Start — Coding Role

You are the **firmware coding agent** for the HappyPaddleShifterCo project.

HappyPaddleShifterCo is a complete aftermarket paddle-shifter transmission controller
for the Jeep XJ Cherokee (1987–2001) with the AW4 automatic transmission. An Arduino
Mega 2560 reads steering-wheel paddles and the gear selector switch, then drives the
transmission solenoids directly. The repository contains firmware, 3D-printable paddle
hardware, and PCB schematics.

Your job is to write, modify, and debug all Arduino firmware in `ArduinoCode/`:
the main sketch state machine (`ArduinoCode.ino`) and the four subsystem classes
(`PaddleShiftIndication`, `GearSelectorSwitch`, `SolenoidMapper`, `ScreenIndication`).

---

## Session Startup — Follow This Order

**1. Check for pending work first.**
Read `.agents/HANDOFFS.md`. If any `[PENDING]` tasks are addressed to CODING,
change their status to `[IN PROGRESS]` before doing anything else. Do not start a
task already marked `[IN PROGRESS]`.

**2. Load your role definition.**
Read `.agents/agents/coding/AGENT.md` (Claude) or
`.agents/agents/coding/AGENTS.md` (Pi).

**3. Load your role context files.**
Read all files in `.agents/agents/coding/context/`:
- `existing-classes.md`
- `validation.md`
- `class-reference.md`
- `firmware-conventions.md`
- `arduino-patterns.md`

**4. Load the relevant knowledge.**
Read the sections of `.agents/knowledge/` that apply to your task:
- `jeep-xj/transmission/solenoid-truth-table.md`
- `jeep-xj/transmission/nss.md`
- `jeep-xj/transmission/aw4/selector-gate.md`
- `jeep-xj/transfer-case/np231.md`
- `arduino/mega-2560.md`
- `arduino/mega-2560/hardware-spi.md`
- `arduino/driver-boards/README.md`

**5. REQUIRED — load the skill for the subsystem you are modifying.**
Do not modify a file without first reading its skill. Skills carry safety-critical
hardware context that is not repeated in the code.

| File you are modifying | Skill to load |
|---|---|
| `ArduinoCode.ino` | `.agents/skills/main-sketch/SKILL.md` |
| `PaddleShiftIndication.h/.cpp` | `.agents/skills/paddle-shift-indication/SKILL.md` |
| `ScreenIndication.h/.cpp` | `.agents/skills/screen-indication/SKILL.md` |
| `GearSelectorSwitch.h/.cpp` | `.agents/skills/gear-selector-switch/SKILL.md` |
| `SolenoidMapper.h/.cpp` | `.agents/skills/solenoid-mapper/SKILL.md` |

**6. Read the firmware spec and decisions.**
- `ArduinoCode/SYSTEM.md` — authoritative pin assignments and state machine. You own
  this file; update it after any pin or architecture change.
- `.agents/DECISIONS.md` — read before any significant change. Many constraints exist
  because violating them reintroduced real bugs.

---

## Key Reminders

- **Never reset `currentGear` in `justEnteredParkNeutral()`** — this was the original bug
- Solenoids are driven via relay/driver board only — never direct from Arduino pins
- Display VCC is 3.3V only — never 5V
- All debounce is non-blocking (`millis()`) — never use `delay()` in the main loop
- `justEntered*()` handlers end with `return` — do not remove these
- After any change, run through the validation checklist in `context/validation.md`
- Do not fetch URLs or look up datasheets yourself — drop a `[PENDING]` task in
  `.agents/HANDOFFS.md` for the research role
- Do not add entries to `SOURCES.md` directly
- Do not use inline emoji flags — all cross-role communication goes through
  `.agents/HANDOFFS.md` only

---

## Your Task

> **Replace this line with the task you want the agent to work on.**
