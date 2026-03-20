# HappyPaddleShifterCo — Claude Code Project Guide

## What This Project Is

A complete aftermarket paddle-shifter transmission controller for the Jeep XJ Cherokee (1987–2001)
with the AW4 automatic transmission (also known as the A340E). Steering-wheel paddles replace the
factory TCU. The driver controls gear selection directly; an Arduino Mega 2560 reads the selector
position, the paddles, and drives the transmission solenoids accordingly.

The repository contains firmware, 3D-printable paddle hardware, and PCB schematics.

---

## Agent Roles

Three specialist roles operate on this project. When starting a task, identify which role applies
and load its `AGENT.md` before doing any work.

| Role | AGENT.md | Responsible for |
|---|---|---|
| **Documentation** | `.agents/agents/documentation/AGENT.md` | Wiring diagrams, pinout tables, install guides, print settings |
| **Coding** | `.agents/agents/coding/AGENT.md` | Arduino firmware — `.ino`, `.h`, `.cpp` files |
| **Research** | `.agents/agents/research/AGENT.md` | Part numbers, datasheets, source verification, web research |

A task may need more than one role. Complete the roles sequentially; use `.agents/HANDOFFS.md` to
pass work between them.

---

## Shared Knowledge Base

Vehicle and hardware context that all roles need lives in `.agents/knowledge/`. Read the relevant
sub-section before starting work — do not re-derive facts already documented there.

```
.agents/knowledge/
  jeep-xj/
    overview.md              — XJ Cherokee variants, years, NSS connector by year
    transmission/
      aw4-overview.md        — What the AW4 is, what we're replacing, gear ranges
      solenoid-truth-table.md — Verified S1/S2/SLU states per gear (sourced)
      nss.md                 — NSS pin continuity map, wiring method, year variants
      aw4/                   — Deeper AW4 detail: selector gate, solenoid specs, NSS wiring
    electrical/
      power-distribution.md  — 12V supply, fusing, grounding rules
    transfer-case/
      np231.md               — NP231, 4WD Low procedure, why Neutral preserves currentGear
    body-chassis/
      steering-column.md     — Paddle mounting options, airbag years, wiring routing
  arduino/
    mega-2560.md             — Pin assignments, hardware SPI, memory constraints
    mega-2560/               — Deeper detail: pinout, hardware-spi, specs
    driver-boards/           — Relay vs high-side driver, flyback diodes, wiring
```

---

## Agent Skills

Subsystem-targeted skills in `.agents/skills/` carry critical hardware context for each class.
Load the relevant skill when working on that subsystem.

| Skill | When to use |
|---|---|
| `paddle-shift-indication` | Modifying `PaddleShiftIndication.h/.cpp` |
| `screen-indication` | Modifying `ScreenIndication.h/.cpp` |
| `gear-selector-switch` | Modifying `GearSelectorSwitch.h/.cpp` |
| `solenoid-mapper` | Modifying `SolenoidMapper.h/.cpp` |
| `main-sketch` | Modifying `ArduinoCode.ino` state machine |
| `hardware-bom` | Selecting or verifying hardware components and part numbers |

---

## Coordination

- **`.agents/WORKFLOW.md`** — How roles collaborate and in what order
- **`.agents/HANDOFFS.md`** — Drop cross-role tasks here; pick them up here
- **`.agents/DECISIONS.md`** — Architectural decisions. Read before modifying anything significant.

---

## Critical Rules (Read Every Session)

1. **Never work on a new branch.** Always commit directly to the currently checked-out branch.
2. **Never reset `currentGear` in the `justEnteredParkNeutral()` handler.** See `DECISIONS.md`.
3. **Solenoids are not driven directly from Arduino pins.** Always via relay/driver board.
4. **Display VCC is 3.3V only.** 5V permanently damages the SSD1351.
5. **`SOURCES.md` is exclusively owned by the Research role.** Coding and Documentation must not add entries directly — route source logging through a HANDOFF to Research.
6. **Check `.agents/HANDOFFS.md` before starting any work.** Change any `[PENDING]` task you are picking up to `[IN PROGRESS]` before beginning. Do not duplicate work already in progress.
