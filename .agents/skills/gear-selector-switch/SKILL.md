---
name: gear-selector-switch
description: Modify or debug the GearSelectorSwitch class — the AW4 neutral safety switch (NSS) reader for the Jeep XJ paddle shifter controller. Use when changing selector position detection, debounce logic, state enum values, or one-shot entry flag behaviour. Source files are ArduinoCode/GearSelectorSwitch.h and ArduinoCode/GearSelectorSwitch.cpp.
---

# Skill: gear-selector-switch

Reads the AW4 neutral safety switch (NSS) and resolves the current selector position
into a `GearSelectorState` enum value with one-shot entry flags.

## Key Electrical Facts

The AW4 NSS is a **continuity switch** — NOT a 12V powered switch.
Each selector position closes a specific pair of internal pins.
All pins are wired as `INPUT_PULLUP`. Active LOW (LOW = that pair is closed).
Drive is detected by the **absence** of any signal — all pins HIGH.

| Position | NSS Pins Closed | Arduino Pin | Active when |
|---|---|---|---|
| Park / Neutral | B ↔ C | 4 | LOW |
| Reverse | A ↔ E | 5 | LOW |
| 3rd hold | A ↔ G | 6 | LOW |
| 1-2 hold | A ↔ H | 7 | LOW |
| Drive | none | — | all pins HIGH |

Park and Neutral share the same NSS signal (B↔C). They cannot be distinguished
by the switch alone. Both are reported as `GEAR_SEL_PARK_NEUTRAL`.

## Source Files

- `ArduinoCode/GearSelectorSwitch.h` — enum definition, class declaration, `IDX_*` constants
- `ArduinoCode/GearSelectorSwitch.cpp` — debounce logic, state resolution, one-shot flags

## State Enum

```cpp
enum GearSelectorState {
    GEAR_SEL_PARK_NEUTRAL,  // B↔C closed — Park and Neutral share this signal
    GEAR_SEL_REVERSE,       // A↔E closed
    GEAR_SEL_DRIVE,         // No continuity — detected by absence of all signals
    GEAR_SEL_THIRD,         // A↔G closed — 1st through 3rd only
    GEAR_SEL_ONE_TWO,       // A↔H closed — 1st and 2nd only
    GEAR_SEL_UNKNOWN        // Multiple pins LOW — transitioning between positions
};
```

## Public Interface

```cpp
GearSelectorSwitch(int pinPN, int pinR, int pin3, int pin12);
void begin();                     // Call once in setup()
void update();                    // Call every loop() iteration
GearSelectorState getState();
bool justEnteredParkNeutral();    // True for exactly one loop() cycle on entry
bool justEnteredReverse();
bool justEnteredDrive();
bool justEnteredThird();
bool justEnteredOneTwo();
```

## Private State (for reference when modifying internals)

```cpp
int _pins[4];                     // Indexed by IDX_PN, IDX_R, IDX_3, IDX_12
GearSelectorState _state, _lastState;
int _lastReading[4];
unsigned long _lastChangeTime[4];
bool _stableLow[4];               // true = pin has been stably LOW for >= DEBOUNCE_MS
static const unsigned long DEBOUNCE_MS = 50;
```

## Behaviour Notes

- `update()` must be called every `loop()` iteration — debounce is timestamp-based, not blocking
- Trigger on falling edge (HIGH→LOW) — matches INPUT_PULLUP / active LOW wiring
- UNKNOWN fires when more than one pin is stably LOW simultaneously (selector mid-travel)
  — there is no priority chain; any multi-pin state is treated as a transient
- `justEntered<X>()` flags auto-clear on the next `update()` call; ArduinoCode.ino does not need to reset them

## Usage Pattern in ArduinoCode.ino

```cpp
selector.update();

if (selector.justEnteredDrive()) {
    // Runs once on transition into Drive
}

switch (selector.getState()) {
    case GEAR_SEL_DRIVE:
        // Ongoing Drive handling
        break;
    // ...
}
```
