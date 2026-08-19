---
name: paddle-shift-indication
description: Modify or debug the PaddleShiftIndication class — the debounced paddle switch reader for the Jeep XJ paddle shifter controller. Use when changing shift input pins, debounce timing, or the one-shot flag behaviour for upshift/downshift requests. Source files are Firmware/PaddleShiftIndication.h and Firmware/PaddleShiftIndication.cpp.
---

# Skill: paddle-shift-indication

Monitors two paddle-mounted IR slot optocoupler sensors (shift up, shift down,
LM393-based — NOT mechanical switches, NOT Hall effect) and exposes debounced
one-shot request flags to `ArduinoCode.ino`.

## Key Electrical Facts

- Sensor DO output is **actively driven (push-pull)** — pins are plain `INPUT`, NOT `INPUT_PULLUP`. Enabling the internal pull-up would fight the sensor's own driver.
- Metal tab sits **IN the slot at rest** → DO reads HIGH. Paddle pull clears the tab from the slot → DO reads LOW. Same HIGH→LOW falling edge the debounce/edge-detection logic already expects.
- Debounce is timestamp-based (non-blocking) — 50ms settle window
- Source: `SOURCES.md` → "Paddle Trigger Sensor — IR Slot-Type Optocoupler (LM393), User-Owned Part"

| Function | Arduino Pin | Mode |
|---|---|---|
| Shift Up | 2 | plain INPUT — sensor-driven, rest = HIGH |
| Shift Down | 3 | plain INPUT — sensor-driven, rest = HIGH |

## Source Files

- `Firmware/PaddleShiftIndication.h` — class declaration
- `Firmware/PaddleShiftIndication.cpp` — debounce logic, flag set/clear

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
