#ifndef GEAR_SELECTOR_SWITCH_H
#define GEAR_SELECTOR_SWITCH_H

#include <Arduino.h>

// GearSelectorSwitch
// Reads the Jeep XJ AW4 neutral safety switch (NSS).
//
// The AW4 NSS is a CONTINUITY switch — NOT a 12V powered switch.
// Each selector position closes a specific pair of internal pins.
// No voltage dividers needed. Wire one side of each pair to an Arduino
// INPUT_PULLUP pin, the other side to GND. Active LOW logic.
//
// '87-'96 connector (8-pin Deutsch, pins A-H):
//   Park/Neutral : B<->C  → pinPN  (LOW in P and N — cannot distinguish)
//   Reverse      : A<->E  → pinR
//   3rd hold     : A<->G  → pin3
//   1-2 hold     : A<->H  → pin12
//   Drive        : no continuity → all pins HIGH = Drive
//
// '97-'01 connector: different physical connector, verify pinout from
// '97-'01 FSM before wiring. Same INPUT_PULLUP / active LOW logic applies.
//
// Drive is detected by ABSENCE of signal — no pin reads LOW.
// UNKNOWN = multiple pins LOW simultaneously (transitioning between positions).
//
// justEntered<X>() fires true for exactly one loop cycle on state entry.

enum GearSelectorState {
    GEAR_SEL_PARK_NEUTRAL,  // B<->C closed — Park and Neutral share this signal
    GEAR_SEL_REVERSE,       // A<->E closed
    GEAR_SEL_DRIVE,         // No continuity — detected by all pins HIGH
    GEAR_SEL_THIRD,         // A<->G closed — 1st through 3rd only
    GEAR_SEL_ONE_TWO,       // A<->H closed — 1st and 2nd only
    GEAR_SEL_UNKNOWN        // Multiple pins LOW — transitioning
};

class GearSelectorSwitch {
public:
    // Pin order: Park/Neutral, Reverse, 3rd hold, 1-2 hold
    GearSelectorSwitch(int pinPN, int pinR, int pin3, int pin12);

    void begin();

    // Must be called every loop iteration
    void update();

    GearSelectorState getState();

    // One-shot entry flags — true for exactly one loop cycle on state entry
    bool justEnteredParkNeutral();
    bool justEnteredReverse();
    bool justEnteredDrive();
    bool justEnteredThird();
    bool justEnteredOneTwo();

private:
    static const int NUM_PINS = 4;
    int _pins[NUM_PINS];

    GearSelectorState _state;
    GearSelectorState _lastState;

    int           _lastReading[NUM_PINS];
    unsigned long _lastChangeTime[NUM_PINS];
    bool          _stableLow[NUM_PINS];   // true = pin is stably LOW (active)

    bool _justEnteredParkNeutral;
    bool _justEnteredReverse;
    bool _justEnteredDrive;
    bool _justEnteredThird;
    bool _justEnteredOneTwo;

    static const unsigned long DEBOUNCE_MS = 50;

    GearSelectorState resolveState();
};

// Pin index constants
#define IDX_PN  0   // Park / Neutral
#define IDX_R   1   // Reverse
#define IDX_3   2   // 3rd hold
#define IDX_12  3   // 1-2 hold

#endif
