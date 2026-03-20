# Firmware Conventions — HappyPaddleShifterCo

Naming, style, and structural rules for all code in `ArduinoCode/`. New code must follow these conventions so the codebase stays readable and consistent.

---

## File Naming

- Each class lives in its own `.h` / `.cpp` pair named after the class: `ClassName.h`, `ClassName.cpp`
- The main sketch is `ArduinoCode.ino` — do not rename it
- All files live flat in `ArduinoCode/` — no subdirectories within the sketch folder (Arduino IDE requirement)

---

## Class Naming

- Class names: `PascalCase` — e.g. `PaddleShiftIndication`, `SolenoidMapper`
- Class names are descriptive nouns or noun phrases describing what the class represents, not what it does

---

## Member Naming

| Kind | Convention | Example |
|---|---|---|
| Private member variables | `_camelCase` with leading underscore | `_lastUpTime`, `_pinS1` |
| Public methods | `camelCase` | `shiftUpRequested()`, `applyGear()` |
| Private methods | `camelCase` | `write()`, `renderText()` |
| `#define` pin constants | `SCREAMING_SNAKE_CASE` | `PIN_S1`, `PIN_NSS_PN` |
| `#define` bounds/limits | `SCREAMING_SNAKE_CASE` | `GEAR_MIN`, `GEAR_MAX` |
| `static const` members | `SCREAMING_SNAKE_CASE` | `DEBOUNCE_MS` |
| Enum values | `SCREAMING_SNAKE_CASE` | `GEAR_SEL_DRIVE`, `GEAR_SEL_UNKNOWN` |
| Local variables | `camelCase` | `reading`, `wantUp` |

---

## Constants

- **Pin assignments and limits** go in `ArduinoCode.ino` as `#define` — they are configuration, not logic
- **Timing constants inside a class** (e.g. debounce window) use `static const unsigned long` as a private member — keeps the value inside the class it belongs to
- Do not use magic numbers inline — every numeric constant must have a named define or `const`

---

## Header Files

Each `.h` file must use include guards:

```cpp
#ifndef CLASSNAME_H
#define CLASSNAME_H

// ... class definition

#endif
```

Forward declarations go in the `.h`. Implementation goes in the `.cpp`. Do not put non-trivial logic in a header.

---

## Comments

- File header block: every `.h` and `.cpp` file starts with a brief comment naming the class, its role, and any critical hardware note
- Non-obvious logic: explain the *why*, not the *what*
- Safety-critical sections must have a comment:

```cpp
// Do NOT reset currentGear here — gear is preserved through Neutral for transfer case operations.
// See SYSTEM.md: "Transfer Case Operation" section.
```

- TODOs must include a specific description and, where applicable, a reference to a SKILL.md:

```cpp
// TODO: currently shows "N" — add showThird() to ScreenIndication if "3" is preferred
// See .agents/skills/screen-indication/SKILL.md for implementation instructions
```

---

## Serial Logging

- Baud rate: `9600` (set in `setup()`)
- Format: `"-> STATE | action | detail"` for state transitions
- Format: `"SHIFT UP -> gear N"` / `"SHIFT DOWN -> gear N"` for gear changes
- Format: `"INIT: STATE"` for startup initialisation in `applyState()`
- Do not add verbose logging to `update()` methods — they run every loop and will flood the monitor

---

## Safety Defaults

- Every output class must call its safe-state function in `begin()` before returning
- `SolenoidMapper::begin()` calls `allOff()` — this is the AW4 electrical failsafe (4th gear hydraulic)
- `ScreenIndication::begin()` clears the display to black
- Any new output class must define and document what its safe default state is

---

## What Lives Where

| Thing | Where it lives |
|---|---|
| Pin assignments | `#define` in `ArduinoCode.ino` |
| Gear bounds (GEAR_MIN, GEAR_MAX) | `#define` in `ArduinoCode.ino` |
| `currentGear` | `int currentGear` in `ArduinoCode.ino` — nowhere else |
| Debounce timing | `static const` inside the class that uses it |
| State machine logic | `ArduinoCode.ino` `loop()` and `applyState()` |
| Hardware output mapping | Inside the class that owns that output |
| Class API contracts | `.h` file |
| Class implementation | `.cpp` file |
| Architecture and pin table | `ArduinoCode/SYSTEM.md` |
