#include "PaddleShiftIndication.h"

PaddleShiftIndication::PaddleShiftIndication(int pinUp, int pinDown)
    : _pinUp(pinUp),
      _pinDown(pinDown),
      _upFlag(false),
      _downFlag(false),
      _lastUpState(HIGH),
      _lastDownState(HIGH),
      _lastUpTime(0),
      _lastDownTime(0)
{}

void PaddleShiftIndication::begin() {
    // Switches are wired to GND — INPUT_PULLUP means HIGH = unpressed, LOW = pressed
    pinMode(_pinUp, INPUT_PULLUP);
    pinMode(_pinDown, INPUT_PULLUP);
}

void PaddleShiftIndication::update() {
    unsigned long now = millis();

    // --- Shift Up ---
    int upState = digitalRead(_pinUp);
    if (upState != _lastUpState) {
        _lastUpTime = now;
    }
    if ((now - _lastUpTime) >= DEBOUNCE_MS) {
        // Stable reading — trigger on falling edge (HIGH -> LOW = press)
        if (upState == LOW && _lastUpState == HIGH) {
            _upFlag = true;
        }
    }
    _lastUpState = upState;

    // --- Shift Down ---
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

bool PaddleShiftIndication::shiftUpRequested() {
    if (_upFlag) {
        _upFlag = false;
        return true;
    }
    return false;
}

bool PaddleShiftIndication::shiftDownRequested() {
    if (_downFlag) {
        _downFlag = false;
        return true;
    }
    return false;
}
