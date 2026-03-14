# HappyPaddleShifterCo

A complete paddle shifter conversion for the Jeep XJ Cherokee with the AW4 automatic
transmission (1987–2001). Steering wheel paddles replace the factory TCU — the driver
controls gear selection directly via solenoid outputs read from the AW4 neutral safety switch.

This repository contains everything needed to build and install the system: firmware,
3D-printable paddle hardware, and PCB schematics.

---

## Folders

| Folder | What it contains |
|---|---|
| [`ArduinoCode/`](ArduinoCode/README.md) | Arduino Mega 2560 firmware — the transmission controller |
| [`Models/`](Models/README.md) | 3D-printable STL files for the steering wheel paddle hardware |
| [`Schematics/`](Schematics/README.md) | PCB schematics and wiring diagrams |

---

## Getting Started

1. **Read [`ArduinoCode/README.md`](ArduinoCode/README.md)** — hardware requirements, wiring, and flash instructions
2. **Read [`Models/README.md`](Models/README.md)** — print settings and hardware BOM for the paddles
3. **Read [`Schematics/README.md`](Schematics/README.md)** — PCB layout and connector pinouts

Research sources for all hardware and electrical decisions are in [`SOURCES.md`](SOURCES.md).
