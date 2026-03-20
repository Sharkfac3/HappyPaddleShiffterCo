# AW4 / A340E Transmission — Knowledge Index

Complete technical reference for the AW4 automatic transmission as used in the Jeep XJ Cherokee.

---

## Files in This Section

| File | Contents |
|---|---|
| [`overview.md`](overview.md) | Transmission background, Toyota lineage, variants, gear ratios |
| [`solenoids.md`](solenoids.md) | S1, S2, SLU solenoid specs and verified truth table |
| [`neutral-safety-switch.md`](neutral-safety-switch.md) | NSS pin continuity map, connector types, wiring procedure |
| [`selector-gate.md`](selector-gate.md) | Selector gate positions (P/R/N/D/3/2-1), detents, mechanical behaviour |

---

## Quick Reference — Solenoid Truth Table

Verified against MaxxECU A340E docs and EveryCircuit AW4 community build. See [`solenoids.md`](solenoids.md) for sources and full specs.

| Gear | S1 | S2 | SLU |
|---|---|---|---|
| 1st | ON | OFF | OFF |
| 2nd | ON | ON | OFF |
| 3rd | OFF | ON | OFF |
| 4th (OD) | OFF | OFF | OFF |
| 4th + Lockup | OFF | OFF | ON |
| P / R / N | OFF | OFF | OFF |

> 4th gear (all solenoids OFF) is the **electrical failsafe state** — if the controller loses power, the transmission defaults to 4th gear hydraulically.

---

## Quick Reference — NSS Continuity Map

Verified from Jeep XJ 1993 FSM. Consistent across all XJ years. See [`neutral-safety-switch.md`](neutral-safety-switch.md) for full wiring detail.

| Selector Position | NSS Pins Closed | Notes |
|---|---|---|
| Park | B ↔ C | Shared with Neutral — electrically identical |
| Neutral | B ↔ C | Shared with Park — cannot be distinguished |
| Reverse | A ↔ E | — |
| Drive | None | Detected by absence of all signals |
| 3rd hold | A ↔ G | Pin A is shared common leg |
| 1-2 hold | A ↔ H | Pin A is shared common leg |
