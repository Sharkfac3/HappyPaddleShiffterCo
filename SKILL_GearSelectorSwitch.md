# Skill: GearSelectorSwitch

## Purpose
Reads all 6 positions of the A340 inhibitor switch. Reports current state and fires one-shot entry flags on state changes.

## Pins
Pins 4–9, plain INPUT, active HIGH via voltage dividers (see SYSTEM.md).
Priority if multiple HIGH simultaneously: P > R > N > D > 2 > L.

## Enum
```cpp
enum GearSelectorState {
    GEAR_SEL_PARK, GEAR_SEL_REVERSE, GEAR_SEL_NEUTRAL,
    GEAR_SEL_DRIVE, GEAR_SEL_SECOND, GEAR_SEL_LOW,
    GEAR_SEL_UNKNOWN
};
```

## Behavior
- Call `update()` every loop
- 50ms debounce per pin (timestamp-based), triggers on rising edge
- `justEntered<X>()` returns true for exactly one loop cycle on entry to that state
- UNKNOWN = no pin active (transitioning between positions)

## Interface
```cpp
GearSelectorSwitch(int pinP, int pinR, int pinN, int pinD, int pin2, int pinL);
void begin();
void update();
GearSelectorState getState();
bool justEnteredPark();
bool justEnteredReverse();
bool justEnteredNeutral();
bool justEnteredDrive();
bool justEnteredSecond();
bool justEnteredLow();
```

## Private State
```cpp
int _pins[6];
GearSelectorState _state, _lastState;
int _lastReading[6];
unsigned long _lastChangeTime[6];
bool _stableHigh[6];
bool _justEntered[6];
static const unsigned long DEBOUNCE_MS = 50;
```
