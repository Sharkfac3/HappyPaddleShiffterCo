# ArduinoCode

Arduino Mega 2560 firmware for the AW4 paddle shifter controller.
Open this folder in the Arduino IDE (`File → Open → ArduinoCode.ino`).
The IDE will automatically include the sibling `.h` and `.cpp` files.

For the full technical spec — pin assignments, state machine, solenoid truth table,
NSS wiring detail — see [`SYSTEM.md`](SYSTEM.md).

---

## Source Files

| File | Role |
|---|---|
| `ArduinoCode.ino` | `setup()`, `loop()`, main state machine, owns `currentGear` |
| `GearSelectorSwitch.h/.cpp` | AW4 NSS continuity reader — selector position + one-shot entry flags |
| `PaddleShiftIndication.h/.cpp` | Debounced shift up/down paddle switch reader |
| `SolenoidMapper.h/.cpp` | Gear 1–5 → S1/S2/SLU solenoid output states |
| `ScreenIndication.h/.cpp` | WaveShare SSD1351 OLED display wrapper |

---

## Requirements

### Hardware
| Item | Notes |
|---|---|
| Arduino Mega 2560 | Uno lacks sufficient pins and flash |
| WaveShare 1.5″ RGB OLED | SSD1351 driver, 128×128 — **3.3V only, 5V will destroy it** |
| Relay or high-side driver board | One channel per solenoid. Never drive solenoids directly from Arduino pins. |
| 1N4007 flyback diodes | One across each solenoid coil — protects the driver board |
| Paddle switches ×2 | Normally-open momentary. Wire one terminal to GND, other to Arduino pin. |

### Libraries (install via `Tools → Manage Libraries`)
| Library | Purpose |
|---|---|
| `Adafruit_SSD1351` | SSD1351 OLED driver |
| `Adafruit_GFX` | Graphics primitives — required by SSD1351 |
| `SPI` | Built-in, no install needed |

---

## Build & Flash

1. Install the libraries above via `Tools → Manage Libraries`
2. `Tools → Board → Arduino Mega 2560`
3. `Tools → Port` → select the correct COM port
4. Click **Upload**
5. Open `Tools → Serial Monitor` at **9600 baud** to confirm startup and watch state transitions
