# Arduino Mega 2560 — Hardware SPI

## What is Hardware SPI?

The ATmega2560 has a hardware SPI peripheral that handles serial data clocking in silicon, separate from general-purpose I/O. Hardware SPI is significantly faster and more reliable than software ("bit-bang") SPI for display communication.

---

## Hardware SPI Pins on the Mega 2560

| SPI Signal | Arduino Pin | Notes |
|---|---|---|
| MOSI (Master Out Slave In) | **51** | Data from Arduino to display |
| MISO (Master In Slave Out) | **50** | Data from peripheral to Arduino (not used by SSD1351) |
| SCK (Serial Clock) | **52** | Clock signal |
| SS (Slave Select) | **53** | Hardware SS — not used directly; CS managed via software (A5) |

> ⚠️ CRITICAL: **Pins 51 and 52 are the only valid hardware SPI pins on the Mega.** On the Uno/Nano, hardware SPI uses pins 11 and 13. On the Mega, it is 51 and 52. If you wire the display to 11 and 13 on a Mega, SPI will not function — those pins are ordinary GPIO on the Mega. This is a common mistake when adapting Uno examples to the Mega.

---

## SSD1351 Display SPI Wiring (This Project)

| SSD1351 Pin | Connected to | Notes |
|---|---|---|
| DIN | Mega pin 51 (MOSI) | Hardware SPI — fixed |
| CLK | Mega pin 52 (SCK) | Hardware SPI — fixed |
| CS | Mega pin A5 | Software chip select — can be reassigned |
| DC | Mega pin A4 | Data/command select — can be reassigned |
| RES | Mega pin A3 | Reset — can be reassigned |
| VCC | Mega 3.3V pin | **3.3V ONLY — never 5V** |
| GND | Mega GND | — |

Only DIN and CLK are fixed. CS, DC, and RES can be moved to any available digital output pin by updating the `#define` values in `ArduinoCode.ino` and the `ScreenIndication` constructor call.

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

The hardware SPI bus on the Mega can be shared between multiple devices (only one active at a time, selected by their individual CS pins). The current build has only one SPI device (the display), so bus sharing is not a concern. If a second SPI device is added in future (e.g. an SD card, external flash, or CAN controller), manage CS pins carefully — only one CS must be LOW at any time.

---

## Why Not Software SPI?

The Adafruit SSD1351 library supports both hardware and software SPI. Software SPI:
- Works on any digital pins
- Is significantly slower (~10× or more at 16MHz)
- Can cause visible flicker or lag on a 128×128 colour OLED

This project uses hardware SPI exclusively. Do not switch to software SPI without a specific hardware constraint that requires it.
