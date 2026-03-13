#ifndef GEAR_SELECTOR_SWITCH_H
#define GEAR_SELECTOR_SWITCH_H

#include <Arduino.h>

// GearSelectorSwitch
// Reads the Toyota A340 9-pin inhibitor switch (neutral start switch).
//
// The factory switch outputs 12V on each position wire — these MUST be
// converted to 5V logic via voltage dividers before connecting to Arduino:
//   10kΩ from signal wire → Arduino pin
//   4.7kΩ from Arduino pin → GND
//   Result: ~3.8V (safe HIGH for Arduino 5V logic)
//
// Only one position pin should be HIGH at a time. If none are HIGH, the
// selector is transitioning between positions → UNKNOWN state.
//
// justEntered<X>() returns true for exactly one loop cycle on state entry,
// useful for one-shot actions (e.g. resetting gear to 1st on Park/Reverse).

enum GearSelectorState {
    GEAR_SEL_PARK,
    GEAR_SEL_REVERSE,
    GEAR_SEL_NEUTRAL,
    GEAR_SEL_DRIVE,
    GEAR_SEL_SECOND,
    GEAR_SEL_LOW,
    GEAR_SEL_UNKNOWN   // Transitioning — no pin active
};

class GearSelectorSwitch {
public:
    // Pin order: Park, Reverse, Neutral, Drive, Second, Low
    GearSelectorSwitch(int pinP, int pinR, int pinN, int pinD, int pin2, int pinL);

    void begin();

    // Must be called every loop iteration
    void update();

    GearSelectorState getState();

    // One-shot entry flags — true for exactly one loop cycle on state entry
    bool justEnteredPark();
    bool justEnteredReverse();
    bool justEnteredNeutral();
    bool justEnteredDrive();
    bool justEnteredSecond();
    bool justEnteredLow();

private:
    int _pins[6];   // P, R, N, D, 2, L

    GearSelectorState _state;
    GearSelectorState _lastState;

    // Debounce tracking per pin
    int           _lastReading[6];
    unsigned long _lastChangeTime[6];
    bool          _stableHigh[6];

    // One-shot flags
    bool _justEnteredPark;
    bool _justEnteredReverse;
    bool _justEnteredNeutral;
    bool _justEnteredDrive;
    bool _justEnteredSecond;
    bool _justEnteredLow;

    static const unsigned long DEBOUNCE_MS = 50;

    GearSelectorState resolveState();
};

#endif
