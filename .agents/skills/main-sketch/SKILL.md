---
name: main-sketch
description: >
  Modify or debug ArduinoCode.ino — the main sketch that owns the state machine,
  setup(), loop(), and applyState() for the Jeep XJ AW4 paddle shifter controller.
  Use this skill when making changes that span multiple classes or touch the core
  loop logic, state transitions, or startup initialisation. For single-class changes,
  load the relevant class skill instead.
---

# Skill: main-sketch

The top-level orchestrator. `ArduinoCode.ino` owns:
- `currentGear` (the single source of truth for selected gear, 1–5)
- `setup()` — initialises all four class instances, calls `applyState()`
- `loop()` — samples inputs, runs one-shot transition handlers, runs ongoing state switch
- `applyState()` — sets initial display and solenoid state at power-on

## Class Instances (declared at file scope)

```cpp
PaddleShiftIndication paddle(PIN_SHIFT_UP, PIN_SHIFT_DOWN);   // pins 2, 3
GearSelectorSwitch selector(PIN_NSS_PN, PIN_NSS_R, PIN_NSS_3, PIN_NSS_12); // pins 4,5,6,7
SolenoidMapper solenoids(PIN_S1, PIN_S2, PIN_SLU);            // pins 11, 12, 13
ScreenIndication screen(PIN_LCD_CS, PIN_LCD_DC, PIN_LCD_RST); // A5, A4, A3
```

## loop() Structure — Ordering Constraints

The order of operations in `loop()` is critical:

```
1. paddle.update()    — must be first; samples paddle pins, updates flags
2. selector.update()  — must be second; samples NSS pins, updates state + flags
3. justEntered*() checks — must come before getState() switch
4. switch(state) block — ongoing state handling
```

**Never reorder these.** `justEntered*()` flags are set by `update()` and cleared on
the next `update()` call. Reading them before `update()` gives stale data.

## One-Shot Handlers (justEntered*)

Each `justEntered*()` handler ends with `return` to exit `loop()` immediately after
a state transition. This prevents the `switch(state)` block below from also processing
the same cycle.

Do not remove the `return` statements. Do not add additional logic after a `return`.

### justEnteredParkNeutral()
```cpp
solenoids.allOff();
screen.showPark();
// DO NOT reset currentGear here — see DECISIONS.md ADR-001
return;
```

### justEnteredReverse()
```cpp
currentGear = 1;    // CORRECT — Reverse always starts fresh in 1st
solenoids.allOff();
screen.showReverse();
return;
```

### justEnteredDrive()
```cpp
solenoids.applyGear(currentGear);   // Re-applies preserved gear
screen.showGear(currentGear);
return;
```

### justEnteredThird()
```cpp
if (currentGear > 3) currentGear = 3;   // Clamp to max 3rd
solenoids.applyGear(currentGear);
screen.showNeutral(); // Known issue — shows "N" not "3". See screen-indication skill.
return;
```

### justEnteredOneTwo()
```cpp
if (currentGear > 2) currentGear = 2;   // Clamp to max 2nd
solenoids.applyGear(currentGear);
screen.showGear(2);
return;
```

## applyState() — Startup Initialisation Only

`applyState()` is called once from `setup()`. It is NOT called from `loop()`.
It handles the case where the vehicle is powered on mid-drive (selector not in Park).

`applyState()` is the ONLY place where `currentGear = 1` is set for
`GEAR_SEL_PARK_NEUTRAL`. This is correct — there is no previous gear at power-on.
Do not duplicate this reset anywhere else.

## GEAR_MIN / GEAR_MAX

```cpp
#define GEAR_MIN  1   // Cannot shift below 1st
#define GEAR_MAX  5   // Cannot shift above 4th+Lockup
```

Shift requests outside these bounds are silently ignored:
```cpp
if (wantUp && currentGear < GEAR_MAX) { currentGear++; ... }
if (wantDown && currentGear > GEAR_MIN) { currentGear--; ... }
```

## Known Issues

- **3rd hold shows "N" on the display** instead of "3".
  `justEnteredThird()` calls `screen.showNeutral()` as a placeholder.
  Fix: add `showThird()` to `ScreenIndication` (see `screen-indication` skill),
  then replace `screen.showNeutral()` in both `justEnteredThird()` and the
  `GEAR_SEL_THIRD` case in `applyState()`.

## Adding a New Selector State

1. Add the new value to `GearSelectorState` enum in `GearSelectorSwitch.h`
2. Add `justEntered<NewState>()` to `GearSelectorSwitch.h/.cpp`
3. Add the one-shot handler in `loop()` (with `return`)
4. Add the ongoing case in `switch(state)` in `loop()`
5. Add the startup case in `applyState()`
6. Update `ArduinoCode/SYSTEM.md` state machine table
7. Drop a handoff in `.agents/HANDOFFS.md` for the documentation role
