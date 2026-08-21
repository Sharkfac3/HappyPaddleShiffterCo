# Arduino Pin Assignments for This Project

This table documents how the project's pins are used, using the Mega 2560's pin numbers as the
reference column. Pin numbers are identical on the Uno and Nano except the display's
hardware-SPI pins — see the Hardware SPI row below and
[`../board-comparison.md`](../board-comparison.md) for the full Uno/Nano/Mega comparison. For
the firmware `#define` names, see `Firmware/ArduinoCode/SYSTEM.md`.

---

## Used Pins

| Arduino Pin | Physical Role | Direction | Mode | Connected To | Notes |
|---|---|---|---|---|---|
| 0 (RX) | Serial receive | INPUT | Hardware UART | USB / Serial monitor | Do not use for other purposes |
| 1 (TX) | Serial transmit | OUTPUT | Hardware UART | USB / Serial monitor | Do not use for other purposes |
| 2 | Shift Up paddle | INPUT | plain INPUT | Paddle sensor DO | Sensor drives line; do not use INPUT_PULLUP |
| 3 | Shift Down paddle | INPUT | plain INPUT | Paddle sensor DO | Sensor drives line; do not use INPUT_PULLUP |
| 4 | NSS Park/Neutral | INPUT | INPUT_PULLUP | NSS pin B → GND (via B↔C closure) | Active LOW |
| 5 | NSS Reverse | INPUT | INPUT_PULLUP | NSS pin E → GND (via A↔E closure) | Active LOW |
| 6 | NSS 3rd hold | INPUT | INPUT_PULLUP | NSS pin G → GND (via A↔G closure) | Active LOW |
| 7 | NSS 1-2 hold | INPUT | INPUT_PULLUP | NSS pin H → GND (via A↔H closure) | Active LOW |
| A0 | S1 solenoid output | OUTPUT | — | Driver board channel 1 → S1 solenoid | 5V logic to driver board; solenoid itself is 12V |
| A1 | S2 solenoid output | OUTPUT | — | Driver board channel 2 → S2 solenoid | 5V logic to driver board |
| A2 | SLU solenoid output | OUTPUT | — | Driver board channel 3 → SLU solenoid | 5V logic to driver board |
| 51 (Mega) / 11 (Uno, Nano) | Display DIN (MOSI) | OUTPUT | Hardware SPI | SSD1351 display DIN | **Fixed hardware SPI pin — cannot be changed; auto-selected by SPI library per board** |
| 52 (Mega) / 13 (Uno, Nano) | Display CLK (SCK) | OUTPUT | Hardware SPI | SSD1351 display CLK | **Fixed hardware SPI pin — cannot be changed; auto-selected by SPI library per board** |
| A3 | Display RST | OUTPUT | Digital | SSD1351 display RES | Used as digital output via `analogPinToDigitalPin()`. Board silkscreen may say "RST" instead of "RES" — same pin, not a different display variant. |
| A4 | Display DC | OUTPUT | Digital | SSD1351 display DC | — |
| A5 | Display CS | OUTPUT | Digital | SSD1351 display CS | — |

---

## Available / Unused Pins (Mega)

The Mega has 54 digital and 16 analog pins. The following are currently unused and available for future expansion:

| Range | Notes |
|---|---|
| D8–D10 | Digital I/O — available |
| D14–D43 | Digital I/O — available (D14–D19 are hardware UART TX/RX for Serial1–Serial3) |
| D44–D46 | PWM-capable — available |
| D47–D50 | Digital I/O — available |
| D53 | Hardware SPI SS — available (SPI SS is managed by Adafruit library on CS pin A5) |
| A6–A15 | Analog input / digital I/O — available |

Note: A0–A2 are used by this project (solenoid outputs) on all three boards — no longer
available on any of them. On the Uno and Nano, digital 11 and 13 are also committed (display
hardware SPI); digital 12 (MISO) is unused but reserved if SPI is ever shared with a second
device.

## Available / Unused Pins (Uno / Nano)

The Uno and Nano have 20 usable I/O pins (14 digital + 6 analog-as-digital; the Nano's A6/A7
are analog-input-only and unused by this project). After this project's pin usage (D2–D7,
A0–A5, D11/D13 for display SPI), the following remain free:

| Range | Notes |
|---|---|
| D8, D9, D10, D12 | Digital I/O — available (D12/MISO reserved if SPI is ever shared) |
| D0, D1 | Serial TX/RX — available only if Serial is not needed |
| A6, A7 (Nano only) | Analog input only — not usable as digital I/O |

Headroom for future expansion is far tighter on the Uno/Nano than the Mega — see
`../board-comparison.md` "Choosing a Board" if a future feature needs more free pins.

---

## Pin Constraints to Remember

- **Display hardware-SPI pins are fixed and board-specific** — 51/52 on the Mega, 11/13 on the
  Uno and Nano — they cannot be reassigned for any other function while SPI is in use
- **Pins 0 and 1 are Serial TX/RX** — used by Serial.begin(9600); avoid using them as GPIO
- **Pin 13 has an onboard LED on all three boards** — HIGH on pin 13 also lights it; cosmetic
  only, but on the Uno and Nano pin 13 is also the display's hardware SCK, so this is expected
  during SPI writes
- **A0–A2, A3, A4, A5 used as digital outputs** — do not configure them as analog inputs in any new code
