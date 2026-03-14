#include "GearSelectorSwitch.h"

// =============================================================================
// GearSelectorSwitch.cpp
//
// Reads the AW4 neutral safety switch (NSS) and resolves the current
// selector position into a GearSelectorState enum value.
//
// The AW4 NSS is a continuity switch — each selector position closes a
// specific pair of internal pins. No voltage dividers or 12V power needed.
// Arduino INPUT_PULLUP pins read LOW when the corresponding pair is closed.
//
// Drive is the absence of any signal: all four monitored pins read HIGH.
// UNKNOWN is the presence of more than one signal simultaneously: this is
// a transient state that occurs while the selector is physically moving.
//
// One-shot justEntered<X>() flags are set for exactly one loop() cycle
// on each state transition, then cleared on the next update() call.
// =============================================================================

GearSelectorSwitch::GearSelectorSwitch(int pinPN, int pinR, int pin3, int pin12)
    : _state(GEAR_SEL_UNKNOWN),
      _lastState(GEAR_SEL_UNKNOWN),
      _justEnteredParkNeutral(false),
      _justEnteredReverse(false),
      _justEnteredDrive(false),
      _justEnteredThird(false),
      _justEnteredOneTwo(false)
{
    // Store pins in index order matching the IDX_* constants
    _pins[IDX_PN] = pinPN;
    _pins[IDX_R]  = pinR;
    _pins[IDX_3]  = pin3;
    _pins[IDX_12] = pin12;

    // Default debounce state: treat all pins as HIGH (no continuity / stable)
    for (int i = 0; i < NUM_PINS; i++) {
        _lastReading[i]    = HIGH;
        _lastChangeTime[i] = 0;
        _stableLow[i]      = false;
    }
}

// -----------------------------------------------------------------------------
// begin() — configure pins and snapshot initial state.
// Must be called once in setup() before any update() calls.
// -----------------------------------------------------------------------------
void GearSelectorSwitch::begin() {
    for (int i = 0; i < NUM_PINS; i++) {
        // INPUT_PULLUP: HIGH = open / no continuity, LOW = NSS pair closed
        pinMode(_pins[i], INPUT_PULLUP);

        // Snapshot the current reading so debounce tracking starts from reality
        _lastReading[i] = digitalRead(_pins[i]);

        // If a pin is already LOW at startup, treat it as immediately stable
        // (no need to wait DEBOUNCE_MS on power-on — the switch has been settled)
        _stableLow[i] = (_lastReading[i] == LOW);
    }

    // Resolve and latch initial state so justEntered flags don't fire spuriously
    _state     = resolveState();
    _lastState = _state;
}

// -----------------------------------------------------------------------------
// update() — must be called every loop() iteration.
//
// Steps:
//   1. Debounce each pin independently (50ms timestamp method).
//   2. Resolve the new state from stable pin readings.
//   3. Compute one-shot justEntered<X>() flags for this cycle.
// -----------------------------------------------------------------------------
void GearSelectorSwitch::update() {
    unsigned long now = millis();

    // --- Step 1: Per-pin debounce ---
    for (int i = 0; i < NUM_PINS; i++) {
        int reading = digitalRead(_pins[i]);

        // If the reading changed from last cycle, reset the timer
        if (reading != _lastReading[i]) {
            _lastChangeTime[i] = now;
            _lastReading[i]    = reading;
        }

        // Only promote to stable once the reading has held for DEBOUNCE_MS
        if ((now - _lastChangeTime[i]) >= DEBOUNCE_MS) {
            _stableLow[i] = (reading == LOW);
        }
        // If still within the debounce window, _stableLow[i] retains its last
        // promoted value — the pin is considered to be in its previous stable state
        // until the new reading settles.
    }

    // --- Step 2: Resolve new state ---
    _lastState = _state;
    _state     = resolveState();

    // --- Step 3: One-shot entry flags ---
    // Each flag is true for exactly one loop() cycle after the state changes.
    // ArduinoCode.ino consumes them and does NOT need to clear them — they are
    // automatically reset on the next update() call because _lastState updates.
    _justEnteredParkNeutral = (_state == GEAR_SEL_PARK_NEUTRAL && _lastState != GEAR_SEL_PARK_NEUTRAL);
    _justEnteredReverse     = (_state == GEAR_SEL_REVERSE      && _lastState != GEAR_SEL_REVERSE);
    _justEnteredDrive       = (_state == GEAR_SEL_DRIVE        && _lastState != GEAR_SEL_DRIVE);
    _justEnteredThird       = (_state == GEAR_SEL_THIRD        && _lastState != GEAR_SEL_THIRD);
    _justEnteredOneTwo      = (_state == GEAR_SEL_ONE_TWO      && _lastState != GEAR_SEL_ONE_TWO);
}

// -----------------------------------------------------------------------------
// resolveState() — maps stable pin readings to a GearSelectorState.
//
// Rules:
//   - More than one pin stably LOW → UNKNOWN (physical transition in progress)
//   - Exactly one pin LOW          → the matching named position
//   - No pins LOW                  → DRIVE (detected by absence of signal)
// -----------------------------------------------------------------------------
GearSelectorState GearSelectorSwitch::resolveState() {
    // Count how many pins are currently reading as stably LOW
    int activePins = 0;
    for (int i = 0; i < NUM_PINS; i++) {
        if (_stableLow[i]) activePins++;
    }

    // More than one active simultaneously means the selector is mid-travel
    if (activePins > 1) return GEAR_SEL_UNKNOWN;

    // Exactly one active — identify which position it corresponds to
    if (_stableLow[IDX_PN]) return GEAR_SEL_PARK_NEUTRAL;
    if (_stableLow[IDX_R])  return GEAR_SEL_REVERSE;
    if (_stableLow[IDX_3])  return GEAR_SEL_THIRD;
    if (_stableLow[IDX_12]) return GEAR_SEL_ONE_TWO;

    // No pins active — Drive is indicated by the absence of any continuity
    return GEAR_SEL_DRIVE;
}

// -----------------------------------------------------------------------------
// Public accessors — all trivial, documented in header
// -----------------------------------------------------------------------------
GearSelectorState GearSelectorSwitch::getState()           { return _state; }
bool GearSelectorSwitch::justEnteredParkNeutral()          { return _justEnteredParkNeutral; }
bool GearSelectorSwitch::justEnteredReverse()              { return _justEnteredReverse; }
bool GearSelectorSwitch::justEnteredDrive()                { return _justEnteredDrive; }
bool GearSelectorSwitch::justEnteredThird()                { return _justEnteredThird; }
bool GearSelectorSwitch::justEnteredOneTwo()               { return _justEnteredOneTwo; }
