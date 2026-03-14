# Schematics

PCB schematics and wiring diagrams for the paddle shifter controller.

---

## What belongs here

- PCB schematic files (KiCad, EasyEDA, Eagle, or PDF exports)
- Gerber files if a custom PCB is produced
- Full wiring diagram showing the Arduino Mega, relay/driver board, solenoids, NSS, paddles, and display
- Connector pinout references

---

## Electrical Overview

> Detailed schematics to be added. In the meantime, all pin assignments and wiring
> rules are documented in [`ArduinoCode/SYSTEM.md`](../ArduinoCode/SYSTEM.md).

Key constraints to observe in any schematic:

- Solenoids run on **12V, up to 2A each** — must go through a relay or high-side driver board, never directly from Arduino pins
- Flyback diodes (1N4007) required across each solenoid coil
- Display VCC is **3.3V only** — 5V will permanently damage the SSD1351 OLED
- Arduino Mega SPI pins 51 (MOSI) and 52 (SCK) are fixed — cannot be reassigned
