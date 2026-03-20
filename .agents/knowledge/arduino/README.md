# Arduino Platform — Knowledge Index

Hardware facts about the Arduino Mega 2560 and supporting electronics used in the paddle shifter controller.

---

## Files in This Section

| Folder / File | Contents |
|---|---|
| [`mega-2560/`](mega-2560/README.md) | Arduino Mega 2560 hardware — pins, SPI, voltage, constraints |
| [`driver-boards/`](driver-boards/README.md) | External relay and high-side driver boards for solenoid switching |

---

## Key Facts for This Project

| Item | Value |
|---|---|
| Microcontroller | ATmega2560 |
| Logic voltage | **5V** |
| Max current per I/O pin | 40mA (absolute max) — never drive solenoids directly |
| Hardware SPI (MOSI) | Pin **51** — fixed, cannot be remapped |
| Hardware SPI (SCK) | Pin **52** — fixed, cannot be remapped |
| Digital I/O count | 54 (pins 0–53) |
| Analog input count | 16 (A0–A15) |
| USB programming | Via ATmega16U2 USB-to-serial bridge — standard USB-B connector |

---

## Voltage Compatibility Warning

The Arduino Mega operates at **5V logic**. The SSD1351 OLED display (used in this project) operates at **3.3V only**.

> ⚠️ SAFETY: Connecting the SSD1351 VCC to 5V will permanently damage the display. The display is connected to the Mega's 3.3V output pin, NOT the 5V pin.

The display communicates over SPI. The Mega's SPI signals are 5V logic; the SSD1351 library handles this acceptably because the SSD1351 is tolerant of 5V logic inputs on its SPI lines (data direction is Mega → display only). However, VCC must be 3.3V.
