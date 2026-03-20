# Documentation Deliverables

Status tracker and specification for every documentation deliverable this role owns.

---

## ArduinoCode/README.md

**Status:** Complete (initial version)
**Purpose:** Getting-started guide for builders flashing the firmware.
**Must include:**
- Required hardware list (Arduino Mega 2560, relay/driver board, SSD1351 display, switches)
- Arduino IDE library dependencies (Adafruit_SSD1351, Adafruit_GFX)
- Flash instructions (open .ino, select board, select port, upload)
- Serial monitor expected output at startup
- Quick sanity-check procedure (what to verify before connecting to vehicle)

---

## Schematics/README.md

**Status:** Stub — needs full wiring diagram
**Purpose:** Complete wiring reference for the build.
**Must include:**
- Full system wiring diagram (ASCII or table) covering:
  - Arduino Mega → NSS connector (all 4 signal pins)
  - Arduino Mega → paddle switches (2 pins)
  - Arduino Mega → relay/driver board → solenoids (3 channels)
  - Arduino Mega → SSD1351 display (5 wires)
  - Power and ground distribution
- Connector pinout for the AW4 NSS (8-pin Deutsch, '87-'96 and '97-'01 variants)
- Relay/driver board wiring notes (flyback diodes, 12V supply)

> NOTE: The '97-'01 NSS connector pinout needs research confirmation.
> Drop in HANDOFFS.md for research role before publishing that section.

---

## Models/README.md

**Status:** Stub — print settings and BOM pending
**Purpose:** Guide for printing the steering wheel paddle hardware.
**Must include:**
- Print settings: material, layer height, infill %, supports, orientation
- Hardware BOM: switches (part number), fasteners, any inserts or magnets
- Assembly notes: how paddles mount to steering wheel, switch orientation

> NOTE: Switch part numbers and print settings need confirmation.
> Drop in HANDOFFS.md for research role before publishing.

---

## README.md (project root)

**Status:** Complete — maintain as project evolves
**Purpose:** Project overview and getting-started index.
**Must not:** contain wiring details (those go in Schematics/).

---

## Wiring Diagram Conventions

All wiring diagrams follow this column order when using tables:

| From | Pin / Terminal | To | Pin / Terminal | Notes |
|---|---|---|---|---|

Signal names use the format: `COMPONENT — SIGNAL (direction from Arduino)`.

Example:
| From | Pin / Terminal | To | Pin / Terminal | Notes |
|---|---|---|---|---|
| Arduino Mega | Pin 4 INPUT_PULLUP | AW4 NSS | Pin B | Park/Neutral — active LOW |
| Arduino Mega | Pin 11 OUTPUT | Driver Board | CH1 IN | S1 solenoid control |
