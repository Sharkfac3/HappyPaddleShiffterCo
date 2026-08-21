# Models — Paddle Shifter Hardware

> **Applies to:** HappyPaddleShifterCo — Jeep XJ Cherokee AW4 paddle shifter controller
> **Last verified:** 2026-08-17
> **Related files:** `Firmware/ArduinoCode/SYSTEM.md` (pin assignments), `Schematics/README.md` (wiring), `SOURCES.md` (component sources)
>
> **2026-08-17: Paddle trigger sensor changed.** This document previously covered the Omron
> D2JW-01K11 mechanical switch. The project has moved to an IR slot-type optocoupler sensor
> to eliminate mechanical wear — see [Sensor Detail](#sensor-detail--ir-slot-type-optocoupler)
> below. **The switch pocket geometry described in the old version of this doc no longer
> applies** — a slot-type geometry is needed instead, and that redesign is not yet done.

3D-printable STL files for the physical paddle hardware — the left and right paddles that
mount to the steering wheel and actuate the gear shift switches.

---

## Contents of This Directory

| File / Folder | Description |
|---|---|
| STL files | Printable paddle bodies, switch pockets, and mounting brackets (add filenames here as parts are finalised) |
| Source CAD files | `.f3d`, `.step`, or `.3mf` source files if available |

---

## Bill of Materials — Non-Printed Hardware

These are the purchased components required to complete each paddle assembly. Print quantities
are per paddle; the full build requires two paddles (left and right).

| Qty per Paddle | Qty Total (2 paddles) | Description | Specification | Part Number | Notes |
|---|---|---|---|---|---|
| 1 | 2 | Paddle trigger sensor | IR slot-type optocoupler, LM393-based, 3.3–5V, DO output only | **[UNVERIFIED — generic/unbranded, AliExpress item 3256804480682852]** | Selected sensor (replaces Omron D2JW-01K11). Bare PCB, not automotive/vibration rated as shipped — see [Sensor Detail](#sensor-detail--ir-slot-type-optocoupler) below for required mitigations. |
| — | — | Sensor mounting fasteners | **[PENDING — not yet designed]** | — | Sensor board must be rigid-mounted to the paddle body (no free-hanging PCB); exact fastener spec depends on the not-yet-designed slot pocket geometry. See Sensor Detail below. |
| — | — | Conformal coating or potting compound | **[UNVERIFIED — not yet selected]** | — | Recommended to protect the bare sensor PCB from vibration and moisture; product not yet chosen. |
| — | — | Wire leads | Lightweight hookup wire, 26–28 AWG | — | Short runs from sensor pads (VCC, GND, DO) to PCB or Arduino — solder direct, skip Dupont/header connectors. Exact length depends on routing in your steering column. See `Schematics/README.md` for wiring. |
| — | — | Fasteners (steering wheel mount) | [UNVERIFIED — confirm before purchasing] | — | Fastener spec depends on your steering wheel and bracket design. Add here once mounting method is finalised. |

> **Total estimated cost:** [UNVERIFIED — confirm before purchasing]

[PENDING RESEARCH — see HANDOFFS.md]: Confirm optocoupler module PCB dimensions and slot gap
so the paddle body pocket can be designed. Confirm steering wheel mounting fastener type.
The former D2JW-01K11 M2 fastener research is no longer needed — that switch has been replaced.

---

## Sensor Detail — IR Slot-Type Optocoupler

The IR slot-type optocoupler (LM393-based) is the current paddle trigger sensor as of
2026-08-17. It replaces the former Omron D2JW-01K11 mechanical switch to eliminate mechanical
wear. **This is not a lever-actuated switch geometry — the mechanical requirement is
fundamentally different, and the paddle 3D model needs a new pocket design, not a depth
tweak of the old switch pocket.**

### Confirmed Electrical Facts

| Parameter | Value |
|---|---|
| Sensor type | Slot-type IR optocoupler (photointerrupter) — NOT Hall effect |
| Comparator IC | LM393 |
| Operating voltage | 3.3V–5V — works on Uno, Mega, or Nano, no level-shifting needed |
| Pins | VCC, GND, DO (digital output only) |
| Output type | Actively driven push-pull — do **not** use Arduino `INPUT_PULLUP` |
| Output polarity | Slot unobstructed → DO LOW. Tab in slot → DO HIGH. |
| Confirmed mechanical orientation (2026-08-17, user) | Tab sits **in** the slot at rest; paddle pull clears it |
| IP rating | None — bare PCB as shipped |

Source: `SOURCES.md` → "Paddle Trigger Sensor — IR Slot-Type Optocoupler (LM393), User-Owned Part".

### Mechanical Requirement — [PENDING — Geometry Not Yet Designed]

> ⚠️ **The paddle body pocket for this sensor has not been designed.** Unlike the switch it
> replaces, this sensor needs an opaque tab to pass through a slot gap on the paddle
> mechanism (approximate gap ~5mm — **[UNVERIFIED]**, not independently sourced). Exact
> module PCB dimensions and mounting hole layout are not yet confirmed.
>
> [PENDING RESEARCH — see HANDOFFS.md]: Confirm the optocoupler module's physical PCB
> dimensions, slot gap width, and any mounting holes from the AliExpress listing or by
> direct measurement, so the paddle pocket geometry can be modeled.

### Required Mitigations (Bare, Unrated PCB)

Because this module ships with no IP rating and no automotive/vibration qualification:
- Solder wires direct to the module pads — skip Dupont/header connectors
- Strain-relief the leads at the PCB
- Rigid-mount the board to the paddle body — no free-hanging PCB
- Conformal-coat or pot the board for vibration and moisture resistance

### Sourcing Note

This is a **generic/unbranded AliExpress module** (item 3256804480682852), not a stable
sourced part like the Omron switches it replaces. Verify supplier stock before relying on it
for a repeat build.

---

## Print Settings

> ⚠️ These settings are **[UNVERIFIED — confirm before printing]**. They represent
> reasonable starting points for structural paddle hardware; adjust to suit your printer
> and material.

[PENDING RESEARCH — see HANDOFFS.md]: Print settings (material, layer height, infill, orientation, supports) have not been formally specified or tested. Research role to confirm and document tested settings before these values are published as authoritative.

| Parameter | Recommended Starting Point | Notes |
|---|---|---|
| Material | PETG or ABS | [UNVERIFIED] — PETG preferred for dimensional stability and mild flexibility; ABS for higher heat resistance. PLA not recommended for in-cabin use (summer temperatures). |
| Layer height | 0.2 mm | [UNVERIFIED] |
| Infill | 40 % | [UNVERIFIED] — Switch pocket walls and mounting boss areas may need higher infill or solid layers for thread engagement. |
| Supports | Yes — switch pocket area | [UNVERIFIED] — Pocket geometry will determine support requirement. Review slicer preview. |
| Print orientation | [UNVERIFIED] | Optimise so the switch pocket floor prints as a flat surface without supports if possible. |
| Perimeters / walls | 3 minimum | [UNVERIFIED] — Additional perimeters recommended around mounting bosses. |

---

## Assembly Notes

> **2026-08-17:** Steps below reflect the optocoupler sensor. Step 2 (mounting in the paddle
> body) is **blocked** — see [Mechanical Requirement](#mechanical-requirement--pending--geometry-not-yet-designed)
> above — until the slot-pocket geometry is designed.

### Step 1 — Prepare the Sensor

**Do:** Solder three short wire leads (26–28 AWG, length to suit your routing) directly to
the module's VCC, GND, and DO pads — skip Dupont/header connectors, this module is not rated
for vibration and a crimped connector is a failure point. Insulate each connection with
heat-shrink tubing and add strain relief at the PCB.

**Verify:** Power the module at 3.3–5V. With the slot clear (nothing blocking it), DO should
read LOW. Pass an opaque object through the slot — DO should read HIGH while blocked, LOW
again once clear. Confirm with a multimeter or by reading the pin with a test Arduino sketch
before installing in the paddle.

---

### Step 2 — Mount the Sensor in the Paddle Body

**[PENDING — paddle pocket geometry not yet designed for this sensor.]** See
[Mechanical Requirement](#mechanical-requirement--pending--geometry-not-yet-designed) above.
Once designed: rigid-mount the sensor board to the paddle body (no free-hanging PCB), oriented
so the paddle mechanism's opaque tab passes through the slot on pull. Conformal-coat or pot
the board per the mitigations listed above before final installation.

---

### Step 3 — Route and Connect Wiring

**Do:** Route the wire leads from the sensor pads through the paddle body and steering column
to the Arduino (Uno, Mega, or Nano — same pin numbers on all three). Connect as follows:

| Paddle | Arduino Pin | Mode | Notes |
|---|---|---|---|
| Shift Up (right paddle) | D2 | plain INPUT — sensor drives the line | Tab-in-slot-at-rest = HIGH; do not use INPUT_PULLUP |
| Shift Down (left paddle) | D3 | plain INPUT — sensor drives the line | Tab-in-slot-at-rest = HIGH; do not use INPUT_PULLUP |

Wire GND on each sensor to Arduino GND, VCC to Arduino 5V (or 3.3V — module accepts either).
Wire DO to the Arduino input pin. At rest (tab in slot) the pin reads HIGH; pulling the paddle
clears the tab and the pin reads LOW — the same falling-edge trigger the firmware already
expects (see `Firmware/ArduinoCode/SYSTEM.md`).

**Verify:** With the Arduino powered and running the firmware, open the Serial Monitor
(115200 baud). Press the Shift Up paddle — confirm the display shows a gear increment.
Press Shift Down — confirm a decrement. No press should produce no change.

For full wiring details and the steering column routing guide, see `Schematics/README.md`.

> ⚠️ SAFETY: The NSS (neutral safety switch) is a continuity switch — NOT powered.
> Do not apply 12 V to any NSS or paddle sensor pin. The paddle sensors run on 3.3–5V logic only.

---

## Sensor Alternatives

The optocoupler sensor is user-owned hardware, not a formally sourced/evaluated part — no
alternatives have been evaluated. If it proves unsuitable (sourcing, reliability, or mechanical
integration issues), the former mechanical switch remains a fallback option:

| Part | IP Rating | Electrical Life | Operating Force | Op. Position | Notes |
|---|---|---|---|---|---|
| **Omron D2JW-01K11** *(former selection — mechanical switch fallback)* | IP67 | 100,000 cycles | 82 gf | 8.4 mm | Straight lever, chassis mount, solder lug. See `hardware-bom` skill for full specs if reverting. |
| Omron D2JW-011 | IP67 | 100,000 cycles | 250 gf | — | Pin plunger — rejected; stiff feel, incompatible geometry |
| Omron D2JW-01K21 | IP67 | 100,000 cycles | 100 gf | 14.6 mm | Roller lever — superseded by D2JW-01K11 |
| Omron D2JW-AQ | IP67 | not confirmed | — | — | Automotive-rated; specs unconfirmed — [UNVERIFIED] |
| **Omron D2F-5L** *(replaced — do not use)* | IP40 | 10,000 cycles | 80 gf | 6.8 mm | No water sealing, low electrical life. |
