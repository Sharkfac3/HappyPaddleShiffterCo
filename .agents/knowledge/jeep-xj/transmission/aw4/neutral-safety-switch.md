# AW4 Neutral Safety Switch (NSS)

## What the NSS Is

The AW4 neutral safety switch (NSS) is a **continuity switch**, not a powered switch. It contains a rotating contact disc that mechanically closes different internal pin pairs depending on the selector position.

Key implications:
- It is **NOT a 12V powered device** — do not apply any voltage to NSS pins
- It requires no voltage dividers or pull-down resistors
- Wire it using Arduino `INPUT_PULLUP` — the Arduino's internal pull-up provides the reference voltage
- When a pair closes, the Arduino pin reads **LOW** (active LOW)
- When no pair includes a given pin, it reads **HIGH** (pulled up internally)

---

## Pin Continuity Map

Verified from: **Jeep XJ 1993 Factory Service Manual** (jeep-manual.ru, page 294). Confirmed consistent across all XJ model years 1987–2001.

| Selector Position | NSS Pins Closed | Notes |
|---|---|---|
| Park | B ↔ C | Electrically identical to Neutral — cannot be distinguished |
| Neutral | B ↔ C | Electrically identical to Park — both treated as PARK/NEUTRAL |
| Reverse | A ↔ E | — |
| Drive | None | Detected by absence of all signals — all pins read HIGH |
| 3rd hold | A ↔ G | Pin A is the shared common leg for R, 3rd, and 1-2 |
| 1-2 hold | A ↔ H | Pin A is the shared common leg for R, 3rd, and 1-2 |

### Pin A Sharing

Pin A appears in three positions: Reverse (A↔E), 3rd hold (A↔G), and 1-2 hold (A↔H). It is the common leg. When wiring:
- Connect pin A to GND (common return)
- Connect the unique side of each pair (E, G, H) to its own Arduino `INPUT_PULLUP` pin
- Do not wire pin A to an Arduino input — it carries no position-specific information on its own

### Park vs Neutral

Park and Neutral both close pin pair B↔C. They are electrically indistinguishable from the NSS alone. If you need to distinguish them, a separate park switch (e.g. a switch on the selector mechanism that only activates in Park) is required. This project treats both as PARK/NEUTRAL and does not attempt to distinguish them.

---

## Connectors by Year

### 1987–1996 — 8-pin Deutsch DT Connector

| Attribute | Value |
|---|---|
| Connector type | Deutsch DT series, 8-pin |
| Pin designators | A, B, C, D, E, F, G, H |
| OEM part number | 83503712 |
| Aftermarket (Omix-ADA) | 17216.03 |
| Physical location | Left (driver's) side of transmission, near selector shaft |

### 1997–2001 — Different Physical Housing

| Attribute | Value |
|---|---|
| Connector type | Different physical housing from '87–'96 — not interchangeable |
| OEM part number | 4882173 |
| Aftermarket (Omix-ADA) | 4882173 |
| Electrical behaviour | Identical continuity map to '87–'96 |

> ❓ UNVERIFIED: The exact connector type (Molex, Deutsch, etc.) and pin designators for the '97–'01 NSS have not been confirmed from a primary source. Research role should verify from the 1997 or later XJ FSM.

---

## Wire Colours

> ⚠️ Wire colours for the NSS harness **cannot be reliably extracted from scanned FSM images**. All known FSM wiring diagrams for the NSS connector are scanned images — not text-extractable. Wire colours vary by year and production batch.

**Always use a multimeter to confirm continuity before connecting wires to the Arduino.** The continuity map above is the reliable reference — wire colours are not.

Procedure:
1. Disconnect the NSS connector
2. Set multimeter to continuity / resistance mode
3. Move selector to each position (P, R, N, D, 3, 2-1) one at a time
4. Probe pairs of NSS pins to find which pair shows continuity in each position
5. Map your wire colours to pin labels based on the confirmed continuity

---

## Wiring to Arduino

Each unique NSS pin (B, E, G, H) goes to its own Arduino `INPUT_PULLUP` pin. Pin C and the non-A sides of pairs go to the same Arduino pin as their partner. Pin A goes to GND.

Standard wiring:

| NSS Pin | Function | Arduino Connection |
|---|---|---|
| A | Common (shared leg for R, 3rd, 1-2) | GND |
| B | Park/Neutral (B↔C) | Arduino INPUT_PULLUP pin |
| C | Park/Neutral (B↔C) | GND (or Arduino INPUT_PULLUP — B and C are interchangeable) |
| D | Unused in this project | Leave disconnected |
| E | Reverse (A↔E) | Arduino INPUT_PULLUP pin |
| F | Unused in this project | Leave disconnected |
| G | 3rd hold (A↔G) | Arduino INPUT_PULLUP pin |
| H | 1-2 hold (A↔H) | Arduino INPUT_PULLUP pin |

For the specific Arduino pin numbers used in the firmware, see `ArduinoCode/SYSTEM.md`.

---

## Sources

| Source | URL | Status |
|---|---|---|
| Jeep XJ 1993 FSM — NSS continuity spec | https://jeep-manual.ru/index.php?page=294 | ✅ Read |
| Montana Fab AW4 override instructions | https://montanafab.com/wp-content/uploads/2018/01/tranny_instructions_rev.-5-20-16.pdf | ✅ Read |
| ATSG AW4 Service Information | https://cdn.xjjeeps.com/pdf/en-us/aw4-transmission-service-information.pdf | ✅ Read |
