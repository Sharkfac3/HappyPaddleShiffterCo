# Arduino Platform — Knowledge Index

Hardware facts about the Arduino board (Uno default, Mega 2560 or Nano supported) and
supporting electronics used in the paddle shifter controller.

---

## Files in This Section

| Folder / File | Contents |
|---|---|
| [`board-comparison.md`](board-comparison.md) | Uno vs Nano vs Mega 2560 comparison — pick a board |
| [`pin-reference/`](pin-reference/README.md) | This project's pin assignments — pins, SPI, voltage, constraints (all three boards) |
| [`driver-boards/`](driver-boards/README.md) | External relay and high-side driver boards for solenoid switching |

---

## Key Facts for This Project

| Item | Uno / Nano (default) | Mega 2560 |
|---|---|---|
| Microcontroller | ATmega328P | ATmega2560 |
| Logic voltage | **5V** | **5V** |
| Max current per I/O pin | 40mA (absolute max) — never drive solenoids directly | 40mA (absolute max) — never drive solenoids directly |
| Hardware SPI (MOSI) | Pin **11** — fixed, cannot be remapped | Pin **51** — fixed, cannot be remapped |
| Hardware SPI (SCK) | Pin **13** — fixed, cannot be remapped | Pin **52** — fixed, cannot be remapped |
| Digital I/O count | 20 usable (14 digital + 6 analog-as-digital) | 54 (pins 0–53) |
| Analog input count | 6 (A0–A5); Nano adds A6/A7 (input-only, unused here) | 16 (A0–A15) |
| USB programming | Uno: USB-B. Nano: USB Mini/Micro (varies by clone) | ATmega16U2 USB-to-serial bridge, USB-B |

See `board-comparison.md` for the full comparison and how to choose.

---

## Voltage Compatibility Warning

All three boards operate at **5V logic**. The SSD1351 OLED display (used in this project) operates at **3.3V only**.

> ⚠️ SAFETY: Connecting the SSD1351 VCC to 5V will permanently damage the display. The display is connected to the board's 3.3V output pin, NOT the 5V pin.

The display communicates over SPI. All three boards' SPI signals are 5V logic; the SSD1351 library handles this acceptably because the SSD1351 is tolerant of 5V logic inputs on its SPI lines (data direction is Arduino → display only). However, VCC must be 3.3V.
