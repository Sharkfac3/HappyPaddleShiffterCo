# Firmware Validation Checklist

How to verify firmware changes are correct before committing.
There is no automated test suite — validation is manual and procedural.

---

## Before You Change Anything

1. Read `ArduinoCode/SYSTEM.md` — confirm your understanding of the state machine.
2. Read `.agents/DECISIONS.md` — confirm your change does not contradict a recorded decision.
3. Read the relevant skill file — confirm you understand the subsystem constraints.

---

## Serial Monitor Sanity Check

After flashing, open Serial Monitor at **9600 baud**. Cycle through each selector position
and confirm the expected output appears.

| Action | Expected Serial Output |
|---|---|
| Power on in Park/Neutral | `AW4 Controller — Starting up` then `INIT: PARK/NEUTRAL` |
| Power on in Drive | `AW4 Controller — Starting up` then `INIT: DRIVE gear 1` |
| Move selector to Drive | `-> DRIVE \| gear 1` |
| Press shift up (in Drive) | `SHIFT UP -> gear 2` |
| Press shift down (in Drive) | `SHIFT DOWN -> gear 1` |
| Move to Park/Neutral | `-> PARK/NEUTRAL \| solenoids off \| gear preserved at X` |
| Move to Reverse | `-> REVERSE \| gear reset to 1 \| solenoids off` |
| Move to 3rd hold | `-> 3RD HOLD \| clamped to max 3rd` |
| Move to 1-2 hold | `-> 1-2 HOLD \| clamped to max 2nd` |

---

## Solenoid State Verification

If a relay/driver board is connected (bench test only — do NOT connect to running vehicle):

| Gear | S1 | S2 | SLU | Expected relay state |
|---|---|---|---|---|
| 1 | ON | OFF | OFF | CH1 energised |
| 2 | ON | ON | OFF | CH1 + CH2 energised |
| 3 | OFF | ON | OFF | CH2 energised |
| 4 | OFF | OFF | OFF | All off |
| 5 | OFF | OFF | ON | CH3 (SLU) energised |
| P/R/N | OFF | OFF | OFF | All off |

---

## State Machine Checks

Verify these specific behaviours after any change to `ArduinoCode.ino`:

- [ ] Shifting up at GEAR_MAX (5) does nothing
- [ ] Shifting down at GEAR_MIN (1) does nothing
- [ ] Entering Neutral then returning to Drive resumes at the same gear (not 1)
- [ ] Entering Reverse resets to 1st
- [ ] 3rd hold clamps currentGear to ≤3
- [ ] 1-2 hold clamps currentGear to ≤2
- [ ] UNKNOWN state shows blank display
- [ ] `justEntered*()` handlers each fire exactly once per transition (not repeatedly)

---

## Common Mistakes to Check

- `currentGear` reset inside `justEnteredParkNeutral()` — must NOT happen
- `update()` not called at the top of `loop()` before `getState()`
- `justEntered*()` called before `selector.update()` (stale flags)
- `shiftUpRequested()` or `shiftDownRequested()` called before `paddle.update()`
- `delay()` used anywhere in the main loop
