---
name: paddle-shift-indication
description: Modify or debug the PaddleShiftIndication class — the debounced paddle switch reader for the Jeep XJ paddle shifter controller. Use when changing shift input pins, debounce timing, or the one-shot flag behaviour for upshift/downshift requests. Source files are ArduinoCode/PaddleShiftIndication.h and ArduinoCode/PaddleShiftIndication.cpp.
---

# Skill: paddle-shift-indication

Monitors two momentary paddle switches (shift up, shift down) and exposes
debounced one-shot request flags to `ArduinoCode.ino`.

## Key Electrical Facts

- Both switches wired **active LOW**: one terminal to an Arduino `INPUT_PULLUP` pin, other terminal to GND
- Unpressed = HIGH, pressed = LOW
- Debounce is timestamp-based (non-blocking) — 50ms settle window

| Function | Arduino Pin | Mode |
|---|---|---|
| Shift Up | 2 | INPUT_PULLUP, active LOW |
| Shift Down | 3 | INPUT_PULLUP, active LOW |

## Source Files

- `ArduinoCode/PaddleShiftIndication.h` — class declaration
- `ArduinoCode/PaddleShiftIndication.cpp` — debounce logic, flag set/clear

## Public Interface

```cpp
PaddleShiftIndication(int pinUp, int pinDown);
void begin();                  // Call once in setup() — configures INPUT_PULLUP
void update();                 // Call every loop() iteration — samples pins, updates flags
bool shiftUpRequested();       // Returns true once per physical press, then auto-resets
bool shiftDownRequested();     // Returns true once per physical press, then auto-resets
```

## Private State (for reference when modifying internals)

```cpp
bool _upFlag, _downFlag;
int _lastUpState, _lastDownState;
unsigned long _lastUpTime, _lastDownTime;
static const unsigned long DEBOUNCE_MS = 50;
```

## Behaviour Notes

- `update()` must be called every `loop()` — debounce is timestamp-based, not blocking
- Trigger on **falling edge** (HIGH→LOW = physical press)
- Each flag is consumed-and-cleared by its accessor — `ArduinoCode.ino` never needs to reset flags manually
- A held paddle does NOT produce repeated shift events — only the initial press edge triggers the flag

## Usage Pattern in ArduinoCode.ino

```cpp
paddle.update();

if (paddle.shiftUpRequested() && currentGear < GEAR_MAX) {
    currentGear++;
    solenoids.applyGear(currentGear);
}
if (paddle.shiftDownRequested() && currentGear > GEAR_MIN) {
    currentGear--;
    solenoids.applyGear(currentGear);
}
```
