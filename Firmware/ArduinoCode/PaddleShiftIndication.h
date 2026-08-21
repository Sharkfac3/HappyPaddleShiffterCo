#ifndef PADDLE_SHIFT_INDICATION_H
#define PADDLE_SHIFT_INDICATION_H

#include <Arduino.h>

// PaddleShiftIndication
// Monitors shift up and shift down paddle IR slot optocoupler sensors
// (LM393-based, tab-in-slot-at-rest) wired to the Arduino as plain INPUT
// (sensor output is actively driven, not open-drain).
// Rest (tab in slot) = LOW. Paddle pull = HIGH. Triggers on LOW->HIGH rising
// edge. Confirmed by multimeter on bench hardware 2026-08-20.
// Applies 50ms software debounce as a safety margin against edge noise.
//
// Call update() every loop. Read shiftUpRequested() / shiftDownRequested()
// to check for a pending shift — each returns true only once per physical press.

class PaddleShiftIndication {
public:
    PaddleShiftIndication(int pinUp, int pinDown);

    void begin();

    // Must be called every loop iteration to sample switch states
    void update();

    // Returns true once per physical upshift press, then resets
    bool shiftUpRequested();

    // Returns true once per physical downshift press, then resets
    bool shiftDownRequested();

private:
    int _pinUp;
    int _pinDown;

    bool _upFlag;
    bool _downFlag;

    // Raw last reading (for detecting a change, to reset the debounce timer)
    int _lastUpReading;
    int _lastDownReading;

    // Last reading actually promoted by the debounce window (used for edge detection)
    int _confirmedUpState;
    int _confirmedDownState;

    unsigned long _lastUpTime;
    unsigned long _lastDownTime;

    static const unsigned long DEBOUNCE_MS = 50;
};

#endif
