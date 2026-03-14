---
name: solenoid-mapper
description: Modify or debug the SolenoidMapper class — the AW4 solenoid output driver for the Jeep XJ paddle shifter controller. Use when changing the gear-to-solenoid truth table, adding gear states, or modifying solenoid output pin assignments. Source files are ArduinoCode/SolenoidMapper.h and ArduinoCode/SolenoidMapper.cpp.
---

# Skill: solenoid-mapper

Translates a logical gear number (1–5) into the correct S1 / S2 / SLU digital
output states for the AW4 / A340E automatic transmission.

## Critical Safety Facts

- **Solenoids are NOT driven directly from Arduino pins.** Each output drives a channel
  on an external relay or high-side driver board. Solenoids run on 12V and draw up to 2A each.
- **Flyback diodes (1N4007) are required** across each solenoid coil to protect the driver board.
- **SLU is digital on/off** on this AW4 variant — NOT PWM.
- **4th gear (all solenoids off) is the A340 electrical failsafe state.** If the Arduino
  loses power or resets, the transmission defaults to 4th gear hydraulically.

## Source Files

- `ArduinoCode/SolenoidMapper.h` — class declaration
- `ArduinoCode/SolenoidMapper.cpp` — `applyGear()` truth table, `write()` helper, `allOff()`

## Pin Assignments

| Arduino Pin | Solenoid | Direction |
|---|---|---|
| 11 | S1 | OUTPUT (to driver board) |
| 12 | S2 | OUTPUT (to driver board) |
| 13 | SLU | OUTPUT (to driver board) |

## Solenoid Truth Table (verified — AW4 / A340E)

| Gear | Description | S1 | S2 | SLU |
|---|---|---|---|---|
| 1 | 1st | ON | OFF | OFF |
| 2 | 2nd | ON | ON | OFF |
| 3 | 3rd | OFF | ON | OFF |
| 4 | 4th / Overdrive | OFF | OFF | OFF |
| 5 | 4th + Lockup | OFF | OFF | ON |
| — | P / R / N | OFF | OFF | OFF |

Sources: MaxxECU A340E wiring docs + EveryCircuit AW4 community build (see SOURCES.md).

## Public Interface

```cpp
SolenoidMapper(int pinS1, int pinS2, int pinSLU);
void begin();                // Sets pinMode OUTPUT + calls allOff() — call once in setup()
void applyGear(int gear);   // 1–5; out-of-range falls back to allOff()
void allOff();               // De-energises all three solenoids — used for P/R/N and errors
```

## Behaviour Notes

- `begin()` calls `allOff()` immediately — the transmission starts in electrical failsafe (4th) on power-up
- `applyGear()` with an out-of-range value (e.g. 0 or 6) silently calls `allOff()` as a safe fallback
- All solenoid state changes route through the private `write(bool s1, bool s2, bool slu)` helper
  — a single point of control for easier testing and modification

## Usage Pattern in ArduinoCode.ino

```cpp
solenoids.begin();          // In setup() — safe startup state

solenoids.applyGear(currentGear);   // On any gear change
solenoids.allOff();                 // On entering P, R, or N
```
