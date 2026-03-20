# Arduino Mega 2560 — Pin Assignments for This Project

This table documents how the Arduino Mega 2560 pins are used in the paddle shifter controller. For the firmware `#define` names, see `ArduinoCode/SYSTEM.md`.

---

## Used Pins

| Arduino Pin | Physical Role | Direction | Mode | Connected To | Notes |
|---|---|---|---|---|---|
| 0 (RX) | Serial receive | INPUT | Hardware UART | USB / Serial monitor | Do not use for other purposes |
| 1 (TX) | Serial transmit | OUTPUT | Hardware UART | USB / Serial monitor | Do not use for other purposes |
| 2 | Shift Up paddle | INPUT | INPUT_PULLUP | Paddle switch → GND | Active LOW; pin supports hardware interrupt |
| 3 | Shift Down paddle | INPUT | INPUT_PULLUP | Paddle switch → GND | Active LOW; pin supports hardware interrupt |
| 4 | NSS Park/Neutral | INPUT | INPUT_PULLUP | NSS pin B → GND (via B↔C closure) | Active LOW |
| 5 | NSS Reverse | INPUT | INPUT_PULLUP | NSS pin E → GND (via A↔E closure) | Active LOW |
| 6 | NSS 3rd hold | INPUT | INPUT_PULLUP | NSS pin G → GND (via A↔G closure) | Active LOW |
| 7 | NSS 1-2 hold | INPUT | INPUT_PULLUP | NSS pin H → GND (via A↔H closure) | Active LOW |
| 11 | S1 solenoid output | OUTPUT | — | Driver board channel 1 → S1 solenoid | 5V logic to driver board; solenoid itself is 12V |
| 12 | S2 solenoid output | OUTPUT | — | Driver board channel 2 → S2 solenoid | 5V logic to driver board |
| 13 | SLU solenoid output | OUTPUT | — | Driver board channel 3 → SLU solenoid | 5V logic to driver board |
| 51 | Display DIN (MOSI) | OUTPUT | Hardware SPI | SSD1351 display DIN | **Fixed hardware SPI pin — cannot be changed** |
| 52 | Display CLK (SCK) | OUTPUT | Hardware SPI | SSD1351 display CLK | **Fixed hardware SPI pin — cannot be changed** |
| A3 | Display RST | OUTPUT | Digital | SSD1351 display RES | Used as digital output via `analogPinToDigitalPin()` |
| A4 | Display DC | OUTPUT | Digital | SSD1351 display DC | — |
| A5 | Display CS | OUTPUT | Digital | SSD1351 display CS | — |

---

## Available / Unused Pins

The Mega has 54 digital and 16 analog pins. The following are currently unused and available for future expansion:

| Range | Notes |
|---|---|
| D8–D10 | Digital I/O — available |
| D14–D43 | Digital I/O — available (D14–D19 are hardware UART TX/RX for Serial1–Serial3) |
| D44–D46 | PWM-capable — available |
| D47–D50 | Digital I/O — available |
| D53 | Hardware SPI SS — available (SPI SS is managed by Adafruit library on CS pin A5) |
| A0–A2 | Analog input / digital I/O — available |
| A6–A15 | Analog input / digital I/O — available |

---

## Pin Constraints to Remember

- **Pins 51 and 52 are hardware SPI — they cannot be reassigned** for any other function while SPI is in use
- **Pins 0 and 1 are Serial TX/RX** — used by Serial.begin(9600); avoid using them as GPIO
- **Pin 13 has an onboard LED** — HIGH on pin 13 also lights the onboard LED; this is cosmetic and does not affect solenoid function
- **A3, A4, A5 used as digital outputs** — do not configure them as analog inputs in any new code
