# AW4 Neutral Safety Switch (NSS) — Wiring Reference

## What the NSS Is

The AW4 neutral safety switch is a **continuity switch** — it physically closes
specific pin pairs for each selector position. It is NOT a 12V powered switch.
No voltage dividers are needed. Wire using Arduino `INPUT_PULLUP`.

## How to Wire It

1. Identify the unique pin for each selector position (E, G, H, and one side of B/C).
2. Connect each unique pin to an Arduino `INPUT_PULLUP` digital input.
3. Connect the common/shared side to GND.
4. When the selector closes a pair, the Arduino pin reads LOW (active LOW).
5. Drive is detected by **absence** — when all four monitored pins read HIGH.

## Continuity Map — All XJ Years (Consistent)

Source: Jeep XJ 1993 FSM (confirmed consistent across all model years).

| Selector Position | NSS Pins Closed | Arduino Pin | Signal when selected |
|---|---|---|---|
| Park | B ↔ C | 4 | LOW |
| Neutral | B ↔ C | 4 | LOW (same as Park — cannot distinguish) |
| Reverse | A ↔ E | 5 | LOW |
| Drive | (none) | — | All pins HIGH |
| 3rd hold | A ↔ G | 6 | LOW |
| 1-2 hold | A ↔ H | 7 | LOW |

## Important Wiring Notes

**Pin A is shared.** Pin A is the common leg for Reverse (A↔E), 3rd (A↔G), and
1-2 (A↔H). Wire each unique side (E, G, H) to its own Arduino pin. Wire Pin A to GND.
`INPUT_PULLUP` handles the shared leg correctly — no conflicts.

**Park and Neutral share B↔C.** They cannot be distinguished by the NSS alone.
Both positions are reported as `GEAR_SEL_PARK_NEUTRAL` in firmware.
If hard Park vs Neutral differentiation is needed, a separate park-pawl switch is required.

**Wire colour warning:** Factory wire colours appear in FSM connector images (scanned).
Do not rely on wire colour alone — always verify each position with a multimeter
before connecting to the Arduino.

## Connector Variants by Year

| Years | Connector | OEM Part # | Aftermarket |
|---|---|---|---|
| 1987–1996 | 8-pin Deutsch, pins A–H | 83503712 | Omix-ADA 17216.03 |
| 1997–2001 | Different physical connector | 4882173 | Omix-ADA 4882173 |

The continuity map (which pins close for which position) is the same for both variants.
Only the physical housing is different.

> **1997–2001 pinout:** The exact pin-label-to-wire mapping for the '97–'01 connector
> has not been independently verified from a primary source. Use a multimeter to confirm
> before wiring. See `SOURCES.md` for research status.
