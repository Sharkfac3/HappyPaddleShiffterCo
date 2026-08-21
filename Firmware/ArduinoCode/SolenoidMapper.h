#ifndef SOLENOID_MAPPER_H
#define SOLENOID_MAPPER_H

#include <Arduino.h>

// SolenoidMapper
// Actuates S1, S2, and SLU solenoids based on the selected gear.
//
// Verified A340 solenoid mapping (MaxxECU A340E docs + EveryCircuit A340 community):
//   Gear 1 (1st)        : S1=ON,  S2=OFF, SLU=OFF
//   Gear 2 (2nd)        : S1=ON,  S2=ON,  SLU=OFF
//   Gear 3 (3rd)        : S1=OFF, S2=ON,  SLU=OFF
//   Gear 4 (4th/OD)     : S1=OFF, S2=OFF, SLU=OFF
//   Gear 5 (4th+Lockup) : S1=OFF, S2=OFF, SLU=ON
//
// Note: SLU on this A340 variant is a simple digital on/off solenoid (not PWM).
// Note: 4th gear (all off) is also the transmission's electrical failsafe state.

class SolenoidMapper {
public:
    SolenoidMapper(int pinS1, int pinS2, int pinSLU);

    void begin();

    // Apply solenoid state for gear 1-5
    // 1=1st, 2=2nd, 3=3rd, 4=4th(OD), 5=4th+Lockup
    void applyGear(int gear);

    // Turn all solenoids off (used in Park)
    void allOff();

private:
    int _pinS1;
    int _pinS2;
    int _pinSLU;

    void write(bool s1, bool s2, bool slu);
};

#endif
