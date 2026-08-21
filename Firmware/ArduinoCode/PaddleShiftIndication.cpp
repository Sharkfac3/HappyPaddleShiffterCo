#include "PaddleShiftIndication.h"

// =============================================================================
// PaddleShiftIndication.cpp
//
// Monitors two paddle-mounted IR slot optocoupler sensors (shift up, shift down)
// and exposes one-shot request flags to ArduinoCode.ino.
//
// Each sensor is an LM393-based slot-type IR photointerrupter (not a mechanical
// switch, not Hall effect) with a metal tab that sits IN the slot at rest.
// The sensor's DO pin is an ACTIVELY DRIVEN push-pull output — do NOT enable
// INPUT_PULLUP on these pins, the sensor drives the line itself.
//
// Tab in slot (rest) = DO LOW. Paddle pull clears the tab from the slot =
// DO HIGH. This is a LOW->HIGH rising edge on pull.
// Confirmed by multimeter on bench hardware 2026-08-20 (0V rest / 4.3V pulled) —
// opposite of the 2026-08-17 assumption this class originally shipped with.
// Source: SOURCES.md "Paddle Trigger Sensor — IR Slot-Type Optocoupler (LM393)".
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
      _lastUpReading(LOW),      // Unpressed at construction time (tab in slot = LOW)
      _lastDownReading(LOW),
      _confirmedUpState(LOW),
      _confirmedDownState(LOW),
      _lastUpTime(0),
      _lastDownTime(0)
{}

// -----------------------------------------------------------------------------
// begin() — configure pins as plain INPUT.
// Must be called once in setup() before any update() calls.
// -----------------------------------------------------------------------------
void PaddleShiftIndication::begin() {
    // Sensor DO output is actively driven (push-pull) — INPUT_PULLUP would
    // fight the sensor's own driver. Plain INPUT only.
    pinMode(_pinUp,   INPUT);
    pinMode(_pinDown, INPUT);
}

// -----------------------------------------------------------------------------
// update() — must be called every loop() iteration.
//
// Reads both paddle pins, applies 50ms debounce, and sets the corresponding
// flag on a confirmed rising edge (LOW → HIGH = physical press).
//
// Raw reading vs. confirmed state are tracked separately on purpose:
// _lastUpReading/_lastDownReading only exist to detect when the pin has
// changed (so the debounce timer can be reset). _confirmedUpState/
// _confirmedDownState hold the last value the debounce window actually
// promoted, and only THAT is compared for the edge — comparing against the
// raw reading instead (as this class originally did) means loop() runs many
// times faster than DEBOUNCE_MS, so the raw reading has already caught up
// to the new level long before the timer elapses, and the edge is never seen.
// -----------------------------------------------------------------------------
void PaddleShiftIndication::update() {
    unsigned long now = millis();

    // --- Shift Up ---
    int upReading = digitalRead(_pinUp);

    // Reset the debounce timer any time the raw reading changes
    if (upReading != _lastUpReading) {
        _lastUpTime    = now;
        _lastUpReading = upReading;
    }

    // Only promote once the reading has been stable for DEBOUNCE_MS
    if ((now - _lastUpTime) >= DEBOUNCE_MS && upReading != _confirmedUpState) {
        // Rising edge: was LOW (unpressed), now HIGH (pressed) — trigger shift
        if (upReading == HIGH && _confirmedUpState == LOW) {
            _upFlag = true;
        }
        _confirmedUpState = upReading;
    }

    // --- Shift Down (identical logic) ---
    int downReading = digitalRead(_pinDown);

    if (downReading != _lastDownReading) {
        _lastDownTime    = now;
        _lastDownReading = downReading;
    }

    if ((now - _lastDownTime) >= DEBOUNCE_MS && downReading != _confirmedDownState) {
        if (downReading == HIGH && _confirmedDownState == LOW) {
            _downFlag = true;
        }
        _confirmedDownState = downReading;
    }
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
