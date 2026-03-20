# Solenoid Truth Table — AW4 / A340E (Verified)

## Sources

Confirmed from two independent sources:
1. MaxxECU A340E/A341E wiring documentation — https://www.maxxecu.com/webhelp/wirings-auto_transmission-toyota_a340e_a341e.html
2. EveryCircuit AW4/A340 paddle shifter community build — https://everycircuit.com/circuit/4930966876323840/

## Verified Truth Table

| Gear | Description | S1 | S2 | SLU |
|---|---|---|---|---|
| 1 | 1st gear | ON | OFF | OFF |
| 2 | 2nd gear | ON | ON | OFF |
| 3 | 3rd gear | OFF | ON | OFF |
| 4 | 4th gear / Overdrive | OFF | OFF | OFF |
| 5 | 4th gear + Torque Converter Lockup | OFF | OFF | ON |
| — | Park | OFF | OFF | OFF |
| — | Reverse | OFF | OFF | OFF |
| — | Neutral | OFF | OFF | OFF |

## Critical Notes

- **4th gear (all off) is the electrical failsafe.** If the controller loses power,
  the transmission hydraulically defaults to 4th gear.
- **SLU is digital on/off on this AW4 variant.** It is NOT PWM. Do not attempt
  torque converter slip control.
- **Reverse, Park, and Neutral are hydraulic.** Solenoid state has no mechanical
  effect in these positions. The firmware calls `allOff()` as a safe default.
- **Solenoids run on 12V, up to 2A each.** They are NEVER driven directly from
  Arduino pins. Always use a relay or high-side driver board with flyback diodes.

## Pin Assignments (Firmware)

| Solenoid | Arduino Mega Pin | Direction |
|---|---|---|
| S1 | Pin 11 | OUTPUT (to driver board) |
| S2 | Pin 12 | OUTPUT (to driver board) |
| SLU | Pin 13 | OUTPUT (to driver board) |
