#include "PaddleShiftIndication.h"

// =============================================================================
// PaddleShiftIndication.cpp
//
// Monitors two momentary paddle switches (shift up, shift down) and exposes
// one-shot request flags to ArduinoCode.ino.
//
// Each switch is wired active LOW: one terminal to an Arduino INPUT_PULLUP
// pin, the other terminal to GND. Unpressed = HIGH, pressed = LOW.
//
// Debounce strategy: timestamp-based (not blocking).
// A press is only recognised when the LOW reading has been stable for at
// least DEBOUNCE_MS milliseconds. This prevents double-shifts from the
// mechanical bounce that is common in paddle switches.
//
// Each flag (_upFlag / _downFlag) is set once per physical press and is
// consumed-and-cleared by the matching shiftUpRequested() /
// shiftDownRequested() accessor. ArduinoCode.ino never needs to manually
// reset these flags.
// =============================================================================

PaddleShiftIndication::PaddleShiftIndication(int pinUp, int pinDown)
    : _pinUp(pinUp),
      _pinDown(pinDown),
      _upFlag(false),
      _downFlag(false),
      _lastUpState(HIGH),     // Unpressed at construction time
      _lastDownState(HIGH),
      _lastUpTime(0),
      _lastDownTime(0)
{}

// -----------------------------------------------------------------------------
// begin() — configure pins as INPUT_PULLUP.
// Must be called once in setup() before any update() calls.
// -----------------------------------------------------------------------------
void PaddleShiftIndication::begin() {
    // Switches are wired to GND — INPUT_PULLUP means HIGH = unpressed, LOW = pressed
    pinMode(_pinUp,   INPUT_PULLUP);
    pinMode(_pinDown, INPUT_PULLUP);
}

// -----------------------------------------------------------------------------
// update() — must be called every loop() iteration.
//
// Reads both paddle pins, applies 50ms debounce, and sets the corresponding
// flag on a confirmed falling edge (HIGH → LOW = physical press).
// -----------------------------------------------------------------------------
void PaddleShiftIndication::update() {
    unsigned long now = millis();

    // --- Shift Up ---
    int upState = digitalRead(_pinUp);

    // Reset the debounce timer any time the reading changes
    if (upState != _lastUpState) {
        _lastUpTime = now;
    }

    // Only act once the reading has been stable for DEBOUNCE_MS
    if ((now - _lastUpTime) >= DEBOUNCE_MS) {
        // Falling edge: was HIGH (unpressed), now LOW (pressed) — trigger shift
        if (upState == LOW && _lastUpState == HIGH) {
            _upFlag = true;
        }
    }

    _lastUpState = upState;  // Track for next cycle's edge detection

    // --- Shift Down (identical logic) ---
    int downState = digitalRead(_pinDown);

    if (downState != _lastDownState) {
        _lastDownTime = now;
    }

    if ((now - _lastDownTime) >= DEBOUNCE_MS) {
        if (downState == LOW && _lastDownState == HIGH) {
            _downFlag = true;
        }
    }

    _lastDownState = downState;
}

// -----------------------------------------------------------------------------
// shiftUpRequested() — returns true once per physical upshift press.
// Clears the internal flag on read, so subsequent calls return false until
// the next confirmed press.
// -----------------------------------------------------------------------------
bool PaddleShiftIndication::shiftUpRequested() {
    if (_upFlag) {
        _upFlag = false;
        return true;
    }
    return false;
}

// -----------------------------------------------------------------------------
// shiftDownRequested() — returns true once per physical downshift press.
// Same consume-and-clear semantics as shiftUpRequested().
// -----------------------------------------------------------------------------
bool PaddleShiftIndication::shiftDownRequested() {
    if (_downFlag) {
        _downFlag = false;
        return true;
    }
    return false;
}
