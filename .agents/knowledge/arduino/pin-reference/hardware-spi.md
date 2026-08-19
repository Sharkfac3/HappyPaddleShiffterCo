# Arduino Hardware SPI — Uno / Nano / Mega 2560

## What is Hardware SPI?

The ATmega328P (Uno, Nano) and ATmega2560 (Mega) each have a hardware SPI peripheral that
handles serial data clocking in silicon, separate from general-purpose I/O. Hardware SPI is
significantly faster and more reliable than software ("bit-bang") SPI for display communication.

---

## Hardware SPI Pins — Mega 2560 vs Uno vs Nano (This Project Supports All Three)

| SPI Signal | Mega Pin | Uno Pin | Nano Pin | Notes |
|---|---|---|---|---|
| MOSI (Master Out Slave In) | **51** | **11** | **11** | Data from Arduino to display |
| MISO (Master In Slave Out) | **50** | **12** | **12** | Data from peripheral to Arduino (not used by SSD1351) |
| SCK (Serial Clock) | **52** | **13** | **13** | Clock signal |
| SS (Slave Select) | **53** | **10** | **10** | Hardware SS — not used directly; CS managed via software (A5) |

Uno and Nano share the same ATmega328P and the same hardware SPI pin numbers — the Nano column
is identical to the Uno column throughout this file.

> ⚠️ CRITICAL: **The Mega uses different hardware SPI pins than the Uno/Nano.** Mega: 51/52.
> Uno/Nano: 11/13. This project's solenoid outputs sit on A0/A1/A2 specifically to avoid the
> Uno/Nano's 11/13 conflict (see `.agents/DECISIONS.md` ADR-008/ADR-009). You never wire this
> by hand or set it in a `#define` — the `Adafruit_SSD1351` library resolves MOSI/SCK
> automatically based on which board the sketch is compiled for. If you wire the display to the
> wrong pins for your board, SPI will not function.

---

## SSD1351 Display SPI Wiring (This Project)

| SSD1351 Pin | Connected to | Notes |
|---|---|---|
| DIN | MOSI — pin 51 (Mega) / pin 11 (Uno, Nano) | Hardware SPI — fixed, auto-selected by board |
| CLK | SCK — pin 52 (Mega) / pin 13 (Uno, Nano) | Hardware SPI — fixed, auto-selected by board |
| CS | A5 | Software chip select — can be reassigned |
| DC | A4 | Data/command select — can be reassigned |
| RES | A3 | Reset — can be reassigned |
| VCC | 3.3V pin | **3.3V ONLY — never 5V** |
| GND | GND | — |

Only DIN and CLK are fixed (and board-specific). CS, DC, and RES can be moved to any available
digital output pin by updating the `#define` values in `ArduinoCode.ino` and the
`ScreenIndication` constructor call.

---

## SPI and the Adafruit SSD1351 Library

The Adafruit SSD1351 library initialises hardware SPI automatically when constructed with pin numbers:

```cpp
// Adafruit_SSD1351 constructor — uses hardware SPI
Adafruit_SSD1351 _tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, cs, dc, rst);
```

Calling `_tft.begin()` (NOT `_tft.initR()`) initialises the SSD1351 chip. `initR()` is for the ST7735 — a different and incompatible display driver.

---

## SPI Bus Sharing

The hardware SPI bus on any of the three boards can be shared between multiple devices (only one active at a time, selected by their individual CS pins). The current build has only one SPI device (the display), so bus sharing is not a concern. If a second SPI device is added in future (e.g. an SD card, external flash, or CAN controller), manage CS pins carefully — only one CS must be LOW at any time. The Mega has by far the most free pins for this; the Uno/Nano's 20-pin budget is tighter.

---

## Why Not Software SPI?

The Adafruit SSD1351 library supports both hardware and software SPI. Software SPI:
- Works on any digital pins
- Is significantly slower (~10× or more at 16MHz)
- Can cause visible flicker or lag on a 128×128 colour OLED

This project uses hardware SPI exclusively. Do not switch to software SPI without a specific hardware constraint that requires it.
