# AW4 Selector Gate

## Gate Layout

The AW4 uses a 6-position selector gate. Moving the selector lever down (toward the driver in most XJ configurations) steps through the positions in this order:

```
P  →  R  →  N  →  D  →  3  →  2-1
```

There are physical detents at each position. The gate has a locking mechanism that requires lifting a button/collar on the selector lever to move out of Park and (depending on year) out of Reverse.

---

## Position Descriptions

| Position | Label | Transmission Behaviour |
|---|---|---|
| **P** | Park | Parking pawl engages — locks transmission output shaft. Solenoids OFF. |
| **R** | Reverse | Hydraulic reverse gear. Solenoids OFF. Engine start allowed. |
| **N** | Neutral | No drive range selected. Solenoids OFF. Engine start allowed. |
| **D** | Drive | Full 1–4 automatic (or manual with paddles in this project). Solenoids per gear. |
| **3** | 3rd hold | Limits shifts to 1st, 2nd, 3rd only. Prevents 4th gear engagement. |
| **2-1** | 1-2 hold | Limits shifts to 1st and 2nd only. Engine braking available. |

---

## NSS Signal for Each Position

| Selector Position | NSS Pins Closed | Controller State |
|---|---|---|
| P | B ↔ C | PARK/NEUTRAL |
| R | A ↔ E | REVERSE |
| N | B ↔ C | PARK/NEUTRAL (electrically same as Park) |
| D | None (all HIGH) | DRIVE |
| 3 | A ↔ G | THIRD HOLD |
| 2-1 | A ↔ H | ONE-TWO HOLD |

---

## Physical Selector Gate and Transfer Case Operations

The physical selector gate is **P → R → N → D**. To engage or disengage 4WD Low on vehicles with the NP231 transfer case, the driver must momentarily move the selector to **Neutral** while working the transfer case shift lever.

This creates a critical interaction with the controller:

**Expected sequence for 4WD Low engagement:**
1. Vehicle stopped, selector in Drive
2. Driver moves selector to Neutral (B↔C closes → PARK/NEUTRAL state)
3. Driver engages 4WD Low on transfer case lever
4. Driver moves selector back to Drive (all pins HIGH → DRIVE state)
5. Controller re-applies solenoids at the previously selected gear

**Why this matters:** If the controller resets `currentGear` to 1 every time the selector enters Neutral, the driver loses their selected gear on every 4WD Low engagement. The controller is designed to **preserve `currentGear` through Neutral** so that returning to Drive re-applies the previously selected gear.

This is distinct from Reverse: when returning from Reverse to Drive, resetting to 1st gear is correct because Reverse always requires a full stop.

See `ArduinoCode/SYSTEM.md` — "Transfer Case Operation" section — for the firmware implementation detail.

---

## Detent Positions vs Midpoints

The selector travels through mechanical detent positions. While transitioning between positions, the contact disc inside the NSS may momentarily close multiple pairs simultaneously. This is the source of the `GEAR_SEL_UNKNOWN` state in the controller — it fires briefly while the selector is physically moving between positions and is expected transient behaviour, not an error.

The controller holds the last known solenoid state and blanks the display during UNKNOWN, then transitions cleanly when the selector settles into a new position.
