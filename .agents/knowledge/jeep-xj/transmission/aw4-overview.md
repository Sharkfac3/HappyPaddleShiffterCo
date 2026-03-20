# AW4 Transmission — Overview

## What the AW4 Is

The AW4 is Jeep's name for the **Toyota/Aisin A340E** automatic transmission, used in
Jeep XJ Cherokees from 1987 to 2001. It is a 4-speed automatic with an optional
torque converter lock-up clutch (controlled by the SLU solenoid).

The A340E and AW4 share the same solenoid mapping and hydraulic control logic.
Documentation for the Toyota A340E applies directly to the AW4.

## What We Are Replacing

The factory AW4 is controlled by a **Transmission Control Unit (TCU)** that shifts
automatically based on vehicle speed, throttle position, and other inputs. This project
**bypasses the factory TCU entirely**. The Arduino Mega takes over all shift decisions.

The driver controls gear selection directly via steering-wheel paddles (shift up / shift down)
and the gear selector switch (Park, Reverse, Neutral, Drive, 3rd hold, 1-2 hold).

## Gear Ranges

| Selector Position | Gears Available | Notes |
|---|---|---|
| Drive (D) | 1, 2, 3, 4, 4+Lockup (5) | Full range, paddle-controlled |
| 3rd hold | 1, 2, 3 | Engine braking in mountainous terrain |
| 1-2 hold | 1, 2 | Maximum engine braking, off-road crawling |
| Reverse | — | Hydraulic — solenoid state irrelevant |
| Park / Neutral | — | Hydraulic — solenoids off |

## Why 4th (All Solenoids Off) Is the Failsafe

The A340E is hydraulically designed so that 4th gear (overdrive) engages when all
shift solenoids are de-energised. This means if the controller loses power or the
Arduino resets, the transmission defaults to 4th gear automatically.

This is the electrical failsafe state. The Arduino leverages this by calling `allOff()`
on startup and in Park/Reverse/Neutral — all safe states.

## Solenoids

Three solenoids are electronically controlled:
- **S1** — Shift solenoid 1 (gear selection)
- **S2** — Shift solenoid 2 (gear selection)
- **SLU** — Shift lock-up (torque converter lock-up clutch)

See `solenoid-truth-table.md` for the verified state table.
See `.agents/skills/solenoid-mapper/SKILL.md` for the firmware implementation.
