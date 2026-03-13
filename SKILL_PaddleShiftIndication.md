# Skill: PaddleShiftIndication

## Purpose
Detects debounced shift up/down paddle presses and exposes one-shot flags to ArduinoCode.ino.

## Pins
- Shift Up: pin 2, INPUT_PULLUP, active LOW
- Shift Down: pin 3, INPUT_PULLUP, active LOW

## Behavior
- Call `update()` every loop to sample inputs
- Trigger on falling edge (HIGH→LOW)
- 50ms debounce window (timestamp-based)
- `shiftUpRequested()` / `shiftDownRequested()` return true once per physical press, then auto-reset

## Interface
```cpp
PaddleShiftIndication(int pinUp, int pinDown);
void begin();
void update();
bool shiftUpRequested();
bool shiftDownRequested();
```

## Private State
```cpp
bool _upFlag, _downFlag;
int _lastUpState, _lastDownState;
unsigned long _lastUpTime, _lastDownTime;
static const unsigned long DEBOUNCE_MS = 50;
```
