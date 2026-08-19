# Firmware — System Specification
## Jeep XJ Cherokee AW4 Transmission Controller (1987–2001), Arduino Uno (default), Mega 2560, or Nano

This is the authoritative technical reference for the firmware.
It covers architecture, pin assignments, hardware wiring, the state machine, and the solenoid truth table.
For build/flash instructions see [`README.md`](README.md). For research sources see [`SOURCES.md`](../SOURCES.md).

### Supported Boards

Same firmware, same `#define` pin numbers, same wiring — works unchanged on any of the three
boards, no `#ifdef` branching. Solenoid outputs sit on A0–A2 specifically so they don't collide with
the Uno's fixed hardware-SPI pins (MOSI=11, SCK=13); the Mega's hardware SPI (MOSI=51, SCK=52)
was never on those pins either. The display's DIN/CLK hardware-SPI pins are auto-selected by
the SPI library per board — not a `#define` in this project. See `DECISIONS.md` ADR-008/ADR-009.

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
| 2 | INPUT | plain INPUT — sensor drives line, tab-in-slot-at-rest = HIGH | Shift Up IR slot optocoupler DO |
| 3 | INPUT | plain INPUT — sensor drives line, tab-in-slot-at-rest = HIGH | Shift Down IR slot optocoupler DO |
| 4 | INPUT | INPUT_PULLUP active LOW | NSS pin B (B↔C — Park/Neutral) → GND |
| 5 | INPUT | INPUT_PULLUP active LOW | NSS pin E (A↔E — Reverse) → GND |
| 6 | INPUT | INPUT_PULLUP active LOW | NSS pin G (A↔G — 3rd hold) → GND |
| 7 | INPUT | INPUT_PULLUP active LOW | NSS pin H (A↔H — 1-2 hold) → GND |
| A0 | OUTPUT | — | S1 solenoid via relay/driver board |
| A1 | OUTPUT | — | S2 solenoid via relay/driver board |
| A2 | OUTPUT | — | SLU solenoid via relay/driver board |
| A3 | OUTPUT | — | Display RES |
| A4 | OUTPUT | — | Display DC |
| A5 | OUTPUT | — | Display CS |
| MOSI (hw SPI) | OUTPUT | — | Display DIN — pin 11 on Uno, pin 51 on Mega, fixed, auto-selected by SPI library |
| SCK (hw SPI) | OUTPUT | — | Display CLK — pin 13 on Uno, pin 52 on Mega, fixed, auto-selected by SPI library |

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
S1/S2/SLU outputs are on A0/A1/A2 (see Pin Assignments above) — moved off 11/12/13 so they
don't collide with the Uno's fixed hardware-SPI pins.

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

| Selector State | Display | Solenoids | Paddle Shifting | currentGear |
|---|---|---|---|---|
| PARK / NEUTRAL | P | all off | disabled | **preserved** (startup: 1) |
| REVERSE | R | all off | disabled | → 1 |
| DRIVE | 1 / 2 / 3 / 4 / 4L | per solenoid map | enabled | — |
| 3RD HOLD | N* | clamp currentGear to ≤3, per map | disabled | clamped if > 3 |
| 1-2 HOLD | 2 | clamp currentGear to ≤2, per map | disabled | clamped if > 2 |
| UNKNOWN | blank | hold last state | disabled | — |

> \* 3RD HOLD currently calls `showNeutral()` as a placeholder — displays "N" not "3".
> See the `screen-indication` skill for instructions on adding `showThird()`.

### Transfer Case Operation

The physical selector gate is **P → R → N → D**. Engaging 4WD Low requires the vehicle
to be stopped and the selector moved to Neutral while the transfer case lever is worked.

Expected sequence: **Drive → Neutral → (work lever) → Drive**

`currentGear` is preserved through Neutral. When the selector returns to Drive,
`justEnteredDrive()` re-applies `solenoids.applyGear(currentGear)` at the gear that was
active before Neutral — no gear is lost.

> **Do NOT reset `currentGear` in the `justEnteredParkNeutral()` handler.** This was the
> original bug. The startup-only path (`applyState()`) initialises to 1 because there is
> no previous gear at power-on — that reset is correct and intentional only there.
>
> **Reverse resets to 1 (this is correct).** Reverse always requires a full stop.
> Resetting to 1st ensures 1st gear is always engaged when returning from Reverse to Drive.

---

## Debounce

All inputs use 50ms timestamp-based debounce (non-blocking).
NSS pins (4–7) are `INPUT_PULLUP`. Paddle sensor pins (2–3) are plain `INPUT` —
the IR slot optocoupler drives its own output, INPUT_PULLUP would fight it.
All triggers fire on falling edge (HIGH→LOW = active/pressed).

---

## Display

WaveShare 1.5″ RGB OLED, SSD1351 driver chip, 128×128 pixels, **3.3V only**.
DIN → hardware MOSI, CLK → hardware SCK — fixed per board, cannot be reassigned
(Uno: 11/13, Mega: 51/52; the `Adafruit_SSD1351` library selects the right pins
automatically for whichever board the sketch is compiled for).
Library: `Adafruit_SSD1351` + `Adafruit_GFX` (install via Library Manager).
