#include "SolenoidMapper.h"

SolenoidMapper::SolenoidMapper(int pinS1, int pinS2, int pinSLU)
    : _pinS1(pinS1),
      _pinS2(pinS2),
      _pinSLU(pinSLU)
{}

void SolenoidMapper::begin() {
    pinMode(_pinS1,  OUTPUT);
    pinMode(_pinS2,  OUTPUT);
    pinMode(_pinSLU, OUTPUT);
    allOff();
}

void SolenoidMapper::write(bool s1, bool s2, bool slu) {
    digitalWrite(_pinS1,  s1  ? HIGH : LOW);
    digitalWrite(_pinS2,  s2  ? HIGH : LOW);
    digitalWrite(_pinSLU, slu ? HIGH : LOW);
}

void SolenoidMapper::applyGear(int gear) {
    // Verified A340 mapping:
    // Gear | S1  | S2  | SLU
    //  1   | ON  | OFF | OFF
    //  2   | ON  | ON  | OFF
    //  3   | OFF | ON  | OFF
    //  4   | OFF | OFF | OFF
    //  5   | OFF | OFF | ON   (4th + lockup)
    switch (gear) {
        case 1:  write(true,  false, false); break;
        case 2:  write(true,  true,  false); break;
        case 3:  write(false, true,  false); break;
        case 4:  write(false, false, false); break;
        case 5:  write(false, false, true);  break;
        default: allOff();                   break;
    }
}

void SolenoidMapper::allOff() {
    write(false, false, false);
}
