# ArduinoCode — System Specification
## Jeep XJ Cherokee AW4 Transmission Controller (1987–2001), Arduino Mega 2560

This is the authoritative technical reference for the firmware.
It covers architecture, pin assignments, hardware wiring, the state machine, and the solenoid truth table.
For build/flash instructions see [`README.md`](README.md). For research sources see [`SOURCES.md`](../SOURCES.md).

---

## Architecture

Five classes coordinated by `ArduinoCode.ino`. Single source of truth for the currently
selected gear: `int currentGear` (1–5) declared in `ArduinoCode.ino`.

| File | Role |
|---|---|
| `ArduinoCode.ino` | `setup()`, `loop()`, state machine, owns `currentGear` |
| `PaddleShiftIndication` | Debounced shift up/down paddle reads |
| `GearSelectorSwitch` | AW4 NSS continuity reads, one-shot state entry flags |
| `SolenoidMapper` | Gear 1–5 → S1/S2/SLU output states |
| `ScreenIndication` | SSD1351 OLED display wrapper |

---

## Pin Assignments

| Pin | Direction | Mode | Connected to |
|---|---|---|---|
| 2 | INPUT | INPUT_PULLUP active LOW | Shift Up paddle → GND |
| 3 | INPUT | INPUT_PULLUP active LOW | Shift Down paddle → GND |
| 4 | INPUT | INPUT_PULLUP active LOW | NSS pin B (B↔C — Park/Neutral) → GND |
| 5 | INPUT | INPUT_PULLUP active LOW | NSS pin E (A↔E — Reverse) → GND |
| 6 | INPUT | INPUT_PULLUP active LOW | NSS pin G (A↔G — 3rd hold) → GND |
| 7 | INPUT | INPUT_PULLUP active LOW | NSS pin H (A↔H — 1-2 hold) → GND |
| 11 | OUTPUT | — | S1 solenoid via relay/driver board |
| 12 | OUTPUT | — | S2 solenoid via relay/driver board |
| 13 | OUTPUT | — | SLU solenoid via relay/driver board |
| 51 | OUTPUT | — | Display DIN — hardware MOSI, fixed on Mega |
| 52 | OUTPUT | — | Display CLK — hardware SCK, fixed on Mega |
| A3 | OUTPUT | — | Display RES |
| A4 | OUTPUT | — | Display DC |
| A5 | OUTPUT | — | Display CS |

---

## AW4 Neutral Safety Switch — Wiring & Behaviour

The AW4 NSS is a **continuity switch** — it is NOT a powered or 12V switch.
Each selector position closes a specific internal pin pair. No voltage dividers are needed.

**Wiring rule:** connect the unique leg of each pin pair to an Arduino `INPUT_PULLUP` pin.
Connect the common/shared leg to GND. When the selector closes a pair, the Arduino pin reads LOW.
Use a multimeter to confirm continuity for each position before connecting to the Arduino.

### Pin Continuity Map (FSM-verified, consistent across all XJ years)

| Selector Position | NSS Pins Closed | Arduino Pin | Notes |
|---|---|---|---|
| Park | B ↔ C | 4 | Shared with Neutral — electrically indistinguishable |
| Neutral | B ↔ C | 4 | Shared with Park — both reported as PARK/NEUTRAL |
| Reverse | A ↔ E | 5 | — |
| Drive | none | — | Detected by absence of signal — all four pins HIGH |
| 3rd hold | A ↔ G | 6 | Pin A is shared across Reverse, 3rd, and 1-2 |
| 1-2 hold | A ↔ H | 7 | Pin A is shared across Reverse, 3rd, and 1-2 |

> **Park vs Neutral:** Both close B↔C. Cannot be distinguished from the NSS alone.
> Add a separate park switch if hard differentiation is required.
>
> **Pin A sharing:** Pin A is the common leg for Reverse (A↔E), 3rd (A↔G), and 1-2 (A↔H).
> Wire each unique side (E, G, H) to its own Arduino pin. `INPUT_PULLUP` handles the shared leg correctly.
>
> **Drive:** No pins close in Drive. Detected when all four monitored pins read HIGH.

### NSS Connector by Year

| Years | Connector | NSS Part Number |
|---|---|---|
| 1987–1996 | 8-pin Deutsch, pins A–H | Omix-ADA 17216.03 / OEM 83503712 |
| 1997–2001 | Different physical connector | Omix-ADA 4882173 / OEM 4882173 |

> **Wire colours:** Factory wire colours appear in FSM connector diagrams (scanned images — not
> extractable as text). Always probe with a multimeter before wiring.

---

## Solenoid Mapping (AW4 / A340E — verified)

Solenoids are driven via an external relay or high-side driver board — **never directly from Arduino pins.**
Solenoids run on 12V and draw up to 2A. Flyback diodes (1N4007) are required across each coil.
SLU is **digital on/off** — not PWM on this AW4 variant.

| Gear | Description | S1 | S2 | SLU |
|---|---|---|---|---|
| 1 | 1st | ON | OFF | OFF |
| 2 | 2nd | ON | ON | OFF |
| 3 | 3rd | OFF | ON | OFF |
| 4 | 4th / Overdrive | OFF | OFF | OFF |
| 5 | 4th + Lockup | OFF | OFF | ON |
| — | P / R / N | OFF | OFF | OFF |

> 4th gear (all solenoids off) is the A340's electrical failsafe state.
> Reverse and Neutral are hydraulic — solenoid state has no mechanical effect there.

Sources: MaxxECU A340E wiring docs + EveryCircuit AW4 community build. See [`SOURCES.md`](../SOURCES.md).

---

## State Machine

| Selector State | Display | Solenoids | Paddle Shifting | Gear Reset |
|---|---|---|---|---|
| PARK / NEUTRAL | P | all off | disabled | → 1 |
| REVERSE | R | all off | disabled | → 1 |
| DRIVE | 1 / 2 / 3 / 4 / 4L | per solenoid map | enabled | — |
| 3RD HOLD | N* | clamp currentGear to ≤3, per map | disabled | — |
| 1-2 HOLD | 2 | clamp currentGear to ≤2, per map | disabled | — |
| UNKNOWN | blank | hold last state | disabled | — |

> \* 3RD HOLD currently calls `showNeutral()` as a placeholder — displays "N" not "3".
> See the `screen-indication` skill for instructions on adding `showThird()`.

---

## Debounce

All inputs use 50ms timestamp-based debounce (non-blocking).
All input pins are `INPUT_PULLUP`. Triggers fire on falling edge (HIGH→LOW = active/pressed).

---

## Display

WaveShare 1.5″ RGB OLED, SSD1351 driver chip, 128×128 pixels, **3.3V only**.
DIN → pin 51, CLK → pin 52 (hardware SPI on Mega — fixed, cannot be reassigned).
Library: `Adafruit_SSD1351` + `Adafruit_GFX` (install via Library Manager).
