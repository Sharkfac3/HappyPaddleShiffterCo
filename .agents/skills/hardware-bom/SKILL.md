---
name: hardware-bom
description: Return or update the complete hardware bill of materials for the HappyPaddleShifterCo Jeep XJ AW4 paddle shifter. Use when the user asks for a parts list, BOM, what to buy, or what hardware is needed.
---

# Skill: hardware-bom

Complete hardware BOM for the HappyPaddleShifterCo AW4 paddle shifter controller.
All data is authoritative — sourced from Firmware/ArduinoCode/README.md and Firmware/ArduinoCode/SYSTEM.md.

## Electronics

| Item | Part / Notes |
|---|---|
| Microcontroller | Arduino Uno (default), Mega 2560, or Nano — same firmware, same pin numbers, no `#ifdef` |
| Display | WaveShare 1.5" RGB OLED — SSD1351 driver, 128×128 px — **3.3V only, 5V destroys it** |
| Solenoid driver | Relay or high-side driver board — 3 channels (S1, S2, SLU) — never drive solenoids directly from Arduino |
| Flyback diodes | 1N4007 × 3 — one across each solenoid coil |
| Paddle trigger sensors | IR slot-type optocoupler (LM393-based) × 2 — generic/unbranded module, **[UNVERIFIED — verify supplier stock before relying on it]** — see [Paddle Trigger Sensor Detail](#paddle-trigger-sensor-detail) below |

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

## Paddle Trigger Sensor Detail

### Selected Part: IR Slot-Type Optocoupler (LM393-based)

**Current selection (2026-08-17)** — replaces the Omron D2JW-01K11 mechanical switch (see
[Former Selection](#former-selection--omron-d2jw-01k11-mechanical-switch-replaced) below) to
eliminate mechanical wear. User-owned AliExpress module, item 3256804480682852 — **generic/
unbranded, no manufacturer part number.** `[UNVERIFIED — verify supplier stock before builders
rely on it]`. Treat as a known-working part on hand, not a stable sourced component like the
Omron switches it replaces.

#### Confirmed Electrical Specifications

| Parameter | Value |
|---|---|
| Sensor type | Slot-type IR optocoupler (photointerrupter) — NOT Hall effect, no magnet sensitivity |
| Comparator IC | LM393 |
| Operating voltage | 3.3V–5V — compatible with both Uno and Mega 5V logic, no level-shifting needed |
| Pins | VCC, GND, DO (digital output only — no AO on this module variant) |
| Output type | Actively driven push-pull (module drives the line) — do **not** enable Arduino `INPUT_PULLUP` |
| Output polarity | Slot unobstructed → DO LOW. Slot obstructed (tab in slot) → DO HIGH. |
| Confirmed mechanical orientation (2026-08-17, user) | Tab sits **in** the slot at rest → DO HIGH at rest; paddle pull clears the tab → DO LOW |
| IP rating | None — bare PCB, not automotive/vibration rated as shipped |

Firmware wired to match: `PaddleShiftIndication.cpp` uses plain `INPUT` (not `INPUT_PULLUP`)
and triggers on the same HIGH→LOW falling edge the old switch logic already expected — see
`Firmware/ArduinoCode/SYSTEM.md` pin table and the `paddle-shift-indication` skill.

#### Mounting Note — Mechanical Requirement Differs Fundamentally From the Switch It Replaces

This is **not** a lever-actuated switch geometry. The sensor needs an opaque tab to pass
through a slot gap on the paddle mechanism (approximate gap ~5mm, not independently sourced —
`[UNVERIFIED]`). **The paddle 3D model geometry needs redesign, not just a pocket depth
tweak** — see `Models/README.md` for the current state of that redesign.

Because the module ships as a bare, unrated PCB, carry these mitigations into the build:
- Solder wires direct to the module pads — skip Dupont/header connectors
- Strain-relief the leads at the PCB
- Rigid-mount the board to the paddle body (no free-hanging PCB)
- Conformal-coat or pot the board for vibration and moisture resistance

#### Suitability Assessment

| Category | Assessment |
|---|---|
| Mechanical durability | ✅ No moving parts to wear — eliminates the switch's mechanical life limit entirely |
| Electrical load | ✅ Signal-only, low current — appropriate for Arduino digital inputs |
| Voltage compatibility | ✅ 3.3V–5V — works unchanged on Uno, Mega, or Nano |
| Environmental sealing | ⚠️ Bare PCB, no IP rating as shipped — requires the mitigations above |
| Sourcing stability | ⚠️ Unbranded/generic AliExpress listing, no part number — verify stock before relying on it for a repeat build |
| Mechanical integration | ⚠️ Requires new paddle body geometry (slot, not lever pocket) — not yet designed |

> **Verdict:** Good electrical/durability upgrade over the mechanical switch, but it trades a
> well-sourced, IP67-rated part for an unrated generic module that needs new paddle geometry
> and physical protection measures before it's build-ready.

---

## Former Selection — Omron D2JW-01K11 (Mechanical Switch, Replaced)

Retained for reference in case the project reverts to a mechanical switch. Replaced 2026-08-17
by the IR slot optocoupler above to eliminate mechanical wear.

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
| Electrical life | 100,000 cycles |
| Operating temperature | −40°C to +85°C |
| IP rating | IP67 — dust tight, waterproof |
| Mounting | Chassis mount (mounts to paddle body directly) |
| Termination | Solder lug — wire leads run to PCB/Arduino |

#### Alternatives Evaluated (Historical)

| Part | IP Rating | Current Rating | Temp Range | Mechanical Life | Electrical Life | Notes |
|---|---|---|---|---|---|---|
| **Omron D2JW-01K11** *(former selection)* | IP67 | 100 mA @ 30 VDC | −40°C to +85°C | 1,000,000 ops | 100,000 cycles | Straight lever, 82 gf, 8.4 mm op position, chassis mount, solder lug |
| **Omron D2F-5L** *(replaced earlier)* | IP40 | 5 A @ 250 VAC | −40°C to +85°C | 1,000,000 ops | 10,000 cycles | Through-hole PCB, hinge lever, 80 gf; replaced due to low electrical life and no water protection |
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
