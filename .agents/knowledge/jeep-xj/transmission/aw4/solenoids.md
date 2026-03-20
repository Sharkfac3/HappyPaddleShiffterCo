# AW4 Solenoids — Specifications and Truth Table

## Solenoids Overview

The AW4 has three electronically-controlled solenoids relevant to this project:

| Solenoid | Full Name | Function |
|---|---|---|
| S1 | Shift Solenoid 1 | Controls 1st/2nd gear hydraulic circuit |
| S2 | Shift Solenoid 2 | Controls 3rd/4th gear hydraulic circuit |
| SLU | Solenoid Lock-Up | Engages torque converter lockup clutch |

There is also a separate **Solenoid Line Pressure Control (SLP)** valve in some variants, but it is not used in this project. The AW4 operates at acceptable line pressures without electronic line pressure control, relying on the governor (speed-based hydraulic pressure) as it did in earlier automatic transmissions.

---

## Solenoid Electrical Specifications

| Parameter | Value | Source |
|---|---|---|
| Operating voltage | 12V DC | Factory spec |
| Coil resistance | ~10–13 Ω per solenoid | [UNVERIFIED — measure with multimeter] |
| Current draw (active) | ~1–1.5A per solenoid at 12V | Derived from resistance; confirm |
| Peak current (activation) | Up to 2A | Conservative estimate for driver board sizing |
| SLU control type | Digital ON/OFF | This AW4 variant uses on/off SLU; NOT PWM |

> ❓ UNVERIFIED: Coil resistance has not been confirmed by direct measurement for this specific unit. Measure with a multimeter across solenoid terminals before sizing protection components.

> ⚠️ SAFETY: Solenoids draw up to 2A at 12V. Never connect them directly to Arduino output pins (max 40mA per pin). Always use an external relay board or high-side driver IC.

---

## Solenoid Truth Table

Verified from: MaxxECU A340E/A341E wiring documentation + EveryCircuit AW4 community build. Cross-referenced with ATSG AW4 service manual.

| Gear | Description | S1 | S2 | SLU |
|---|---|---|---|---|
| 1 | 1st gear | ON | OFF | OFF |
| 2 | 2nd gear | ON | ON | OFF |
| 3 | 3rd gear | OFF | ON | OFF |
| 4 | 4th gear (overdrive) | OFF | OFF | OFF |
| 5 | 4th gear + torque converter lockup | OFF | OFF | ON |
| — | Park / Reverse / Neutral | OFF | OFF | OFF |

### Failsafe State

**4th gear (all solenoids OFF) is the electrical failsafe.** If the controller loses power or resets, the AW4 defaults to 4th gear hydraulically. This is intentional Toyota/Jeep design — 4th gear allows the vehicle to be driven home even with a complete electrical failure of the TCU.

Reverse and Neutral are purely hydraulic — solenoid state has no effect in these positions.

---

## SLU (Lockup) Behaviour

The SLU solenoid engages the torque converter lockup clutch, which mechanically couples the engine to the transmission input shaft (eliminating torque converter slip losses).

On this AW4 variant:
- SLU is **digital on/off** — apply 12V to engage, 0V to disengage
- SLU is only meaningful in 4th gear (gear 5 in this project's numbering)
- Engaging SLU in lower gears is hydraulically blocked or undesirable — do not command SLU ON unless in 4th gear

---

## Solenoid Connector Location

The AW4 solenoid harness exits from the **passenger side** of the transmission, under a heat shield. It uses a multi-pin connector that includes S1, S2, SLU, and SLP (line pressure, not used).

> ❓ UNVERIFIED: Exact connector type (Molex, Deutsch, etc.) and pin count for the solenoid harness external connector. Research role should verify this from the FSM or ATSG manual and update this file.

---

## Sources

| Source | URL | Status |
|---|---|---|
| MaxxECU A340E wiring docs | https://www.maxxecu.com/webhelp/wirings-auto_transmission-toyota_a340e_a341e.html | ✅ Read |
| EveryCircuit AW4 community build | https://everycircuit.com/circuit/4930966876323840/working-aw4-a340-automatic-transmission-paddle-shifter-control- | ✅ Read |
| ATSG AW4 Service Information PDF | https://cdn.xjjeeps.com/pdf/en-us/aw4-transmission-service-information.pdf | ✅ Read |
