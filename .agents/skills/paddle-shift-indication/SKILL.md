---
name: paddle-shift-indication
description: Modify or debug the PaddleShiftIndication class — the debounced paddle switch reader for the Jeep XJ paddle shifter controller. Use when changing shift input pins, debounce timing, or the one-shot flag behaviour for upshift/downshift requests. Source files are Firmware/ArduinoCode/PaddleShiftIndication.h and Firmware/ArduinoCode/PaddleShiftIndication.cpp.
---

# Skill: paddle-shift-indication

Monitors two paddle-mounted IR slot optocoupler sensors (shift up, shift down,
LM393-based — NOT mechanical switches, NOT Hall effect) and exposes debounced
one-shot request flags to `ArduinoCode.ino`.

## Key Electrical Facts

- Sensor DO output is **actively driven (push-pull)** — pins are plain `INPUT`, NOT `INPUT_PULLUP`. Enabling the internal pull-up would fight the sensor's own driver.
- Metal tab sits **IN the slot at rest** → DO reads LOW. Paddle pull clears the tab from the slot → DO reads HIGH. LOW→HIGH rising edge triggers the debounce/edge-detection logic. **Confirmed by multimeter on bench hardware 2026-08-20** (0V rest / 4.3V pulled) — opposite of the original 2026-08-17 assumption this class shipped with; that assumption is now known wrong for this hardware.
- Debounce is timestamp-based (non-blocking) — 50ms settle window
- Source: `SOURCES.md` → "Paddle Trigger Sensor — IR Slot-Type Optocoupler (LM393), User-Owned Part" (flagged for a Research-role correction — see HANDOFFS.md)

| Function | Arduino Pin | Mode |
|---|---|---|
| Shift Up | 2 | plain INPUT — sensor-driven, rest = LOW |
| Shift Down | 3 | plain INPUT — sensor-driven, rest = LOW |

## Source Files

- `Firmware/ArduinoCode/PaddleShiftIndication.h` — class declaration
- `Firmware/ArduinoCode/PaddleShiftIndication.cpp` — debounce logic, flag set/clear

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
int _lastUpReading, _lastDownReading;        // raw reading, resets the debounce timer on change
int _confirmedUpState, _confirmedDownState;  // debounce-promoted state, used for edge detection
unsigned long _lastUpTime, _lastDownTime;
static const unsigned long DEBOUNCE_MS = 50;
```

**Why two state variables per pin, not one:** comparing the edge against the raw reading (as
this class did until 2026-08-20) is a latent bug — `loop()` runs far faster than `DEBOUNCE_MS`,
so the raw reading catches up to the new level long before the timer elapses, and the promoted
edge is never seen. `_confirmedUpState`/`_confirmedDownState` only change when the debounce
window actually closes, so the edge check compares against the truly-last-stable value, not
last loop iteration's value.

## Behaviour Notes

- `update()` must be called every `loop()` — debounce is timestamp-based, not blocking
- Trigger on **rising edge** (LOW→HIGH = physical press)
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
