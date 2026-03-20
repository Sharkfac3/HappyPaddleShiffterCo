---
name: hardware-bom
description: Return or update the complete hardware bill of materials for the HappyPaddleShifterCo Jeep XJ AW4 paddle shifter. Use when the user asks for a parts list, BOM, what to buy, or what hardware is needed.
---

# Skill: hardware-bom

Complete hardware BOM for the HappyPaddleShifterCo AW4 paddle shifter controller.
All data is authoritative — sourced from ArduinoCode/README.md and ArduinoCode/SYSTEM.md.

## Electronics

| Item | Part / Notes |
|---|---|
| Microcontroller | Arduino Mega 2560 (Uno lacks pins/flash) |
| Display | WaveShare 1.5" RGB OLED — SSD1351 driver, 128×128 px — **3.3V only, 5V destroys it** |
| Solenoid driver | Relay or high-side driver board — 3 channels (S1, S2, SLU) — never drive solenoids directly from Arduino |
| Flyback diodes | 1N4007 × 3 — one across each solenoid coil |
| Paddle switches | Omron D2JW-01K11 microswitch × 2 — normally-open momentary, IP67, chassis mount — see [Paddle Switch Detail](#paddle-switch-detail) below |

## Vehicle Connector (choose by year)

| Years | Part Number | Notes |
|---|---|---|
| 1987–1996 | Omix-ADA 17216.03 / OEM 83503712 | 8-pin Deutsch connector, pins A–H |
| 1997–2001 | Omix-ADA 4882173 / OEM 4882173 | Different physical connector |

## Arduino Libraries (no purchase needed)

| Library | Source |
|---|---|
| `Adafruit_SSD1351` | Arduino Library Manager |
| `Adafruit_GFX` | Arduino Library Manager |
| `SPI` | Built-in — no install needed |

---

## Paddle Switch Detail

### Selected Part: Omron D2JW-01K11

**Current selection** — normally-open, momentary, straight lever, SPDT, IP67, chassis mount with solder lug wire leads. Replaces D2F-5L (see Alternatives for D2F-5L specs if needed).

#### Full Specifications

| Parameter | Value |
|---|---|
| Contact configuration | SPDT (NO + NC) |
| Actuator type | Lever, Straight |
| Voltage rating | 30 VDC |
| Current rating | 100 mA (DC) |
| Operating force | 82 gf |
| Release force | 16 gf |
| Operating position | 8.4 mm (0.330") |
| Pretravel | 6.4 mm (0.252") |
| Differential travel | 0.7 mm (0.027") |
| Overtravel | 1.4 mm (0.055") |
| Mechanical life | 1,000,000 cycles |
| Electrical life | **100,000 cycles** |
| Operating temperature | −40°C to +85°C |
| IP rating | **IP67** — dust tight, waterproof |
| Mounting | Chassis mount (mounts to paddle body directly) |
| Termination | Solder lug — wire leads run to PCB/Arduino |

#### Mounting Note

The D2JW-01K11 is not a PCB through-hole part. It chassis-mounts to the paddle body with wire leads soldered to the lugs. The paddle 3D model switch pocket must position the lever 8.4 mm from the paddle contact surface (1.6 mm deeper than the former D2F-5L pocket at 6.8 mm).

#### Motorsport Suitability

| Category | Assessment |
|---|---|
| Mechanical durability | ✅ 1M cycles — excellent for paddle shifting |
| Tactile feedback | ✅ Snap-action straight lever — 82 gf nearly identical to D2F-5L (80 gf) |
| Electrical load | ✅ 100 mA signal rating is appropriate for Arduino digital inputs |
| Temperature range | ✅ −40°C to +85°C covers all cabin environments |
| Moisture/water | ✅ IP67 — fully dust tight and waterproof |
| Electrical life | ✅ 100,000 cycles — ~13.7 yrs at 20 shifts/day |
| Mounting | ✅ Chassis mount to paddle body is robust under vibration |

> **Verdict:** Strong choice for street, off-road, and sustained use. 10× better electrical life and full IP67 sealing vs the former D2F-5L selection. Paddle feel is near-identical.

---

## Paddle Switch Alternatives

Evaluated alternatives to the selected D2JW-01K11, and the replaced D2F-5L for reference. All are normally-open momentary snap-action types.

| Part | IP Rating | Current Rating | Temp Range | Mechanical Life | Electrical Life | Notes |
|---|---|---|---|---|---|---|
| **Omron D2JW-01K11** *(selected)* | IP67 | 100 mA @ 30 VDC | −40°C to +85°C | 1,000,000 ops | 100,000 cycles | Straight lever, 82 gf, 8.4 mm op position, chassis mount, solder lug |
| **Omron D2F-5L** *(replaced)* | IP40 | 5 A @ 250 VAC | −40°C to +85°C | 1,000,000 ops | 10,000 cycles | Former selection — through-hole PCB, hinge lever, 80 gf; replaced due to low electrical life and no water protection |
| **Omron D2JW-011** | IP67 | 100 mA @ 30 VDC | −40°C to +85°C | 1,000,000 ops | 100,000 cycles | Pin plunger actuator, 250 gf — rejected; incompatible geometry and stiff feel |
| **Omron D2JW-01K21** | IP67 | 100 mA @ 30 VDC | −40°C to +85°C | 1,000,000 ops | 100,000 cycles | Roller lever, 100 gf, 14.6 mm op position — superseded by D2JW-01K11 |
| **Omron D2JW-AQ** | IP67 | 10 mA @ 14 VDC | −40°C to +85°C | 1,000,000 ops | not confirmed | Explicitly automotive-rated; signal-only current — unconfirmed specs |
| **Omron D2VW** | IP67 | 21 A @ 250 VAC | −25°C to +85°C | 1,000,000 ops | not confirmed | Sealed, higher current — larger footprint |
| **Honeywell V7 Series** | Not sealed | 5 A @ 250 VAC | −40°C to +85°C | 1,000,000 ops | not confirmed | Requires sealed housing; not evaluated further |
| **APEM IS/IC Series** | IP67 | ~3 A | — | — | not confirmed | Pushbutton not microswitch — different form factor |

---

## Physical / Paddle Hardware

STL files and non-printed hardware BOM (fasteners, magnets, etc.) are tracked in
`Models/README.md`. That section is currently a placeholder — add items there as
parts are finalised, then update this skill to match.

---

> **Updating this BOM:** If parts change, update this file AND the relevant source README
> so both stay in sync.
