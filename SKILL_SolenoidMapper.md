# Skill: SolenoidMapper

## Purpose
Translates gear number (1–5) into S1/S2/SLU digital outputs. All solenoids driven via external relay/driver board — never direct from Arduino pins.

## Pins
- S1: pin 11, OUTPUT
- S2: pin 12, OUTPUT
- SLU: pin 13, OUTPUT

## Mapping
| gear | S1 | S2 | SLU |
|---|---|---|---|
| 1 | ON | OFF | OFF |
| 2 | ON | ON | OFF |
| 3 | OFF | ON | OFF |
| 4 | OFF | OFF | OFF |
| 5 | OFF | OFF | ON |

`allOff()` used for P/R/N and startup.

## Interface
```cpp
SolenoidMapper(int pinS1, int pinS2, int pinSLU);
void begin();           // sets pinMode + calls allOff()
void applyGear(int gear); // 1–5
void allOff();
```
