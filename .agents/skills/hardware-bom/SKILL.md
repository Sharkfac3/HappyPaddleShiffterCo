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
| Paddle switches | Omron D2F-5L microswitch × 2 — normally-open momentary |

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

## Physical / Paddle Hardware

STL files and non-printed hardware BOM (fasteners, magnets, etc.) are tracked in
`Models/README.md`. That section is currently a placeholder — add items there as
parts are finalised, then update this skill to match.

---

> **Updating this BOM:** If parts change, update this file AND the relevant source README
> so both stay in sync.
