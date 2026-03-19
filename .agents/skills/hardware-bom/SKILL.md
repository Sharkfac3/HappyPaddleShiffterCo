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
| Paddle switches | Omron D2F-5L microswitch × 2 — normally-open momentary — see [Paddle Switch Detail](#paddle-switch-detail) below |

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

### Selected Part: Omron D2F-5L

**Current selection** — normally-open, momentary, hinge lever, SPDT, PCB through-hole solder terminals.

#### Full Specifications

| Parameter | Value |
|---|---|
| Contact configuration | SPDT (NO + NC) |
| Actuator type | Hinge lever |
| Voltage rating | 250 VAC / 30 VDC |
| Current rating | 5 A |
| Operating force | 1.47 N |
| Operating speed | 5–500 mm/s (lever models) |
| Operating frequency (mechanical) | 100 ops/min |
| Operating frequency (electrical) | 30 ops/min |
| Mechanical life | 1,000,000 operations |
| Electrical life | ~30,000 operations |
| Contact resistance (initial) | 30 mΩ max |
| Insulation resistance | 100 MΩ min @ 500 VDC |
| Dielectric strength | 600 VAC (same polarity) / 1,500 VAC (to ground) |
| Operating temperature | −25°C to +85°C |
| IP rating | **IP40** (dust proof — no water protection) |
| Vibration resistance (malfunction) | 10–55 Hz, 1.5 mm double amplitude |
| Shock resistance (destruction) | 1,000 m/s² |
| Shock resistance (malfunction) | 300 m/s² |
| Termination | PCB through-hole solder pins |
| RoHS | Yes |

#### Motorsport Suitability

| Category | Assessment |
|---|---|
| Mechanical durability | ✅ 1M operations — excellent for paddle shifting |
| Tactile feedback | ✅ Snap-action gives crisp, positive actuation |
| Electrical load | ✅ 5A rating far exceeds Arduino signal input requirements |
| Temperature range | ✅ −25°C to +85°C covers all cabin environments |
| Shock resistance | ✅ 1,000 m/s² destruction threshold is robust |
| Moisture/water | ⚠️ IP40 — no water protection; risk in a Jeep XJ interior |
| Continuous vibration | ⚠️ Omron explicitly warns against it — can cause contact failure from internal abrasive powder |
| Terminal integrity | ⚠️ PCB solder pins can fatigue under vibration if switch body is not mechanically supported |
| Electrical life | ⚠️ ~30,000 ops is lower than mechanical life — adequate for normal use (~4 yrs at 20 shifts/day) |

> **Verdict:** Suitable for a street/mild off-road build with good mounting practice. For sustained motorsport or heavy off-road use, evaluate a sealed alternative (see below).

---

## Paddle Switch Alternatives

Evaluated alternatives if the D2F-5L is replaced for higher environmental demands. All are normally-open momentary snap-action types.

| Part | IP Rating | Current Rating | Temp Range | Mechanical Life | Key Advantage | Trade-off |
|---|---|---|---|---|---|---|
| **Omron D2F-5L** *(current)* | IP40 | 5 A @ 250 VAC | −25°C to +85°C | 1,000,000 ops | Proven, widely available, crisp snap feel | Not sealed; vibration caveat |
| **Omron D2JW** (e.g. D2JW-011) | **IP67** | 100 mA @ 30 VDC | −40°C to +85°C | 1,000,000 ops | Fully sealed, gold-alloy crossbar contact, automotive-grade; used OEM in AT shift units | Lower current rating (signal use only — fine for this project); slightly higher OF (2.45 N) |
| **Omron D2JW-AQ** | **IP67** | 10 mA @ 14 VDC | −40°C to +85°C | 1,000,000 ops | Explicitly automotive-rated; OEM P-range detection use | Very low current rating — signal only |
| **Omron D2VW** | **IP67** | 21 A @ 250 VAC | −25°C to +85°C | 1,000,000 ops | Sealed miniature, higher current if ever needed | Larger physical footprint |
| **Honeywell V7 Series** | Not sealed | 5 A @ 250 VAC | −40°C to +85°C | 1,000,000 ops | Industry-standard snap-action, pin plunger or lever | Requires sealed paddle housing to compensate |
| **APEM IS/IC Series** | **IP67** | ~3 A | — | — | Panel-mount momentary pushbutton, designed for vehicle dashboards | Different form factor — pushbutton not microswitch; mounting approach differs |

> **Recommended upgrade path:** If moisture or sustained vibration becomes a concern, swap to the **Omron D2JW** — it is pin-compatible in function (SPDT, NO, snap-action), purpose-built for automotive use, and retains the same 1M mechanical life. The lower current rating is irrelevant since the Arduino input draws microamps.

---

## Physical / Paddle Hardware

STL files and non-printed hardware BOM (fasteners, magnets, etc.) are tracked in
`Models/README.md`. That section is currently a placeholder — add items there as
parts are finalised, then update this skill to match.

---

> **Updating this BOM:** If parts change, update this file AND the relevant source README
> so both stay in sync.
