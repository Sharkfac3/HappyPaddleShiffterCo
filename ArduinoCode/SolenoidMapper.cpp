#include "SolenoidMapper.h"

// =============================================================================
// SolenoidMapper.cpp
//
// Translates a logical gear number (1–5) into the correct S1 / S2 / SLU
// digital output states for the AW4 / A340E transmission.
//
// IMPORTANT — solenoids are NOT driven directly from Arduino pins.
// Solenoids run on 12V and can draw up to 2A each. Each output pin drives
// a channel on an external relay or high-side driver board. Flyback diodes
// (1N4007) are required across each solenoid coil to protect the driver board.
//
// Verified mapping (MaxxECU A340E docs + EveryCircuit AW4 community build):
//   Gear 1 (1st)        : S1=ON,  S2=OFF, SLU=OFF
//   Gear 2 (2nd)        : S1=ON,  S2=ON,  SLU=OFF
//   Gear 3 (3rd)        : S1=OFF, S2=ON,  SLU=OFF
//   Gear 4 (4th/OD)     : S1=OFF, S2=OFF, SLU=OFF  ← also electrical failsafe
//   Gear 5 (4th+Lockup) : S1=OFF, S2=OFF, SLU=ON
//
// SLU is digital on/off on this AW4 variant — NOT PWM.
// P/R/N call allOff() because solenoid state has no mechanical effect in
// those positions (reverse and park/neutral are purely hydraulic).
// =============================================================================

SolenoidMapper::SolenoidMapper(int pinS1, int pinS2, int pinSLU)
    : _pinS1(pinS1),
      _pinS2(pinS2),
      _pinSLU(pinSLU)
{}

// -----------------------------------------------------------------------------
// begin() — configure output pins and set all solenoids OFF.
// Must be called once in setup(). Calling allOff() here ensures the
// transmission starts in a safe, known state regardless of prior pin state.
// -----------------------------------------------------------------------------
void SolenoidMapper::begin() {
    pinMode(_pinS1,  OUTPUT);
    pinMode(_pinS2,  OUTPUT);
    pinMode(_pinSLU, OUTPUT);
    allOff();   // Safe startup default — transmission in electrical failsafe (4th)
}

// -----------------------------------------------------------------------------
// write() — private helper that applies three boolean states to the three pins.
// All solenoid state changes route through here for a single point of control.
// -----------------------------------------------------------------------------
void SolenoidMapper::write(bool s1, bool s2, bool slu) {
    digitalWrite(_pinS1,  s1  ? HIGH : LOW);
    digitalWrite(_pinS2,  s2  ? HIGH : LOW);
    digitalWrite(_pinSLU, slu ? HIGH : LOW);
}

// -----------------------------------------------------------------------------
// applyGear() — apply the solenoid pattern for the given gear.
//
// gear: 1 = 1st, 2 = 2nd, 3 = 3rd, 4 = 4th/OD, 5 = 4th+Lockup
// Any out-of-range gear calls allOff() as a safe fallback.
// -----------------------------------------------------------------------------
void SolenoidMapper::applyGear(int gear) {
    // Verified A340 solenoid truth table:
    // Gear | S1  | S2  | SLU
    //  1   | ON  | OFF | OFF
    //  2   | ON  | ON  | OFF
    //  3   | OFF | ON  | OFF
    //  4   | OFF | OFF | OFF   (also the electrical failsafe state)
    //  5   | OFF | OFF | ON    (4th + torque converter lockup)
    switch (gear) {
        case 1:  write(true,  false, false); break;
        case 2:  write(true,  true,  false); break;
        case 3:  write(false, true,  false); break;
        case 4:  write(false, false, false); break;
        case 5:  write(false, false, true);  break;
        default: allOff();                   break;  // Safe fallback for unexpected values
    }
}

// -----------------------------------------------------------------------------
// allOff() — de-energise all three solenoids.
// Called for Park, Reverse, Neutral, and any unknown/error state.
// Leaves the transmission in 4th gear electrically (the A340 failsafe state).
// -----------------------------------------------------------------------------
void SolenoidMapper::allOff() {
    write(false, false, false);
}
