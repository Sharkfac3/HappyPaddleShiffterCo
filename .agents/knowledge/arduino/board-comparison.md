# Arduino Uno vs Mega 2560 vs Nano — Board Reference

Firmware runs unchanged on any of the three boards — same source files, same pin `#define`s,
same wiring, no `#ifdef` branching. Uno is the default board (ADR-009); Mega and Nano remain
fully supported. See `.agents/DECISIONS.md` ADR-008/ADR-009/ADR-010 for the full history.

## Why All Three Boards Work Unchanged

The only real conflict was solenoid outputs sitting on the Uno's (and Nano's — same ATmega328P,
same pin numbering) fixed hardware-SPI pins (11/13). Fix: `PIN_S1/PIN_S2/PIN_SLU` moved to
A0/A1/A2 (used as digital outputs — same technique already used for CS/DC/RST on A3/A4/A5). The
Mega's hardware SPI (51/52) was never on 11/12/13, so it was never affected. The display's
DIN/CLK hardware-SPI pins are auto-selected by the `Adafruit_SSD1351` library per board — never
a project `#define`.

The Nano is electrically the same microcontroller as the Uno (ATmega328P) with the same digital/
analog pin numbering (D0–D13, A0–A5 shared; Nano adds A6/A7 as analog-input-only, unused by this
project). Everything documented for the Uno below — pin table, hardware SPI, flash/SRAM — applies
to the Nano as well unless noted otherwise.

## Pin Assignments (This Project — Identical on All Three Boards)

| Pin | Direction | Mode | Connected to |
|---|---|---|---|
| 2 | INPUT | plain INPUT | Shift Up paddle sensor DO |
| 3 | INPUT | plain INPUT | Shift Down paddle sensor DO |
| 4 | INPUT | INPUT_PULLUP active LOW | NSS Park/Neutral (B↔C) |
| 5 | INPUT | INPUT_PULLUP active LOW | NSS Reverse (A↔E) |
| 6 | INPUT | INPUT_PULLUP active LOW | NSS 3rd hold (A↔G) |
| 7 | INPUT | INPUT_PULLUP active LOW | NSS 1-2 hold (A↔H) |
| A0 | OUTPUT | — | S1 solenoid via driver board |
| A1 | OUTPUT | — | S2 solenoid via driver board |
| A2 | OUTPUT | — | SLU solenoid via driver board |
| A3 | OUTPUT | — | Display RES |
| A4 | OUTPUT | — | Display DC |
| A5 | OUTPUT | — | Display CS |

## Hardware SPI (Display Only) — Board-Specific, Fixed

| Signal | Uno Pin | Nano Pin | Mega Pin |
|---|---|---|---|
| MOSI → Display DIN | 11 | 11 | 51 |
| SCK → Display CLK | 13 | 13 | 52 |

These are the only pins that differ by board family (Uno/Nano share the same pins), and the
`Adafruit_SSD1351` library resolves them automatically — nothing to configure in the sketch.

## Board Comparison

| Attribute | Uno | Nano | Mega 2560 |
|---|---|---|---|
| Digital I/O pins | 20 usable (14 digital + 6 analog-as-digital) | 20 usable (14 digital + 6 analog-as-digital, same as Uno; A6/A7 are analog-input-only, unused here) | 54 |
| Flash | 32 KB | 32 KB (30720 B usable — see note) | 256 KB |
| SRAM | 2 KB | 2 KB | 8 KB |
| This project's flash usage | 14070 B (43%) | 14070 B (45%) — identical byte count to the Uno; higher percentage only because the Nano's usable flash is smaller | 14878 B (5%) |
| This project's SRAM usage | 864 B (42%) | 864 B (42%) — identical to the Uno | 864 B (10%) |
| Form factor | Full-size, USB-B | Smallest of the three — breadboard-friendly, USB Mini/Micro (varies by clone) | Largest |
| Barrel jack / VIN | Yes | No barrel jack (VIN pin only) — matters for power wiring, see ADR-010 | Yes |
| Cost | Lower | Lowest (clones are very cheap) | Higher |
| Headroom for future features | Comfortable, but tighter | Comfortable, but tighter (same silicon as Uno) | Ample |

All three boards measured via `arduino-cli compile` (1.5.2-rc.1, 2026-08-19) against
`arduino:avr:uno`, `arduino:avr:mega`, and `arduino:avr:nano`. The Nano was compiled against
both processor/bootloader options — `cpu=atmega328` (default, new bootloader) and
`cpu=atmega328old` (old bootloader) — with identical results on both: program size is byte-for-
byte the same as the Uno build, but this arduino-cli board definition reports the Nano's usable
flash as 30720 B rather than the Uno's 32256 B (the bootloader reserves more space), so the same
14070 B occupies a larger percentage (45% vs 43%). See `ArduinoCode/README.md` for which
processor option to pick when flashing a physical Nano — picking the wrong one uploads
successfully but the board won't run. None of the three boards has been bench-tested on
physical hardware yet.

## Choosing a Board

- **Uno (default):** Cheaper, smaller, this project's headroom is still comfortable
  (43% flash / 42% SRAM). Recommended unless a future feature needs more room.
- **Nano:** Smallest and cheapest option, same headroom as the Uno. No barrel jack — power
  must come in via VIN or 5V pin (see `.agents/knowledge/jeep-xj/electrical/power-distribution.md`
  and ADR-010 for the buck-converter requirement, which applies to all three boards). Good fit
  if enclosure space is tight.
- **Mega 2560:** More headroom for future expansion (CAN bus, telemetry, data logging
  via the extra hardware UARTs) — see `pin-reference/pinout.md` for free pins. Choose this
  if you already have one or plan to add features beyond the current scope.

## Files in This Section

| File | Contents |
|---|---|
| [`pin-reference/`](pin-reference/README.md) | This project's full pin assignment reference — pinout, hardware SPI detail, free pins (Mega-specific free-pin list; pin table applies to all boards) |
| [`driver-boards/`](driver-boards/README.md) | External relay and high-side driver boards for solenoid switching |
