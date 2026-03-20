# AW4 / A340E Transmission Overview

## What is the AW4?

The AW4 is a 4-speed electronically-controlled automatic transmission used in Jeep XJ Cherokees from 1987 to 2001. It is mechanically identical to the Toyota A340E used in numerous Toyota Land Cruisers, 4Runners, and Hilux Surf vehicles, and the A341E used in some Lexus applications.

"AW4" is the Jeep-specific designation. The underlying transmission family is the Toyota A340 series.

---

## Toyota A340 Lineage

| Designation | Application | Notes |
|---|---|---|
| A340E | Toyota Land Cruiser 80, 4Runner, Hilux Surf | Same mechanical core as AW4 |
| A341E | Lexus LX450, some Land Cruisers | Overdrive-only variant |
| AW4 | Jeep XJ Cherokee 1987–2001 | Jeep-specific designation for A340E |

The Toyota origin means the AW4 is well-documented in Toyota service manuals, MaxxECU documentation, and the Toyota enthusiast community — all of which apply to the Jeep installation.

---

## Gear Ratios

| Gear | Ratio | Notes |
|---|---|---|
| 1st | 2.804:1 | — |
| 2nd | 1.531:1 | — |
| 3rd | 1.000:1 | Direct drive |
| 4th | 0.753:1 | Overdrive |
| Reverse | 2.393:1 | — |

---

## Selector Positions

The AW4 has a 6-position selector gate: **P – R – N – D – 3 – 2-1**

See [`selector-gate.md`](selector-gate.md) for the mechanical behaviour of each position and how the controller handles them.

---

## Factory TCU (What This Project Replaces)

The factory AW4 TCU is a standalone ECU that:
- Reads throttle position sensor (TPS) output
- Reads vehicle speed sensor (VSS) output
- Reads selector position from the NSS
- Commands shift solenoids (S1, S2) to control shift scheduling
- Commands the SLU solenoid for torque converter lockup
- Controls line pressure via a separate pressure control solenoid (not used in this project)

**This project bypasses the factory TCU completely.** The Arduino Mega reads the NSS directly and accepts driver input via paddle switches. Shift scheduling is entirely manual — the driver determines when to change gear.

The factory TCU connector can be left disconnected. The factory TCU wiring harness to the solenoids and NSS is replaced with the custom harness described in the project wiring documentation.

---

## What the Factory TCU Did Not Affect

The following AW4 functions are entirely hydraulic and continue to operate normally with no TCU:
- Torque converter function (coupling, slip)
- Line pressure regulation via governor pressure (speed-proportional)
- Hydraulic gear selection enforcement (the physical selector gate prevents invalid combinations)
- Reverse and neutral hydraulics

---

## Variants and Differences by Year

| Years | Difference | Notes |
|---|---|---|
| 1987–1996 | NSS 8-pin Deutsch connector (pins A–H) | Part numbers: Omix-ADA 17216.03 / OEM 83503712 |
| 1997–2001 | NSS uses different physical connector housing | Same electrical behaviour and pin continuity map; different part numbers |
| All years | Solenoid truth table is consistent | S1/S2/SLU mapping verified consistent across XJ production run |

---

## Source Quality Note

The AW4/A340E is well-documented in both Jeep FSMs and Toyota service manuals. The solenoid mapping has been confirmed from multiple independent sources (MaxxECU, EveryCircuit, ATSG). The NSS continuity map has been confirmed from the Jeep XJ 1993 FSM and is consistent across all XJ model years.

See `SOURCES.md` in the project root for all source URLs and fetch statuses.
