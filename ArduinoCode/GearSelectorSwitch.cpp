#include "GearSelectorSwitch.h"

// Pin index constants for readability
#define IDX_P  0
#define IDX_R  1
#define IDX_N  2
#define IDX_D  3
#define IDX_2  4
#define IDX_L  5

GearSelectorSwitch::GearSelectorSwitch(int pinP, int pinR, int pinN, int pinD, int pin2, int pinL)
    : _state(GEAR_SEL_UNKNOWN),
      _lastState(GEAR_SEL_UNKNOWN),
      _justEnteredPark(false),
      _justEnteredReverse(false),
      _justEnteredNeutral(false),
      _justEnteredDrive(false),
      _justEnteredSecond(false),
      _justEnteredLow(false)
{
    _pins[IDX_P] = pinP;
    _pins[IDX_R] = pinR;
    _pins[IDX_N] = pinN;
    _pins[IDX_D] = pinD;
    _pins[IDX_2] = pin2;
    _pins[IDX_L] = pinL;

    for (int i = 0; i < 6; i++) {
        _lastReading[i]    = LOW;
        _lastChangeTime[i] = 0;
        _stableHigh[i]     = false;
    }
}

void GearSelectorSwitch::begin() {
    for (int i = 0; i < 6; i++) {
        // Plain INPUT — signals come in via voltage dividers, not pulled up internally
        pinMode(_pins[i], INPUT);
    }
    // Sample initial state immediately
    for (int i = 0; i < 6; i++) {
        _lastReading[i] = digitalRead(_pins[i]);
        _stableHigh[i]  = (_lastReading[i] == HIGH);
    }
    _state     = resolveState();
    _lastState = _state;
}

void GearSelectorSwitch::update() {
    unsigned long now = millis();

    // Debounce each pin independently
    for (int i = 0; i < 6; i++) {
        int reading = digitalRead(_pins[i]);
        if (reading != _lastReading[i]) {
            _lastChangeTime[i] = now;
            _lastReading[i]    = reading;
        }
        if ((now - _lastChangeTime[i]) >= DEBOUNCE_MS) {
            _stableHigh[i] = (reading == HIGH);
        }
    }

    // Resolve new state from stable readings
    _lastState = _state;
    _state     = resolveState();

    // Update one-shot entry flags
    _justEnteredPark    = (_state == GEAR_SEL_PARK    && _lastState != GEAR_SEL_PARK);
    _justEnteredReverse = (_state == GEAR_SEL_REVERSE && _lastState != GEAR_SEL_REVERSE);
    _justEnteredNeutral = (_state == GEAR_SEL_NEUTRAL && _lastState != GEAR_SEL_NEUTRAL);
    _justEnteredDrive   = (_state == GEAR_SEL_DRIVE   && _lastState != GEAR_SEL_DRIVE);
    _justEnteredSecond  = (_state == GEAR_SEL_SECOND  && _lastState != GEAR_SEL_SECOND);
    _justEnteredLow     = (_state == GEAR_SEL_LOW     && _lastState != GEAR_SEL_LOW);
}

GearSelectorState GearSelectorSwitch::resolveState() {
    // Priority order: Park > Reverse > Neutral > Drive > Second > Low
    // Only one should be HIGH at a time under normal operation.
    // If multiple are HIGH (wiring fault), Park takes priority for safety.
    if (_stableHigh[IDX_P]) return GEAR_SEL_PARK;
    if (_stableHigh[IDX_R]) return GEAR_SEL_REVERSE;
    if (_stableHigh[IDX_N]) return GEAR_SEL_NEUTRAL;
    if (_stableHigh[IDX_D]) return GEAR_SEL_DRIVE;
    if (_stableHigh[IDX_2]) return GEAR_SEL_SECOND;
    if (_stableHigh[IDX_L]) return GEAR_SEL_LOW;
    return GEAR_SEL_UNKNOWN;
}

GearSelectorState GearSelectorSwitch::getState() { return _state; }

bool GearSelectorSwitch::justEnteredPark()    { return _justEnteredPark;    }
bool GearSelectorSwitch::justEnteredReverse() { return _justEnteredReverse; }
bool GearSelectorSwitch::justEnteredNeutral() { return _justEnteredNeutral; }
bool GearSelectorSwitch::justEnteredDrive()   { return _justEnteredDrive;   }
bool GearSelectorSwitch::justEnteredSecond()  { return _justEnteredSecond;  }
bool GearSelectorSwitch::justEnteredLow()     { return _justEnteredLow;     }
